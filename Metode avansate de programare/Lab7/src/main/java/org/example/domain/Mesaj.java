package org.example.domain;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Mesaj extends Entity<Tuple<Long, Long>> {
    private Long idExpeditor;
    private String text;
    private LocalDateTime dataTrimitere;
    private Long repliesTo;
    private List<Long> sendTo = new ArrayList<>();

    public Mesaj(Long idExpeditor, String text) {
        this.idExpeditor = idExpeditor;
        this.text = text;
        this.repliesTo = null;
        this.dataTrimitere = LocalDateTime.now();
    }

    public Mesaj(Long idExpeditor, String text, LocalDateTime dataTrimitere) {
        this(idExpeditor,text);
        this.dataTrimitere = dataTrimitere;
    }

    public Mesaj(Long idExpeditor, String text, Long repliesTo) {
        this(idExpeditor,text);
        this.repliesTo = repliesTo;
    }

    public Mesaj(Long idExpeditor, String text, Long repliesTo, LocalDateTime dataTrimitere) {
        this(idExpeditor, text, repliesTo);
        this.dataTrimitere = dataTrimitere;
    }

    public Long getIdExpeditor() {
        return idExpeditor;
    }

    public void setIdExpeditor(Long idExpeditor) {
        this.idExpeditor = idExpeditor;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public LocalDateTime getDataTrimitere() {
        return dataTrimitere;
    }

    public void setDataTrimitere(LocalDateTime dataTrimitere) {
        this.dataTrimitere = dataTrimitere;
    }

    public Long getRepliesTo() {
        return repliesTo;
    }

    public void setRepliesTo(Long repliesTo) {
        this.repliesTo = repliesTo;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Mesaj mesaj = (Mesaj) o;
        return Objects.equals(mesaj.id.getLeft(), this.id.getLeft());
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), idExpeditor, text, dataTrimitere, repliesTo);
    }

    @Override
    public String toString() {
        if (this.repliesTo == null)
            return this.text;
        return "repl : " + text;
    }

    public List<Long> getSendTo() {
        return sendTo;
    }

    public void addSendTo(Long sendTo) {
        this.sendTo.add(sendTo);
    }
    public void rmSendTo(Long sendTo) {
        this.sendTo.remove(sendTo);
    }
    public boolean esteDestinatar(Long id_ut) {
        return this.sendTo.contains(id_ut);
    }

}
