package com.forum.user.exceptions;

public class BadMessageException extends RuntimeException {

    public BadMessageException() { }

    public BadMessageException(String message) {
        super(message);
    }

    public BadMessageException(String message, Throwable cause) {
        super(message, cause);
    }
}
