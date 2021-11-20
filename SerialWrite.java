package com.cookieandroid.cdp;

import java.io.*;

public class SerialWrite implements Runnable {
    private OutputStream ostream;
    private byte[] buffer;

    public SerialWrite(OutputStream ostream, byte[] buffer) {
        this.ostream = ostream;
        this.buffer = buffer;
    }

    public void run() {
        try {
            ostream.write(buffer);
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
