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
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import java.io.IOException;

public class LoginSceneController {
    @FXML
    private TextField userLoginField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private TextField passwordFieldText;
    @FXML
    private ImageView passwordVisibility;
    private User user;

    private final DBManager dbManager = DBManager.getInstance();
    private final MyAlert alert = new MyAlert(UserApplication.LOGIN_SCENE_TITLE);
    private final SwitchScenes switchScenes = new SwitchScenes();

    public void onLoginButtonClicked(ActionEvent event) throws IOException {
        String userLogin = userLoginField.getText();
        String userPassword = passwordField.getText().isEmpty() ? passwordFieldText.getText() : passwordField.getText();
        clearTextFields();

        try {
            UserInputValidator.validateInput(userLogin);
            UserInputValidator.validateInput(userPassword);
        } catch (IllegalArgumentException e) {
            alert.show(MyAlert.WARNING,"Upss..", e.getMessage());
            return;
        }
        if(isUserRegistered(userLogin, userPassword)) {
            setOnlineTrue(userLogin);
            switchScenes.switchToMainScene(event);
            MainSceneController controller = switchScenes.getMainSceneController();
            controller.setUser(user);
            controller.applyCloseHandler();
        } else {
            alert.show(MyAlert.WARNING,"Upss...", "You are not registered!");
        }
    }

    public void switchToSignUpScene(ActionEvent event) throws IOException {
        switchScenes.switchToSignUpScene(event);
    }

    private boolean isUserRegistered(String username, String password) {
        this.user = dbManager.getUser(username, password);
        return user != null;
    }

    private void setOnlineTrue(String userLogin) {
        dbManager.updateUserOnline(userLogin, true);
    }

    public void onHideUnhidePasswordButtonClicked() {
        if(!passwordField.isVisible()) {
            swap(passwordFieldText, passwordField, UserApplication.HIDE_ICON_PATH);
        } else {
            swap(passwordField, passwordFieldText, UserApplication.UNHIDE_ICON_PATH);
        }
    }

    private void swap(TextField source, TextField destination, String pathToImage) {
        source.setVisible(false);
        destination.setText(source.getText());
        destination.setVisible(true);
        passwordVisibility.setImage(new Image(pathToImage));
    }

    private void clearTextFields() {
        userLoginField.clear();
        passwordField.clear();
    }
}