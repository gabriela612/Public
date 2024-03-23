package org.example.domain;

public interface Factory<T,S> {
    public T create(S strategy);
}
