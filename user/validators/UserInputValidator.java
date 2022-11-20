package com.forum.user.validators;

import java.util.regex.Pattern;

public class UserInputValidator {

    private UserInputValidator() {
    }

    public static void validateInput(String input) throws IllegalArgumentException {
        if(input == null || input.isEmpty())
            throw new IllegalArgumentException("Bad input!");
    }

    public static void validateEmail(String email) throws IllegalArgumentException {
        if (!Pattern.compile("^(.+)@(\\S+)$")
                .matcher(email)
                .matches())
            throw new IllegalArgumentException("Bad email format! (--@--.---");
    }
}
