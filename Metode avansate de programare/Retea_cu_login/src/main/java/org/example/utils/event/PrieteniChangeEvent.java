package org.example.utils.event;

import org.example.domain.Prietenie;

public class PrieteniChangeEvent implements Event{
    private PrietenChangeEventType type;
    private Prietenie data, oldData;

    public PrieteniChangeEvent(PrietenChangeEventType type, Prietenie data) {
        this.type = type;
        this.data = data;
    }

     public PrieteniChangeEvent(PrietenChangeEventType type, Prietenie data, Prietenie oldData) {
         this.type = type;
         this.data = data;
         this.oldData = oldData;
     }

    public PrietenChangeEventType getType() {
        return type;
    }

    public Prietenie getData() {
        return data;
    }

    public Prietenie getOldData() {
        return oldData;
    }
}
