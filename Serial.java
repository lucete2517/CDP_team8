package com.cookieandroid.cdp;

import java.io.*;
import java.net.*;

public class Serial implements Runnable {
    private ServerSocket serv_sock; //클라이언트의 접속 요청을 받아들이는 소켓
    private Socket sock;            //클라이언트와 통신하는 소켓
    private InputStream istream;    //클라이언트에게 데이터를 입력받는 스트림 객체
    private OutputStream ostream;   //클라이언트에게 데이터를 출력하는 스트림 객체
    private int port = 3000;        //포트 번호

    public void run() {
        try {
            serv_sock = new ServerSocket(port); //서버 소켓 생성
            sock = serv_sock.accept();          //클라이언트 소켓 열기
            istream = sock.getInputStream();    //입력 스트림 생성
            ostream = sock.getOutputStream();   //출력 스트림 생성

            System.out.println("Connected");    //소켓 생성 및 연결 성공 확인 메시지

            //new Thread(new SerialRead(istream, 256));             //입력 스레드
            //new Thread(new SerialWrite(ostream, new byte[256]));  //출력 스레드

            sock.close();                       //클라이언트 소켓 닫기
            serv_sock.close();                  //서버 소켓 닫기
        }
        catch (IOException e) {
            System.out.println(e.getMessage()); //오류 처리
            System.exit(1);
        }
    }
}