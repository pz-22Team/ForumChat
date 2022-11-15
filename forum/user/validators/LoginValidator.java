package com.forum.user.validators;

public class LoginValidator {

    private LoginValidator() {
    }

    public static void validateUserInput(String input) throws IllegalArgumentException {
        if(input == null || input.isEmpty())
            throw new IllegalArgumentException("Bad input!");
    }
}
