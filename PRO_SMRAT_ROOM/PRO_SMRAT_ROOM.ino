#include <SPI.h>
#include <Servo.h>
#include <MFRC522.h>
#include <DS3231.h>
#include <Wire.h>
#include <RTClib.h> 

Servo myservo;
RTC_DS3231 rtc;
//DS3231  rtc(SDA, SCL);

#define SS_PIN 9
#define RST_PIN 8
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin();
  rtc.begin();

  pinMode(22,OUTPUT);//Living_Room #buzzer
  pinMode(3,OUTPUT);//Living_Room #led
  pinMode(4,OUTPUT);//Living_Room #????
  pinMode(2,INPUT);//Living_Room  #pir
  pinMode(24,OUTPUT);//Bedroom #buzzer
  pinMode(23,OUTPUT);//Bedroom #led
  pinMode(7,OUTPUT);//Bedroom #???
  pinMode(5,INPUT);//Bedroom #pir
  pinMode(26,OUTPUT);//Kitchen #led
  pinMode(11,OUTPUT);//Kitchen #???
  pinMode(25,OUTPUT);//Kitchen #buzzer
  pinMode(6,INPUT);//Kitchen #pir
  pinMode(12,OUTPUT);//Toilet #???
  pinMode(27,OUTPUT);//Toilet #buzzer
  pinMode(28,OUTPUT);//Toilet #led
  pinMode(10,INPUT);//Toilet #pir
}
void loop() {
  int LDR = analogRead(0);
  Serial.print(LDR+String",")
  living_Room();
  bed_Room();
  kitchen();
  toilet();
  rfid();
}
void living_Room(){
  fire_1();
  pir1();
}
void rfid(){
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
  // Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //  Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));  
   }
  content.toUpperCase();
  Serial.print(content+String(","));
}
void fire_1(){
 static unsigned long TIME_2 = millis();
 if((millis()-TIME_2)>500){
  TIME_2 = millis();
  int sensorValue = analogRead(A15);
  Serial.print(sensorValue+String","); //frie_1
  if(sensorValue<=600){
    digitalWrite(22,HIGH);
    analogWrite(4,20);
    }
  else{
    digitalWrite(22,LOW);
    analogWrite(4,0);
  }
 }
}
void pir1(){
  if(LDR<=300){
  static unsigned long TIME_3 = millis();
    if((millis()-TIME_3)>1000){
      TIME_3 = millis();
      int value= digitalRead(2);//read 2 on led 3 
        if (value == HIGH){digitalWrite(3, HIGH);delay(1000);}
          else{digitalWrite(3, LOW);delay(1000) ;
        }
     }
  }
} 
void TIME(){
  RTC.adjust(DateTime(__DATE__, __TIME__));
  static unsigned long TIME = millis();
  if((millis()-TIME)>=1000){
    TIME = millis();
    DateTime now = RTC.now();
    Serial.print("Time:  ");
    Serial.print(rtc.getDateStr());
    Serial.print("  Date: ");
    Serial.print(now.hour(),DEC);
    Serial.print(":"+String(now.minute(),DEC));
    Serial.print(":"+String(now.second(),DEC));
    Serial.print(",")//time
 }
}

void bed_Room(){
  fire_2();
  pir2();
}

void fire_2(){
 static unsigned long TIME_3 = millis();
 if((millis()-TIME_3)>500){
  TIME_3 = millis();
  int sensorValue = analogRead(A14);
  Serial.print(sensorValue+String(","));
  if(sensorValue<=600){
    digitalWrite(24,HIGH);
    analogWrite(7,20);
    }
  else{
    digitalWrite(24,LOW);
    analogWrite(7,0);
  }
 }
}
void pir2(){
    if(LDR<=300){
      static unsigned long TIME_4 = millis();
      if((millis()-TIME_4)>1000){
        TIME_4 = millis();
        int value= digitalRead(5);
        if (value == HIGH){
          digitalWrite(23, HIGH);
        }
          else{digitalWrite(23, LOW);
        }
      }
    }
}

void Kitchen(){
  fire_3();
  pir3();
}
void fire_3(){
 static unsigned long TIME_5 = millis();
 if((millis()-TIME_5)>500){
  TIME_5 = millis();
  int sensorValue = analogRead(A13);
  Serial.print(sensorValue+String(","));
  if(sensorValue<=600){
    digitalWrite(26,HIGH);
    analogWrite(11,20);
  }
  else{
    digitalWrite(26,LOW);
    analogWrite(11,0);
  }
 }
}
void pir3(){
    if(LDR<=300){
      static unsigned long TIME_6 = millis();
      if((millis()-TIME_6)>1000){
        TIME_6 = millis();
        int value= digitalRead(6);
          if (value == HIGH){
            digitalWrite(25, HIGH);
          }
          else{
            digitalWrite(25, LOW);
          
          }
    }
  }
}
void Toilet(){
 fire_4();
 pir4(); 
}
void fire_4(){
 static unsigned long TIME_7 = millis();
 if((millis()-TIME_7)>500){
  TIME_7 = millis();
  int sensorValue = analogRead(A12);
  Serial.print(sensorValue+String(","));
  if(sensorValue<=600){
    digitalWrite(27,HIGH);
    analogWrite(12,20);
    }
  else{
    digitalWrite(27,LOW);
    analogWrite(12,0);
    }
 }
}
void pir4(){
  if(LDR<=300){
    static unsigned long TIME_8 = millis();
    if((millis()-TIME_8)>1000){
      TIME_8 = millis();
      int value= digitalRead(10);
      if (value == HIGH){
        digitalWrite(28, HIGH);
      }
      else{
        digitalWrite(28, LOW);
      }
    }
  }
}
void SERVO(){
  myservo.attach(13);
  myservo.write(90);
  delay(1000);
  myservo.write(-90);
  delay(1000);    
 }
}
