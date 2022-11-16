package com.forum.user.app;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

import java.io.IOException;

public class UserApplication extends Application {

    public static final String LOGIN_SCENE_TITLE = "Log in";
    public static final String SIGNUP_SCENE_TITLE = "Sign up";
    public static final String MAIN_SCENE_TITLE = "Forum(client)";
    public static final String LOGIN_SCENE_PATH = "login.fxml";
    public static final String MAIN_SCENE_PATH = "mainScene.fxml";
    public static final String SIGNUP_SCENE_PATH = "signUp.fxml";
    public static final String ICON_PATH = "userIcon.png";

    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(UserApplication.class.getResource(LOGIN_SCENE_PATH));
        Scene startScene = new Scene(fxmlLoader.load());
        Image img = new Image(ICON_PATH);
        stage.getIcons().add(img);
        stage.setResizable(false);
        stage.setTitle(LOGIN_SCENE_TITLE);
        stage.setScene(startScene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}