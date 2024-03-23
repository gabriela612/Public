package org.example.service.grafuri;

import org.example.domain.Entity;

import java.util.List;
import java.util.Map;
import java.util.function.Function;

public class ComponenteConexe {
    public static Long nrComponenteConexe(List<Entity<Long>> all, Map<Long, Boolean> vizitati, Function<Entity<Long>, List<Entity<Long>>> getVecini) {
        ParcurgereInAdancime parcurgere = new ParcurgereInAdancime();
        Long nrDeComponenteConexe = 0l;
        Entity<Long> entity = primulNevizitat(all, vizitati);
        while (entity != null) {
            nrDeComponenteConexe++;
            parcurgere.parcurge(entity, all, vizitati, getVecini);
            entity = primulNevizitat(all, vizitati);
        }
        return nrDeComponenteConexe;
    }
    private static Entity<Long> primulNevizitat(List<Entity<Long>> all, Map<Long, Boolean> vizitati) {

        for (Entity<Long> i : all) {
            if (vizitati.get(i.getId()) == Boolean.FALSE) {
                vizitati.put(i.getId(), Boolean.TRUE);
                return i;
            }
        }
        return null;
    }

    public static void ceaMaiSociabilaComunitate(List<Entity<Long>> all, Map<Long,
            Boolean> vizitati, Function<Entity<Long>, List<Entity<Long>>> getVecini) {
        int[] drum = {0};
        Entity<Long>[] inceputRezultat = new Entity[1];
        inceputRezultat[0] = null;
        ParcurgereInAdancime parcurgere = new ParcurgereInAdancime();
        all.forEach(i -> {
            all.forEach(utilizator -> vizitati.put(utilizator.getId(), Boolean.FALSE));
            vizitati.put(i.getId(), Boolean.TRUE);
            int drumCurent = parcurgere.parcurge(i, all, vizitati, getVecini);
            if (drumCurent > drum[0]) {
                drum[0] = drumCurent;
                inceputRezultat[0] = i;
            }
        });
        all.forEach(utilizator -> vizitati.put(utilizator.getId(), Boolean.FALSE));
        vizitati.put(inceputRezultat[0].getId(), Boolean.TRUE);
        parcurgere.parcurge(inceputRezultat[0], all, vizitati, getVecini);
//        for (var i : all) {
//            for (Entity<Long> ut : all) {
//                vizitati.put(ut.getId(), Boolean.FALSE);
//            }
//            vizitati.put(i.getId(), Boolean.TRUE);
//            int drumCurent = parcurgere.parcurge(i, all, vizitati, getVecini);
//            if (bfs_rez > drum[0]) {
//                drum[0] = bfs_rez;
//                rez = i;
//            }
//        }
//        for (Utilizator ut : all) {
//            vizitati.put(ut.getId(), Boolean.FALSE);
//        }
//        vizitati.put(rez.getId(), Boolean.TRUE);
//        return bfs_list(rez, all, vizitati);
    }
}
