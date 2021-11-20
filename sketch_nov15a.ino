#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include <ESP8266WiFi.h>
#include <stdio.h>

#define TRIG 45 //핀번호
#define ECHO 44 //핀번호

//wifi 정보
const char* ssid = "iptime"; //wifi 이름
const char* password = "best1008!!"; //wifi 비번

//sql 연결셋팅부
IPAddress server_addr(222, 103, 154, 206); // DB ip
char user[] = "root"; //DB ID
char password_[] = "456258"; //DB password

WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

char INSERT_SQL[] = ""; //쿼리문 

void setup() {
  Serial.begin(115200); //전송속도 (와이파이가 대체로 115200으로 사용한다고 함)

  Wifi_connect();

  Serial.print("Connecting to SQL... ");
  if (conn.connect(server_addr, 3306, user, password_)) {
    Serial.println("OK.");
    }
  else {
    Serial.println("FAILED.");
    }
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) { //와이파이 연결이 이상할시에 재접속 하는 코드
    Serial.println("try reconnect");
    Wifi_connect();
    }

  long duration = 0;
  long distance = 0;

  digitalWrite(TRIG, HIGH); //TRIG 오픈 (초음파 발사)
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW); //TRIG 오픈 (초음파 종료)
  
  duration = pulseIn(ECHO, HIGH); //ECHO가 열린 시간 (초음파가 되돌아오는 시간)
  distance = ((float)(340 * duration) / 1000) / 2; //거리 계산)
  
  Serial.print("duration = " + (String)duration + "\n"); //
  Serial.print("distance = " + (String)distance);
  Serial.println("mm\n");

  sprintf(INSERT_SQL, "INSERT INTO test02.sensor VALUES (%d)", distance); //SQL 선언

  if (conn.connected()) {
    cursor->execute(INSERT_SQL); //DB에 SQL 입력
  }

  delay(1000000); //1초
}

void Wifi_connect() {
  Serial.println("---------------------------------------");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // 와이파이 이름과 비밀번호를 통해 WIFI연결을 시작 // WL_CONNECTED라는 값을 돌려준
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Wifi connected!");
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());
}
