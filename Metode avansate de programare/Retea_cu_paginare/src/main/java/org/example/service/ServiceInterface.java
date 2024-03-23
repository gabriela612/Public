package org.example.service;

import org.example.domain.Prietenie;
import org.example.domain.Utilizator;

import java.sql.SQLException;
import java.util.Optional;

public interface ServiceInterface {

    public Optional<Utilizator> addUtilizator(String firstName, String lastName) throws SQLException;
    public Optional<Prietenie> addPrietenie(Long id1, Long id2) throws SQLException;
    public Optional<Utilizator> rmUtilizator(Long id);
    public Optional<Prietenie> rmPrietenie(Long id1, Long id2);


}
