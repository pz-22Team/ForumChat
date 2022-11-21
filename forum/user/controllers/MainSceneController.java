package com.forum.user.controllers;

import com.forum.user.alerts.MyAlert;
import com.forum.user.app.UserApplication;
import com.forum.user.controllers.util.SwitchScenes;
import com.forum.user.db.manager.DBManager;
import com.forum.user.db.model.User;
import com.forum.user.sockets.Client;
import javafx.fxml.FXML;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;
import java.io.IOException;
import java.net.UnknownHostException;

public class MainSceneController  {
    @FXML
    private TextArea messageArea;
    private User user;
    private final MyAlert alert = new MyAlert(UserApplication.MAIN_SCENE_TITLE);
    private final SwitchScenes switchScenes = new SwitchScenes();
    private final DBManager dbManager = DBManager.getInstance();

    public void onLogOutButtonClicked() throws IOException {
        setOnlineFalse(user.getLogin());
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
        if(!message.isEmpty()) {
            String toSend = String.format("%s@%s@%s", getOnline(), user.getLogin(), message);
            System.out.println(toSend);
            Client client = Client.getInstance();
            try {
                client.sendMessage(toSend);
            } catch (UnknownHostException e) {
                alert.show(MyAlert.ERROR, "Server connection problem!", "Sry, try again later!");
            }
        }
        messageArea.clear();
    }

    private int getOnline() {
        return dbManager.getOnline();
    }

    private void setOnlineFalse(String login) {
        dbManager.updateUserOnline(login, false);
    }

    public void applyCloseHandler() {
        Stage stage = (Stage)messageArea.getScene().getWindow();
        stage.setOnCloseRequest(ev -> {
            setOnlineFalse(user.getLogin());
        });
    }
}
