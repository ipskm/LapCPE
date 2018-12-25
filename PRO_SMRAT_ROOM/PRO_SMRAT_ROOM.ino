#include <SPI.h>
#include <MFRC522.h>
#include <DS3231.h>
#include <Wire.h>
#include <SPI.h>  
#include <RTClib.h> 

RTC_DS3231 RTC;
DS3231  rtc(SDA, SCL);


#define SS_PIN 9
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();     
  mfrc522.PCD_Init();
  Wire.begin();
  rtc.begin(); 
//Serial.println("Approximate your card to the reader...");
//Serial.println();
  pinMode(22,OUTPUT);//Living_Room
  pinMode(3,OUTPUT);//Living_Room
  pinMode(4,OUTPUT);//Living_Room
  pinMode(2,INPUT);//Living_Room
  pinMode(24,OUTPUT);//Bedroom
  pinMode(23,OUTPUT);//Bedroom
  pinMode(7,OUTPUT);//Bedroom
  pinMode(5,INPUT);//Bedroom
  pinMode(26,OUTPUT);//Kitchen
  pinMode(11,OUTPUT);//Kitchen
  pinMode(25,OUTPUT);//Kitchen
  pinMode(6,INPUT);//Kitchen
  pinMode(12,OUTPUT);//Toilet
  pinMode(27,OUTPUT);//Toilet
  pinMode(28,OUTPUT);//Toilet
  pinMode(10,INPUT);//Toilet
}
void loop() {
  Living_Room();//ห้องนั่งเล่น
  Bed_Room();//ห้องนอน
  Kitchen();//ห้องครัว
  Toilet();//ห้องน้ำ
}
void Living_Room(){
 frie_1();
 RFID();
 PIR_1(); 
}
void RFID(){
  static unsigned TIME_1 = millis();
  if((millis()-TIME_1)>1000){
  TIME_1 = millis();
    // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));  
   }
  Serial.println();
//   // Serial.print("Message : ");
//   content.toUpperCase();
//   if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
//   {
//     Serial.println("Authorized access");
//     Serial.println();
//     delay(3000);
//   }
 
//  else   {
//     Serial.println(" Access denied");
//     delay(100);
//   }TIME();
//  }
// }
void frie_1(){
 static unsigned long TIME_2 = millis();
 if((millis()-TIME_2)>500){
  TIME_2 = millis();
  int sensorValue = analogRead(A15);
  Serial.println("sensorvalue_LivingRoom: "+String(sensorValue));
  if(sensorValue<=100){digitalWrite(22,HIGH);analogWrite(4,20);delay(1000);}
  else{digitalWrite(22,LOW);analogWrite(4,0);delay(1000);}
  
 }
}
void PIR_1(){
  static unsigned long TIME_3 = millis();
  if((millis()-TIME_3)>1000){
    TIME_3 = millis();
    int value= digitalRead(2);
    if (value == HIGH){digitalWrite(3, HIGH);delay(1000);}
    else{digitalWrite(3, LOW);delay(1000) ;
  }
 }
}
void TIME(){
// RTC.adjust(DateTime(__DATE__, __TIME__));
 static unsigned long TIME = millis();
 if((millis()-TIME)>=1000){
 TIME = millis();
 DateTime now = RTC.now();
 Serial.print("Time:  ");
 Serial.print(rtc.getDateStr());
 Serial.print("  Date: ");
 Serial.print(now.hour(),DEC);
 Serial.print(":"+String(now.minute(),DEC));
 Serial.println(":"+String(now.second(),DEC));
 }
}
void Bed_Room(){
  frie_2();
  PIR_2();
}
void frie_2(){
 static unsigned long TIME_3 = millis();
 if((millis()-TIME_3)>500){
  TIME_3 = millis();
  int sensorValue = analogRead(A14);
  Serial.println("sensorvalue_Bedroom: "+String(sensorValue));
  if(sensorValue<=60){digitalWrite(24,HIGH);analogWrite(7,20);delay(1000);}
  else{digitalWrite(24,LOW);analogWrite(7,0);delay(1000);}
  
 }
}
void PIR_2(){
  static unsigned long TIME_4 = millis();
  if((millis()-TIME_4)>1000){
    TIME_4 = millis();
    int value= digitalRead(5);
    if (value == HIGH){digitalWrite(23, HIGH);delay(1000);}
    else{digitalWrite(23, LOW);delay(1000) ;
  }
 }
}
void Kitchen(){
  frie_3();
  PIR_3();
}
void frie_3(){
 static unsigned long TIME_5 = millis();
 if((millis()-TIME_5)>500){
  TIME_5 = millis();
  int sensorValue = analogRead(A13);
  Serial.println("sensorvalue_Kitchen: "+String(sensorValue));
  if(sensorValue<=100){digitalWrite(26,HIGH);analogWrite(11,20);delay(1000);}
  else{digitalWrite(26,LOW);analogWrite(11,0);delay(1000);}
  
 }
}
void PIR_3(){
  static unsigned long TIME_6 = millis();
  if((millis()-TIME_6)>1000){
    TIME_6 = millis();
    int value= digitalRead(6);
    if (value == HIGH){digitalWrite(25, HIGH);delay(1000);}
    else{digitalWrite(25, LOW);delay(1000) ;
  }
 }
}
void Toilet(){
 frie_4();
 PIR_4(); 
}
void frie_4(){
 static unsigned long TIME_7 = millis();
 if((millis()-TIME_7)>500){
  TIME_7 = millis();
  int sensorValue = analogRead(A12);
  Serial.println("sensorvalue_Toilet: "+String(sensorValue));
  if(sensorValue<=100){digitalWrite(27,HIGH);analogWrite(12,20);delay(1000);}
  else{digitalWrite(27,LOW);analogWrite(12,0);delay(1000);}
  
 }
}
void PIR_4(){
  static unsigned long TIME_8 = millis();
  if((millis()-TIME_8)>1000){
    TIME_8 = millis();
    int value= digitalRead(10);
    if (value == HIGH){digitalWrite(28, HIGH);delay(1000);}
    else{digitalWrite(28, LOW);delay(1000) ;
  }
 }
}