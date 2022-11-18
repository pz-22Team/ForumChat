package com.forum.user.controllers;

import com.forum.user.controllers.util.SwitchScenes;
import com.forum.user.db.model.User;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;
import java.io.IOException;

public class MainSceneController  {
    @FXML
    private TextArea messageArea;
    private User user;
    private final SwitchScenes switchScenes = new SwitchScenes();

    public void onLogOutButtonClicked() throws IOException {
        switchScenes.switchToLogInScene((Stage) messageArea.getScene().getWindow());
    }

    public void onProfileButtonClicked() throws IOException {
        switchScenes.switchToProfileScene((Stage) messageArea.getScene().getWindow());
        switchScenes.getProfileSceneController().setUser(user);
    }

    public void setUser(final User user) {
        this.user = user;
    }

    public void onSendButtonClicked() {
        String message = messageArea.getText();
        //TODO
        messageArea.clear();
    }
}
