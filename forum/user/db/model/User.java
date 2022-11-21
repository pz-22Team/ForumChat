package com.forum.user.db.model;

import java.util.Objects;
import java.util.StringJoiner;

public class User {
    private int id;
    private String login;
    private String password;
    private String email;

    public static User createUser(String login, String password, String email) {
        return new User(0, login, password, email);
    }

    private User(int id, String login, String password, String email) {
        this.id = id;
        this.login = login;
        this.password = password;
        this.email = email;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", "[", "]")
                .add("id: " + id)
                .add("login: " + login)
                .add("email: " + email)
                .add("password: " + password)
                .toString();
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null || getClass() != obj.getClass()) return false;
        User user = (User) obj;
        return Objects.equals(login, user.login)
                && Objects.equals(password, user.password);
    }

    @Override
    public int hashCode() {
        return Objects.hash(login, password);
    }
}