package com.forum.user.sockets;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Properties;
import java.util.Scanner;

public class Client {
    private PrintWriter printWriter;
    private InputStream inputStream;
    private static final Client INSTANCE;
    private String host;
    private Integer port;

    static {
        INSTANCE = new Client();
    }
    private Client() {
        setServerConfig();
    }

    public static synchronized Client getInstance() {
        return INSTANCE;
    }

    public void sendMessage(String message) {
        Socket socket;
        try {
            socket = new Socket(host, port);
            System.out.println("client created port: " + port.toString());

            printWriter = new PrintWriter(socket.getOutputStream());
            printWriter.println(message);
            inputStream = socket.getInputStream();
        } catch(IOException e) {
            e.printStackTrace();
        } finally {
            printWriter.close();
        }
    }

    private void setServerConfig() {
        Properties properties = new Properties();

        try(FileInputStream fis = new FileInputStream("client.properties")) {
            properties.load(fis);
            host = properties.getProperty("host");
            port = Integer.valueOf(properties.getProperty("port"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
