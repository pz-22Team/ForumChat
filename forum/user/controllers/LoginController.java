package com.forum.user.controllers;

import com.forum.user.alerts.MyAlert;
import com.forum.user.app.UserApplication;
import com.forum.user.db.manager.DBManager;
import com.forum.user.validators.LoginValidator;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;

    private DBManager dbManager = DBManager.getInstance();
    private MyAlert alert = new MyAlert(MyAlert.WARNING, "Login");

    public void onLoginButtonClicked() {
        String userName = usernameField.getText();
        String userPassword = passwordField.getText();
        clearTextFields();
        try {
            LoginValidator.validateUserInput(userName);
            LoginValidator.validateUserInput(userPassword);
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
            alert.show("Upss..", e.getMessage());
            return;
        }
        if(!isUserRegistered(userName, userPassword)) {
            alert.show("Upss...", "You are not registered!");
        } else {
            //TODO
        }
    }

    public void switchToSignUpScene(ActionEvent event) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(UserApplication.class.getResource("signUp.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        Stage currentStage = (Stage)((Node)(event.getSource())).getScene().getWindow();
        currentStage.setScene(scene);
        currentStage.setTitle("Sign up");
        currentStage.show();
    }

    private boolean isUserRegistered(String username, String password) {
        return dbManager.getUser(username, password) != null;
    }

    private void clearTextFields() {
        usernameField.clear();
        passwordField.clear();
    }
}