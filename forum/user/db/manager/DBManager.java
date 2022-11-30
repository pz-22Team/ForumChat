package com.forum.user.db.manager;

import com.forum.user.db.connectionPool.*;
import com.forum.user.db.dao.UserDAO;
import com.forum.user.db.model.User;
import com.forum.user.exceptions.DataBaseException;

import java.io.FileInputStream;
import java.io.IOException;
import java.sql.*;
import java.util.List;
import java.util.Properties;

public class DBManager {
    private static DBManager INSTANCE;
    private final ConnectionPool connectionPool;

    private DBManager() throws SQLException {
        BasicConnectionPool pool = null;
        try {
            pool = BasicConnectionPool.create(getUrl());
        } catch (SQLException e) {
            e.printStackTrace();
            throw new SQLException(e);
        } finally {
            connectionPool = pool;
        }
    }

    private String getUrl() {
        Properties properties = new Properties();
        String url = null;

        try(FileInputStream fis = new FileInputStream("database.properties")) {
            properties.load(fis);
            url = properties.getProperty("connection.url");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return url;
    }

    public static synchronized DBManager getInstance() {
        if(INSTANCE == null) {
            try {
                INSTANCE = new DBManager();
            } catch (SQLException e) {
                throw new DataBaseException();
            }
        }
        return INSTANCE;
    }

    public List<User> findAllUsers() {
        List<User> listOfUsers;
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        listOfUsers = userDAO.readAll();
        connectionPool.releaseConnection(connection);
        return listOfUsers;
    }

    public long getAmountOfUsers() {
        return findAllUsers().size();
    }

    public boolean addUser(User user) {
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        boolean result = userDAO.create(user);
        connectionPool.releaseConnection(connection);
        return result;
    }

    public User getUser(String login, String password) {
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        User user = userDAO.read(login, password);
        connectionPool.releaseConnection(connection);
        return user;
    }

    public boolean deleteUser(User user) {
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        boolean result = userDAO.delete(User.createUser(user.getLogin(), user.getPassword(), ""));
        connectionPool.releaseConnection(connection);
        return result;
    }

    public boolean updateUser(User user) {
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        boolean result = userDAO.update(user);
        connectionPool.releaseConnection(connection);
        return result;
    }

    public boolean updateUserOnline(String login, boolean isOnline) {
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        boolean result = userDAO.updateOnline(login, isOnline);
        connectionPool.releaseConnection(connection);
        return result;
    }

    public boolean isOnline(String login) {
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        boolean result = userDAO.isOnline(login);
        connectionPool.releaseConnection(connection);
        return result;
    }

    public int getOnline() {
        Connection connection = connectionPool.getConnection();
        UserDAO userDAO = new UserDAO(connection);
        int result = userDAO.getAmountOfOnlineUsers();
        connectionPool.releaseConnection(connection);
        return result;
    }

    public void shutdown() {
        try {
            connectionPool.shutdown();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
