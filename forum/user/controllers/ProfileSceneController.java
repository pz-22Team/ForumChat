package com.forum.user.controllers;

import com.forum.user.controllers.util.SwitchScenes;
import com.forum.user.db.model.User;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import org.jetbrains.annotations.NotNull;

import java.io.IOException;

public class ProfileSceneController {
    @FXML
    private Label userLogin;
    @FXML
    private Label userEmail;
    private User user;
    private final SwitchScenes switchScenes = new SwitchScenes();

    public void onLogOutButtonFromProfileClicked() throws IOException {
        switchScenes.switchToMainScene((Stage) userLogin.getScene().getWindow());
        switchScenes.getMainSceneController().setUser(user);
    }

    public void setUser(final @NotNull User user) {
        this.user = user;
        this.userLogin.setText(user.getLogin());
        this.userEmail.setText(user.getEmail());
    }
}
