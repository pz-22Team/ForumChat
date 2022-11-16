package com.forum.user.controllers;


import com.forum.user.controllers.util.SwitchScenes;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import java.io.IOException;

public class MainSceneController {
    @FXML
    private TextArea messageArea;
    private SwitchScenes switchScenes = new SwitchScenes();

    public void onLogOutButtonClicked(ActionEvent event) throws IOException {
        switchScenes.switchToLogInScene(event);
    }

    public void onSendButtonClicked() {
        String message = messageArea.getText();
        //TODO
        messageArea.clear();
    }
}
