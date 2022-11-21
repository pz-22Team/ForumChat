package com.forum.user.sockets;

import com.forum.user.logger.MyLogger;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Properties;


public class Client {
    private PrintWriter printWriter;
    private static final Client INSTANCE;
    //private static final Logger com.forum.user.logger = LogManager.getLogger();
    private static final MyLogger logger = new MyLogger();
    private String host;
    private Integer port;
    private Socket socket;

    static {
        INSTANCE = new Client();
    }
    private Client() {
        setServerConfig();
    }

    public static synchronized Client getInstance() {
        return INSTANCE;
    }

    public void sendMessage(String message) throws UnknownHostException {
        try {
            socket = new Socket(host, port);
            logger.log(MyLogger.INFO,"Client created port: " + port.toString());

            printWriter = new PrintWriter(socket.getOutputStream());
            printWriter.println(message);

            logger.log(MyLogger.INFO, "Message sent to server: " + message);
        } catch (UnknownHostException e) {
            e.printStackTrace();
            logger.log(MyLogger.ERROR, "Cannot connect to server");
            throw new UnknownHostException(e.getMessage());
        } catch(IOException e) {
            logger.log(MyLogger.ERROR, "Cannot connect to server");
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
