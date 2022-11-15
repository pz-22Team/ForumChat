package com.forum.user.app;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.IOException;

public class UserApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(UserApplication.class.getResource("login.fxml"));
        Scene startScene = new Scene(fxmlLoader.load());

        stage.setResizable(false);
        stage.setTitle("Login");
        stage.setScene(startScene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}