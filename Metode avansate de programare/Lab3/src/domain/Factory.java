package domain;

public interface Factory<T,S> {
    public T create(S strategy);
}
