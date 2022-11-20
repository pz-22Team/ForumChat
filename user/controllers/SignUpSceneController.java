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

public class SignUpSceneController {
    @FXML
    private TextField userLoginField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private TextField passwordFieldConfirm;
    @FXML
    private TextField emailField;

    private final DBManager dbManager = DBManager.getInstance();
    private final MyAlert alert = new MyAlert(UserApplication.SIGNUP_SCENE_TITLE);
    private final SwitchScenes switchScenes = new SwitchScenes();

    public void onSignUpButtonClicked(ActionEvent event) throws IOException {
        String userName = userLoginField.getText();
        String userPassword = passwordField.getText();
        String userPasswordConfirm = passwordFieldConfirm.getText();
        String userEmail = emailField.getText();
        clearTextFields();
        try {
            UserInputValidator.validateInput(userName);
            UserInputValidator.validateInput(userPassword);
            UserInputValidator.validateInput(userPasswordConfirm);
            UserInputValidator.validateEmail(userEmail);
        } catch (IllegalArgumentException e) {
            alert.show(MyAlert.WARNING, "Upss..", e.getMessage());
            return;
        }
        try {
            registerUser(userName, userPassword, userPasswordConfirm, userEmail);
            alert.show(MyAlert.INFORMATION, "Success!", "Registered success) Please log in");
            switchScenes.switchToLogInScene(event);
        } catch (IllegalArgumentException e){
            alert.show(MyAlert.WARNING, "Upss..", e.getMessage());
        }
    }

    public void switchToLogInScene(ActionEvent event) throws IOException {
        switchScenes.switchToLogInScene(event);
    }

    private void registerUser(String login, String password, String passwordConfirm, String email) {
        if (!password.equals(passwordConfirm))
            throw new IllegalArgumentException("Bad password!");
        if(!dbManager.addUser(User.createUser(login, password, email)))
            throw new IllegalArgumentException("Username is already taken :(");
    }

    private void clearTextFields() {
        userLoginField.clear();
        passwordField.clear();
        emailField.clear();
        passwordFieldConfirm.clear();
    }
}
