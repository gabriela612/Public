package service.grafuri;

import domain.Entity;
import domain.Utilizator;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

public class Neabstractizare {
    public static List<Entity<Long>> getVecini(Entity entity) {
        if (entity instanceof Utilizator) {
            return abstractizareListaUtilizatori (((Utilizator) entity).getFriends());
        }
        return null;
    }
    public static List<Entity<Long>> abstractizareListaUtilizatori(List<Utilizator> lista) {
        Function<List<Utilizator>, List<Entity<Long>>> fct = utilizators -> {
            List<Entity<Long>> vecini = new ArrayList<>();
            vecini.addAll(utilizators);
            return vecini;
        };
        return fct.apply(lista);
    }
}
