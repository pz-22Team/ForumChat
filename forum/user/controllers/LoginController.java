package com.forum.user.controllers;

import com.forum.user.alerts.MyAlert;
import com.forum.user.app.UserApplication;
import com.forum.user.controllers.util.SwitchScenes;
import com.forum.user.db.manager.DBManager;
import com.forum.user.validators.UserInputValidator;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;


import java.io.IOException;

public class LoginController {
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;

    private DBManager dbManager = DBManager.getInstance();
    private MyAlert alert = new MyAlert(UserApplication.LOGIN_SCENE_TITLE);
    private SwitchScenes switchScenes = new SwitchScenes();

    public void onLoginButtonClicked(ActionEvent event) throws IOException {
        String userName = usernameField.getText();
        String userPassword = passwordField.getText();
        clearTextFields();
        try {
            UserInputValidator.validateInput(userName);
            UserInputValidator.validateInput(userPassword);
        } catch (IllegalArgumentException e) {
            alert.show(MyAlert.WARNING,"Upss..", e.getMessage());
            return;
        }
        if(!isUserRegistered(userName, userPassword)) {
            alert.show(MyAlert.WARNING,"Upss...", "You are not registered!");
        } else {
            switchScenes.switchToMainScene(event);
        }
    }

    public void switchToSignUpScene(ActionEvent event) throws IOException {
        switchScenes.switchToSignUpScene(event);
    }



    private boolean isUserRegistered(String username, String password) {
        return dbManager.getUser(username, password) != null;
    }

    private void clearTextFields() {
        usernameField.clear();
        passwordField.clear();
    }
}