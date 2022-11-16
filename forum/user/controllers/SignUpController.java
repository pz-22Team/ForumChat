package com.forum.user.controllers;

import com.forum.user.alerts.MyAlert;
import com.forum.user.app.UserApplication;
import com.forum.user.controllers.util.SwitchScenes;
import com.forum.user.db.manager.DBManager;
import com.forum.user.db.model.User;
import com.forum.user.validators.UserInputValidator;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;


import java.io.IOException;

public class SignUpController {
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private TextField emailField;

    private final DBManager dbManager = DBManager.getInstance();
    private final MyAlert alert = new MyAlert(UserApplication.SIGNUP_SCENE_TITLE);
    private final SwitchScenes switchScenes = new SwitchScenes();

    public void onSignUpButtonClicked(ActionEvent event) throws IOException {
        String userName = usernameField.getText();
        String userPassword = passwordField.getText();
        String userEmail = emailField.getText();
        clearTextFields();
        try {
            UserInputValidator.validateInput(userName);
            UserInputValidator.validateInput(userPassword);
            UserInputValidator.validateEmail(userEmail);
        } catch (IllegalArgumentException e) {
            alert.show(MyAlert.WARNING, "Upss..", e.getMessage());
            return;
        }
        if(registerUser(userName, userPassword, userEmail)) {
            alert.show(MyAlert.INFORMATION, "Success!", "Registered success) Please log in");
            switchScenes.switchToLogInScene(event);
        } else {
            alert.show(MyAlert.WARNING, "Upss..", "Username is already taken :(");
        }
    }

    public void switchToLogInScene(ActionEvent event) throws IOException {
        switchScenes.switchToLogInScene(event);
    }

    private boolean registerUser(String login, String password, String email) {
        return dbManager.addUser(User.createUser(login, password, email));
    }

    private void clearTextFields() {
        usernameField.clear();
        passwordField.clear();
        emailField.clear();
    }
}
