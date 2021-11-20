#include <stdio.h>

#define TRIG 45 //핀번호
#define ECHO 44 //핀번호

void setup() {
  Serial.begin(9600); //전송속도 (와이파이가 대체로 115200으로 사용한다고 함)

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
 

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

  delay(1000); //1초
}
