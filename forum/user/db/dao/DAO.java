package com.forum.user.db.dao;

import java.util.List;

public interface DAO<Entity, Key> {
    boolean create(Entity model);
    List<Entity> readAll();
    Entity read(Key login, Key password);
    boolean update(Entity model);
    boolean delete(Entity model);
}
