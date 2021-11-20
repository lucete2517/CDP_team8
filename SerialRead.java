package com.cookieandroid.cdp;

import java.io.*;

public class SerialRead extends Thread {
    private InputStream istream;
    public byte[] buffer;
    public int readlen;

    public SerialRead(InputStream istream, int bufflen) {
        this.istream = istream;
        this.buffer = new byte[bufflen];
    }

    public void run() {
        try {
            readlen = istream.read(buffer);
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
