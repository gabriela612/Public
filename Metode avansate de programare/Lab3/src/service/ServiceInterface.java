package service;

import domain.Prietenie;
import domain.Utilizator;

import java.util.Optional;

public interface ServiceInterface {

    public Optional<Utilizator> addUtilizator(String firstName, String lastName);
    public Optional<Prietenie> addPrietenie(Long id1, Long id2);
    public Optional<Utilizator> rmUtilizator(Long id);
    public Optional<Prietenie> rmPrietenie(Long id1, Long id2);


}
