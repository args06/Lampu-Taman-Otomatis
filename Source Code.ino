#include <SoftwareSerial.h>
SoftwareSerial Blue(2, 3);

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

String data;
String dataBaru;
String waktu;
 
int LED = 13; // Led connected
String ON = "2";// light on
String OFF = "1"; // light off

void setup()
{
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, LOW);
  Serial.begin(9600);
  Blue.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
 
void loop()
{
  while(Blue.available()==0) ;
  if(Blue.available()>0)
  {
    data = String(Blue.parseInt());
    Serial.println(data);
  } 

  if(data.length() < 2){
    if (data == ON)
    {
      digitalWrite(LED,HIGH);
      Serial.println("LED ON ");
    }
     
    if( data == OFF)
    {
      digitalWrite(LED,LOW);
      Serial.println("LED OFF");
    }
  } else {
    dataBaru = data.substring(0,2) + ":" + data.substring(2,4);

    while(true){
      if(data.substring(4) != "1" && data.substring(4) != "2"){
        Serial.println("WRONG");
        break;
      }
      
      DateTime now = rtc.now();
      waktu = digit(now.hour());
      waktu += ":";
      waktu += digit(now.minute());
      Serial.println("Patokan : " + data.substring(4));
      Serial.println("Data : " + dataBaru);
      Serial.println("Waktu : " + waktu + ":" + now.second());
      
      if(dataBaru == waktu){
        if(data.substring(4) == "1"){
          digitalWrite(LED,LOW);
          Serial.println("LED OFF");
          break;
        } else if (data.substring(4) == "2"){
          digitalWrite(LED,HIGH);
          Serial.println("LED ON ");
          break;
        }
      }
      waktu = "";
      delay(1000);
    }
  }
}

String digit(int number) {
  String temp = "";
  if (number < 10) {
    temp = "0";
  }
  temp += String(number);
  return temp;
}
