package org.example.utils.event;

import org.example.domain.Utilizator;
import org.w3c.dom.Entity;

public class EntityChangeEvent implements Event{
    private EntityChangeEvent type;
    private Entity data, oldData;

    public EntityChangeEvent(EntityChangeEvent type, Entity data) {
        this.type = type;
        this.data = data;
    }

    public EntityChangeEvent getType() {
        return type;
    }

    public Entity getData() {
        return data;
    }

    public Entity getOldData() {
        return oldData;
    }

    public EntityChangeEvent(EntityChangeEvent type, Entity data, Entity oldData) {
        this.type = type;
        this.data = data;
        this.oldData = oldData;
    }
}
