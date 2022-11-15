package com.forum.user.db.dao;


import com.forum.user.db.model.User;
import org.jetbrains.annotations.NotNull;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Author : rom4ik.
 * Created : 07/11/2022.
 */
public class UserDAO implements DAO<User, String> {
    private final Connection connection;

    public UserDAO(final Connection connection) {
        this.connection = connection;
    }

    /**
     * Create User in database.
     *
     * @param user for create.
     * @return false if User already exist. If creating success true.
     */
    @Override
    public boolean create(@NotNull final User user) {
        boolean result = false;
        try (PreparedStatement statement = connection.prepareStatement(UserQueries.INSERT.QUERY)) {
            statement.setString(1, user.getLogin());
            statement.setString(2, user.getPassword());
            statement.setString(3, user.getEmail());
            result = statement.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result;
    }

    /**
     * Select all Users.
     *
     * @return list of valid entities if exists.
     */
    @Override
    public List<User> readAll() {
        List<User> listOfUsers = new ArrayList<>();
        try(Statement statement = connection.createStatement()) {
            ResultSet res = statement.executeQuery(UserQueries.GET_ALL.QUERY);
            while(res.next()) {
                listOfUsers.add(mapUser(res));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return listOfUsers;
    }

    /**
     * Select User by login.
     *
     * @param login for select.
     * @return valid entity if she exist. If entity does not exist return null
     */
    @Override
    public User read(@NotNull final String login, @NotNull final String password) {
        User user = null;
        try (PreparedStatement statement = connection.prepareStatement(UserQueries.GET.QUERY)) {
            statement.setString(1, login);
            statement.setString(2, password);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                user = mapUser(resultSet);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return user;
    }

    private User mapUser(@NotNull final ResultSet resultSet) throws SQLException {
        User user = User.createUser(resultSet.getString(UserFields.LOGIN.FIELD),
                resultSet.getString(UserFields.PASSWORD.FIELD),
                resultSet.getString(UserFields.EMAIL.FIELD));
        user.setId(resultSet.getInt(UserFields.ID.FIELD));
        return user;
    }

    /**
     * Update User's password by login.
     *
     * @param user new user's state.
     * @return True if success. False if fail.
     */
    @Override
    public boolean update(@NotNull final User user) {
        boolean result = false;
        try (PreparedStatement statement = connection.prepareStatement(UserQueries.UPDATE.QUERY)) {
            statement.setString(1, user.getPassword());
            statement.setInt(2, user.getId());
            result = statement.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result;
    }

    /**
     * Delete User by login AND password.
     *
     * @param user for delete.
     * @return true if User was deleted. False if User not exist.
     */
    @Override
    public boolean delete(@NotNull final User user) {
        boolean result = false;
        try (PreparedStatement statement = connection.prepareStatement(UserQueries.DELETE.QUERY)) {
            statement.setString(1, user.getLogin());
            statement.setString(2, user.getPassword());
            result = statement.executeUpdate() > 0;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return result;
    }

    enum UserQueries {
        GET_ALL("SELECT * FROM logintable"),
        GET("SELECT * FROM logintable WHERE login = ? AND password = sha1(?)"),
        INSERT("INSERT INTO logintable(login, password, email) VALUES(?, sha1(?), ?)"),
        UPDATE("UPDATE logintable SET password = ? WHERE login = ?"),
        DELETE("DELETE FROM logintable WHERE login = ? AND password = sha1(?)");

        final String QUERY;
        UserQueries(String query) {
            this.QUERY = query;
        }
    }

    enum UserFields {
        ID("id"),
        LOGIN("login"),
        EMAIL ("email"),
        PASSWORD("password");

        final String FIELD;
        UserFields(String field) {
            this.FIELD = field;
        }
    }
}
