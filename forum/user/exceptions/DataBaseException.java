package com.forum.user.exceptions;

public class DataBaseException extends RuntimeException {
    public DataBaseException() {}

    public DataBaseException(Throwable e) {
        super(e);
    }

    public DataBaseException(String message, Throwable e) {
        super(message, e);
    }
}
