package org.example.repository;

import org.example.domain.Entity;
import org.example.domain.validators.IsNullException;
import org.example.domain.validators.Validator;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID,E> {
    private Validator<E> validator;
    Map<ID,E> entities;

    public InMemoryRepository(Validator<E> validator) {
        this.validator = validator;
        entities=new HashMap<ID,E>();
    }

    @Override
    public Optional<E> findOne(ID id){
        if (id==null)
            throw new IsNullException("id utilizatorului este null");
        return Optional.ofNullable(entities.get(id));
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

//    @Override
//    public E save(E entity) {
//        if (entity==null)
//            throw new IsNullException("entity must be not null");
//        validator.validate(entity);
//        if(entities.get(entity.getId()) != null) {
//            return entity;
//        }
//        else entities.put(entity.getId(),entity);
//        return null;
//    }
//
//    @Override
//    public E delete(ID id) {
//        if(id == null)
//            throw new IsNullException("entity must be not null!");
//
//        return this.entities.remove(id);
//    }

    @Override
    public Optional<E> save(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        validator.validate(entity);
        return Optional.ofNullable(entities.putIfAbsent(entity.getId(), entity));
    }
    @Override
    public Optional<E> delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("id must not be null");
        }
        return Optional.ofNullable(entities.remove(id));
    }


    @Override
    public Optional<E> update(E entity) {

        if(entity == null)
            throw new IsNullException("entity must be not null!");
        validator.validate(entity);

        entities.put(entity.getId(),entity);

        if(entities.get(entity.getId()) != null) {
            entities.put(entity.getId(),entity);
            return Optional.empty();
        }
        return Optional.ofNullable(entity);

    }


    @Override
    public String toString() {
//        return "InMemoryRepository{" +
//                " entities=" + entities +
//                '}';
        String rez = "";
        for (var i : entities.values()) {
            rez += i.toString() + "\n";
        }
        return rez;
    }
}
