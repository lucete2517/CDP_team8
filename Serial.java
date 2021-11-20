package com.cookieandroid.cdp;

import java.io.*;
import java.net.*;

public class Serial implements Runnable {
    private ServerSocket serv_sock;
    private Socket sock;
    private InputStream istream;
    private OutputStream ostream;
    private int port = 3000;

    public void run() {
        try {
            serv_sock = new ServerSocket(port);
            sock = serv_sock.accept();
            istream = sock.getInputStream();
            ostream = sock.getOutputStream();

            System.out.println("Connected");

            //new Thread(new SerialRead(istream, 256));
            //new Thread(new SerialWrite(ostream, new byte[256]));

            sock.close();
            serv_sock.close();
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
            System.exit(1);
        }
    }
}