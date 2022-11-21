package com.forum.user.logger;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class MyLogger {
    private static File file;
    public static final String INFO = "INFO";
    public static final String ERROR = "ERROR";

    static {
        file = new File("log.txt");
        if(!file.exists()) {
            try {
                file.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void log(String type, String message) {
        SimpleDateFormat sdfDate = new SimpleDateFormat("HH:mm:ss");
        Date now = new Date();
        String strDate = sdfDate.format(now);
        try(FileWriter fWriter = new FileWriter(file, true)) {
            fWriter.write(String.format("[%s]: %s - %s%n", strDate, type, message));
            fWriter.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
