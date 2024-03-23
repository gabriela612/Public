package org.example.utils.event;

import org.example.domain.Mesaj;
import org.example.domain.Utilizator;

public class MesajeChangeEvent implements Event {
    private MesajChangeEventType type;
    private Mesaj data, oldData;

    public MesajeChangeEvent(MesajChangeEventType type, Mesaj data) {
        this.type = type;
        this.data = data;
    }
    public MesajeChangeEvent(MesajChangeEventType type, Mesaj data, Mesaj oldData) {
        this.type = type;
        this.data = data;
        this.oldData = oldData;
    }

    public MesajChangeEventType getType() {
        return type;
    }

    public Mesaj getData() {
        return data;
    }

    public Mesaj getOldData() {
        return oldData;
    }
}
