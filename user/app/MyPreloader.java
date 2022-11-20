package com.forum.user.app;

import javafx.application.Preloader;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class MyPreloader extends Preloader {
    private Stage stage;

    @Override
    public void start(Stage stage) throws Exception {
        System.out.println("preloader start");
        this.stage = stage;
        stage.getIcons().add(new Image(UserApplication.ICON_PATH));
        this.stage.setTitle("Connecting...");
        this.stage.setScene(new Scene(
                new FXMLLoader(
                            UserApplication.class.getResource(
                                UserApplication.DATABASE_CONNECTION_SCENE_PATH
                            )
                ).load()
            )
        );
        stage.show();
    }

    @Override
    public void handleStateChangeNotification(StateChangeNotification stateChangeNotification) {
        if(stateChangeNotification.getType() == StateChangeNotification.Type.BEFORE_START) {
            stage.hide();
        }
    }
}
