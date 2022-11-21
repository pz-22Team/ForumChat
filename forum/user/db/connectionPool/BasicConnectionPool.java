package com.forum.user.db.connectionPool;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class BasicConnectionPool implements ConnectionPool {
    private String url;

    private final List<Connection> connectionPool;
    private final List<Connection> usedConnections = new ArrayList<>();
    private static int INITIAL_POOL_SIZE = 5;

    private BasicConnectionPool(String url, List<Connection> pool) {
        this.url = url;
        this.connectionPool = pool;
    }

    public static BasicConnectionPool create(String url) throws SQLException {
        List<Connection> pool = new ArrayList<>(INITIAL_POOL_SIZE);
        for (int i = 0; i < INITIAL_POOL_SIZE; i++) {
            pool.add(createConnection(url));
        }
        return new BasicConnectionPool(url, pool);
    }

    @Override
    public Connection getConnection() {
        Connection connection;
        try {
            connection = connectionPool
                    .remove(connectionPool.size() - 1);
        } catch (IndexOutOfBoundsException e) {
            throw new NoSuchElementException(e.getMessage(), e);
        }

        usedConnections.add(connection);
        return connection;
    }

    @Override
    public boolean releaseConnection(Connection connection) {
        connectionPool.add(connection);
        return usedConnections.remove(connection);
    }

    private static Connection createConnection(String url) throws SQLException {
        return DriverManager.getConnection(url);
    }

    public int getSize() {
        return connectionPool.size() + usedConnections.size();
    }

    @Override
    public String getUrl() {
        return url;
    }

    public void shutdown() throws SQLException {
        usedConnections.forEach(this::releaseConnection);
        for (Connection c : connectionPool) {
            c.close();
        }
        connectionPool.clear();
    }
}
