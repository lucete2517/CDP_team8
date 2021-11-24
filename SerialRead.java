package com.cookieandroid.cdp;

import java.io.*;

public class SerialRead extends Thread {
    private InputStream istream;    //입력 스트림
    public byte[] buffer;           //입력 버퍼
    public int readlen;             //입력 버퍼의 길이

    public SerialRead(InputStream istream, int bufflen) {
        this.istream = istream;             //입력 스트림 생성
        this.buffer = new byte[bufflen];    //입력 버퍼 생성
    }

    public void run() {
        try {
            readlen = istream.read(buffer); //입력 스트림으로부터 입력 버퍼에 값을 입력받음
        }
        catch (IOException e) {
            e.printStackTrace();    //오류 처리
        }
    }
}
