package com.forum.user.controllers.util;

import com.forum.user.app.UserApplication;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class SwitchScenes {
    private FXMLLoader loader;

    public SwitchScenes() {
        loader = new FXMLLoader();
    }

    public void switchToLogInScene(ActionEvent event) throws IOException {
        loader = new FXMLLoader(UserApplication.class.getResource(UserApplication.LOGIN_SCENE_PATH));
        Scene scene = new Scene(loader.load());
        Stage currentStage = (Stage)((Node)(event.getSource())).getScene().getWindow();
        currentStage.setScene(scene);
        currentStage.setTitle(UserApplication.LOGIN_SCENE_TITLE);
        currentStage.show();
    }

    public void switchToSignUpScene(ActionEvent event) throws IOException {
        loader = new FXMLLoader(UserApplication.class.getResource(UserApplication.SIGNUP_SCENE_PATH));
        Scene scene = new Scene(loader.load());
        Stage currentStage = (Stage)((Node)(event.getSource())).getScene().getWindow();
        currentStage.setScene(scene);
        currentStage.setTitle(UserApplication.SIGNUP_SCENE_TITLE);
        currentStage.show();
    }

    public void switchToMainScene(ActionEvent event) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(UserApplication.class.getResource(UserApplication.MAIN_SCENE_PATH));
        Scene scene = new Scene(fxmlLoader.load());
        Stage currentStage = (Stage)((Node)(event.getSource())).getScene().getWindow();
        currentStage.setScene(scene);
        currentStage.setTitle(UserApplication.MAIN_SCENE_TITLE);
        currentStage.show();
    }
}
