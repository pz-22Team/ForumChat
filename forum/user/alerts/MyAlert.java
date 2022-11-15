package com.forum.user.alerts;

import javafx.scene.control.Alert;

public class MyAlert extends Alert {

    public static final AlertType WARNING = AlertType.WARNING;
    public static final AlertType ERROR = AlertType.ERROR;
    public static final AlertType INFORMATION = AlertType.INFORMATION;

    public MyAlert(AlertType alertType, String title) {
        super(alertType);
        super.setTitle(title);
    }

    public void show(String headerText, String bodyText) {
        super.setHeaderText(headerText);
        super.setContentText(bodyText);
        /*((Stage)super.getDialogPane()
                .getScene()
                .getWindow())
                .getIcons()
                .add(new Image(""));*/
        super.showAndWait();
    }
}
