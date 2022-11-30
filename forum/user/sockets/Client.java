package com.forum.user.sockets;

import com.forum.user.exceptions.BadMessageException;
import com.forum.user.logger.MyLogger;

import java.io.*;
import java.net.ConnectException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Properties;


public class Client {
    private static final Client INSTANCE;
    //private static final Logger com.forum.user.logger = LogManager.getLogger();
    private static final MyLogger logger = new MyLogger();
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

    public void sendMessage(String message) throws ConnectException, UnknownHostException {
        try(Socket socket = new Socket(host, port)) {
            logger.log(MyLogger.INFO,"Client connected to port: " + port.toString() + ", host: " + host);

            PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
            printWriter.println(message);
            printWriter.flush();
            logger.log(MyLogger.INFO, "Message sent to server: " + message);

            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            String receivedMessage = bufferedReader.readLine();
            logger.log(MyLogger.INFO, "Message received from server: " + receivedMessage);
            if(Boolean.valueOf(receivedMessage).equals(Boolean.FALSE)) {
                throw new BadMessageException("Message is unacceptable!");
            }
            printWriter.close();
            bufferedReader.close();
            socket.close();
        } catch (ConnectException e) {
            logger.log(MyLogger.ERROR, "Cannot connect to server");
            throw new ConnectException(e.getMessage());
        } catch (UnknownHostException e) {
            logger.log(MyLogger.ERROR, "Cannot connect to server");
            throw new UnknownHostException(e.getMessage());
        } catch(IOException e) {
            logger.log(MyLogger.ERROR, "Cannot connect to server");
            e.printStackTrace();
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
