package org.example.utils.event;

import org.example.domain.Utilizator;
import org.example.utils.event.Event;

public class UsersChangeEvent implements Event {
    private UserChangeEventType type;
    private Utilizator data, oldData;

    public UsersChangeEvent(UserChangeEventType type, Utilizator data) {
        this.type = type;
        this.data = data;
    }
    public UsersChangeEvent(UserChangeEventType type, Utilizator data, Utilizator oldData) {
        this.type = type;
        this.data = data;
        this.oldData = oldData;
    }

    public UserChangeEventType getType() {
        return type;
    }

    public Utilizator getData() {
        return data;
    }

    public Utilizator getOldData() {
        return oldData;
    }
}
