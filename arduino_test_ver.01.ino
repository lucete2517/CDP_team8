#include <ESP8266.h>
#include <SoftwareSerial.h>
#include <stdio.h>

//SoftwareSerial esp8266Serial = SoftwareSerial(2, 3); 
ESP8266 wifi = ESP8266(Serial2);

#define TRIG 45 //핀번호
#define ECHO 44 //핀번호

#define SSID "iptime"
#define PWD "best1008!!"

void setup()
{
  Serial.begin(115200);   // 핀
  Serial2.begin(115200);  // wifi

  wifi.begin();

  Serial.print("test: ");
  Serial.println(getStatus(wifi.test()));
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // joinAP
  Serial.print("joinAP: ");
  Serial.println(getStatus(wifi.joinAP(SSID, PWD)));
 
  // getAP
  Serial.print("getAP: ");
  Serial.println(getStatus(wifi.getAP(SSID)));
  
}

void loop() {


  long duration = 0;
  long distance = 0;

  digitalWrite(TRIG, HIGH); //TRIG 오픈 (초음파 발사)
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW); //TRIG 오픈 (초음파 종료)

  duration = pulseIn(ECHO, HIGH); //ECHO가 열린 시간 (초음파가 되돌아오는 시간)
  distance = ((float)(340 * duration) / 1000) / 2; //거리 계산)

  Serial.print("test: ");
  Serial.println(getStatus(wifi.test()));
  
  Serial.print("duration = " + (String)duration + "\n"); //
  Serial.print("distance = " + (String)distance);
  Serial.println("mm\n");

  delay(1000); //1초
}

String getStatus(ESP8266CommandStatus status)
{
  switch (status) {
    case ESP8266_COMMAND_INVALID:
      return "INVALID";
      break;
 
    case ESP8266_COMMAND_TIMEOUT:
      return "TIMEOUT";
      break;
 
    case ESP8266_COMMAND_OK:
      return "OK";
      break;
 
    case ESP8266_COMMAND_NO_CHANGE:
      return "NO CHANGE";
      break;
 
    case ESP8266_COMMAND_ERROR:
      return "ERROR";
      break;
 
    case ESP8266_COMMAND_NO_LINK:
      return "NO LINK";
      break;
 
    case ESP8266_COMMAND_TOO_LONG:
      return "TOO LONG";
      break;
 
    case ESP8266_COMMAND_FAIL:
      return "FAIL";
      break;
 
    default:
      return "UNKNOWN COMMAND STATUS";
      break;
  }
}
