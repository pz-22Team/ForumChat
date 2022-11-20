package com.forum.user.controllers.util;

import com.forum.user.app.UserApplication;
import com.forum.user.controllers.MainSceneController;
import com.forum.user.controllers.ProfileSceneController;
import javafx.event.ActionEvent;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class SwitchScenes {
    private FXMLLoader loader;
    private MainSceneController mainSceneController;
    private ProfileSceneController profileSceneController;

    public SwitchScenes() {
        loader = new FXMLLoader();
    }

    public MainSceneController getMainSceneController() {
        return this.mainSceneController;
    }

    public ProfileSceneController getProfileSceneController() {
        return this.profileSceneController;
    }

    public void switchToLogInScene(ActionEvent event) throws IOException {
        switchTo(event, UserApplication.LOGIN_SCENE_PATH, UserApplication.LOGIN_SCENE_TITLE);
    }

    public void switchToLogInScene(Stage stage) throws IOException {
        switchTo(stage, UserApplication.LOGIN_SCENE_PATH, UserApplication.LOGIN_SCENE_TITLE);
    }

    public void switchToSignUpScene(ActionEvent event) throws IOException {
        switchTo(event, UserApplication.SIGNUP_SCENE_PATH, UserApplication.SIGNUP_SCENE_TITLE);
    }

    public void switchToProfileScene(Stage stage) throws IOException {
        switchTo(stage, UserApplication.PROFILE_SCENE_PATH, UserApplication.PROFILE_SCENE_TITLE);
    }

    public void switchToMainScene(ActionEvent event) throws IOException {
        switchTo(event, UserApplication.MAIN_SCENE_PATH, UserApplication.MAIN_SCENE_TITLE);
    }

    public void switchToMainScene(Stage stage) throws IOException {
        switchTo(stage, UserApplication.MAIN_SCENE_PATH, UserApplication.MAIN_SCENE_TITLE);
    }

    private void switchTo(ActionEvent event, String path, String title) throws IOException {
        loader = new FXMLLoader(UserApplication.class.getResource(path));
        Scene scene = new Scene(loader.load());
        setController(path, loader);
        Stage currentStage = (Stage)((Node)(event.getSource())).getScene().getWindow();
        currentStage.setScene(scene);
        currentStage.setTitle(title);
        currentStage.show();
    }

    private void switchTo(Stage stage, String path, String title) throws IOException {
        loader = new FXMLLoader(UserApplication.class.getResource(path));
        stage.setScene(new Scene(loader.load()));
        setController(path, loader);
        stage.setTitle(title);
    }

    private void setController(String path, FXMLLoader loader) {
        if(path.equals(UserApplication.MAIN_SCENE_PATH)) {
            this.mainSceneController = loader.getController();
        } else if(path.equals(UserApplication.PROFILE_SCENE_PATH)) {
            this.profileSceneController = loader.getController();
        }
    }
}