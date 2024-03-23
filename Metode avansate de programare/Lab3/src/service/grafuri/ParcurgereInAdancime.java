package service.grafuri;

import domain.Entity;
import domain.Utilizator;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.function.Function;

public class ParcurgereInAdancime implements ParcurgereComponentaConexa{
    @Override
    public int parcurge(Entity<Long> inceput, List<Entity<Long>> all, Map<Long, Boolean> vizitati, Function<Entity<Long>, List<Entity<Long>>> getVecini) {
        ArrayList<Entity<Long>> coada = new ArrayList<>();
        int st = 0;
        int dr = 1;
        int drum = 0;
        vizitati.put(inceput.getId(), Boolean.TRUE);
        coada.add(inceput);
        while(st < dr) {
            Entity<Long> nod = coada.get(st);
            st ++;

            List<Entity<Long>> vecini = getVecini.apply(nod);
            vecini.forEach(i -> {
                if (vizitati.get(i.getId()) == Boolean.FALSE) {
                    vizitati.put(i.getId(), Boolean.TRUE);
                    coada.add(i);
                }
            });
//            for (Entity<Long> i : vecini) {
//                if (vizitati.get(i.getId()) == Boolean.FALSE) {
//                    vizitati.put(i.getId(), Boolean.TRUE);
//                    coada.add(i);
//                }
//            }
            if (st >= dr) {
                drum ++;
                dr = coada.size();
            }
        }
        return drum;
    }
}
