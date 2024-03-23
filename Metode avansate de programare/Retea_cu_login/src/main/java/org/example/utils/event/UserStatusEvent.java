package org.example.utils.event;

import org.example.domain.Utilizator;

public class UserStatusEvent implements Event {
    private StatusEventType type;
    private Utilizator utilizator;
    public UserStatusEvent(StatusEventType type, Utilizator utilizator) {
        this.utilizator = utilizator;
        this.type = type;
    }

    public Utilizator getUser() {
        return utilizator;
    }

    public void setUser(Utilizator utilizator) {
        this.utilizator = utilizator;
    }

    public StatusEventType getType() {
        return type;
    }

    public void setType(StatusEventType type) {
        this.type = type;
    }
}
