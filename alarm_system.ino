#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <IRremote.h>
const int trigPin = 34;
const int echoPin = 33;
long duration;
int distance;
bool SoundAlarm;
bool StopAlarm;
int i;
bool possibleIntruder;
#define SS_PIN 45
#define RST_PIN 47
const int recvPin = 8;
IRrecv irrecv(recvPin);
IRsend irsend;
decode_results results;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
Servo myservo;
String authorizedUids[] = {"17 7E 57 62", "F9 54 EB 94", "05 80 3D AA AE D2 00"};
void setup() {
  irrecv.enableIRIn(); // Start the receiver
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(43,INPUT_PULLUP);
  SPI.begin();           // Initialize SPI bus
  mfrc522.PCD_Init();    // Initialize MFRC522
  myservo.attach(11);    // Attach servo to pin 11
  myservo.write(0);      // Initialize servo position to 0 degrees
  pinMode(41,INPUT_PULLUP);
  pinMode(3,OUTPUT);
  SoundAlarm=false;
  StopAlarm=false;
  possibleIntruder=false;
}
void(* resetFunc) (void) = 0;
void gateCheck(){
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
  }

  // Get UID
  String cardUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    cardUid += String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    cardUid += String(mfrc522.uid.uidByte[i], HEX);
  }
  cardUid.trim();  // Remove any extra spaces

  // Check if UID matches any in the array
  for (int i = 0; i < sizeof(authorizedUids) / sizeof(authorizedUids[0]); i++) {
    if (cardUid.equalsIgnoreCase(authorizedUids[i])) {
      myservo.write(90);  // Move servo to 90 degrees
      while(true){
        if(!digitalRead(43)){
          myservo.write(0);
          resetFunc();
        }
      }
    }
    else{
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      if(distance>25){
        resetFunc();
      }
      possibleIntruder=true;
      break;
    }
  }
}
void altOpen(){
  if (irrecv.decode(&results)) {
    myservo.write(90);
    while(true){
      if(!digitalRead(43)){
          myservo.write(0);
          resetFunc();
        }
    }
  }
}
void loop() {
  if(SoundAlarm){
    i=0;
    while(!StopAlarm){
      if(i==255){
        i=0;
      }
      analogWrite(10,i);
      analogWrite(9,i);
      analogWrite(3,(255-i));
      i++;
      if(!digitalRead(41)){

        StopAlarm=true;
        analogWrite(10,0);
        digitalWrite(37,LOW);
        digitalWrite(39,LOW);
        analogWrite(9,0);
        analogWrite(3,0);
        mfrc522.PICC_HaltA();
        resetFunc();
      }
      delay(1);
    }
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  if(distance<15){
    for(int i=0;i<100;i++){
      altOpen();
      delay(200);
    }
    gateCheck();
    if(possibleIntruder){
    SoundAlarm=true;
    }
  }
}