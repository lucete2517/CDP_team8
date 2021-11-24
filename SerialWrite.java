package com.cookieandroid.cdp;

import java.io.*;

public class SerialWrite implements Runnable {
    private OutputStream ostream;   //출력 스트림
    private byte[] buffer;          //출력 버퍼

    public SerialWrite(OutputStream ostream, byte[] buffer) {
        this.ostream = ostream; //출력 스트림 생성
        this.buffer = buffer;   //출력할 값을 담고 있는 버퍼를 전달받음
    }

    public void run() {
        try {
            ostream.write(buffer);  //출력 스트림에 출력 버퍼의 값을 출력함
        }
        catch (IOException e) {
            e.printStackTrace();    //오류 처리
        }
    }
}
