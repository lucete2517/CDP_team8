#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include <ESP8266.h>
#include <SoftwareSerial.h>
#include <stdio.h>

#include "MPU9250.h"
#include "HX711.h"

//SoftwareSerial esp8266Serial = SoftwareSerial(2, 3); 
ESP8266 wifi = ESP8266(Serial2);

#define TRIG 45 //초음파 센서 핀번호
#define ECHO 44 //초음파 센서 핀번호

#define OBS 12 //장애물 센서 핀번호

#define SCL 21 //무게 센서 핀번호
#define SDA 20 //무게 센서 핀번호

#define SSID "iptime"
#define PWD "best1008!!"

#define calibration -7050.0 //무게센서 스케일 값 선언
HX711 scale(SCL, SDA);
MPU9250 myIMU;

//sql 연결셋팅부
IPAddress server_addr(222, 103, 154, 206); // DB ip
char user[] = "root"; //DB ID
char password_[] = "456258"; //DB password

WiFiClient client; //클라이언트 초기화
MySQL_Connection conn(&client); //SQL 연결
MySQL_Cursor* cursor;


char INSERT_SQL[] = ""; 

void setup()
{
  Serial.begin(115200);   // 핀
  Serial2.begin(115200);  // wifi

  wifi.begin();

  Serial.print("test: ");
  Serial.println(getStatus(wifi.test()));

  scale.set_scale(calibration); //스케일 지정
  scale.tare(); //스케일 설정

  //자이로 센서 통신 연결
  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);
  myIMU.initMPU9250();
  myIMU.initAK8963(myIMU.factoryMagCalibration);
  myIMU.getAres();
  myIMU.getGres();
  myIMU.getMres();
  myIMU.magCalMPU9250(myIMU.magBias, myIMU.magScale);
    
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(OBS, INPUT);

  // joinAP
  Serial.print("joinAP: ");
  Serial.println(getStatus(wifi.joinAP(SSID, PWD)));
 
  // getAP
  Serial.print("getAP: ");
  Serial.println(getStatus(wifi.getAP(SSID)));

  //DB 연결
  Serial.print("Connecting to SQL... ");
  if (conn.connect(server_addr, 3306, user, password_)) {
    Serial.println("OK.");
  }
  else {
    Serial.println("FAILED.");
  }
}

void loop() {
  float weight = 0;
  float duration = 0;
  float distance = 0;
  float obstacle = 0;
  
  digitalWrite(TRIG, HIGH); //TRIG 오픈 (초음파 발사)
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW); //TRIG 오픈 (초음파 종료)

  duration = pulseIn(ECHO, HIGH); //ECHO가 열린 시간 (초음파가 되돌아오는 시간)
  distance = ((float)(340 * duration) / 1000) / 2; //거리 계산
  weight = scale.get_units(); //무게 값 입력

  myIMU.readAccelData(myIMU.accelCount); //자이로 센서 값 받기

  //자이로 센서 값 계산
  myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes;
  myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes;
  myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes;
  myIMU.readGyroData(myIMU.gyroCount);
  
  myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
  myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
  myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;
  myIMU.readMagData(myIMU.magCount);

  myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes * myIMU.factoryMagCalibration[0] - myIMU.magBias[0];
  myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes * myIMU.factoryMagCalibration[1] - myIMU.magBias[1];
  myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes * myIMU.factoryMagCalibration[2] - myIMU.magBias[2];

  if(digitalRead(OBS) == HIGH) { //장애물 센서 값 받기
    obstacle = 0;
  }
  else {
    obstacle = 1;
  }
  
  Serial.print("test: ");
  Serial.println(getStatus(wifi.test()));
  
  sprintf(INSERT_SQL, "INSERT INTO sensor VALUES (Product001, %f, %f, %f, %f)", weight, distance, myIMU.my, obstacle); //SQL 문 설정
  
  if (conn.connected()) {
    cursor->execute(INSERT_SQL); //DB에 SQL 입력
  }
  
  if(weight > 700) { //무게 이상
      sprintf(INSERT_SQL, "INSERT INTO state VALUES (Product001)"); //SQL 문 설정
      if (conn.connected()) {
          cursor->execute(INSERT_SQL); //DB에 SQL 입력
      }
  }
  
  if(distance < 700) { //거리 이상
      sprintf(INSERT_SQL, "INSERT INTO state VALUES (Product001)"); //SQL 문 설정
      if (conn.connected()) {
          cursor->execute(INSERT_SQL); //DB에 SQL 입력
      }
  }
  
  if(myIMU.myt < -10 || myIMU.my > 10) { //무게 중심 이상
      sprintf(INSERT_SQL, "INSERT INTO state VALUES (Product001)"); //SQL 문 설정
      if (conn.connected()) {
          cursor->execute(INSERT_SQL); //DB에 SQL 입력
      }
  }
  
  delay(5000); //5초
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
