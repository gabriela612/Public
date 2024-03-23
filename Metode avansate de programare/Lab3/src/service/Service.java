package service;

import domain.Prietenie;
import domain.Tuple;
import domain.Utilizator;
import domain.validators.IsNullException;
import domain.validators.NotFoundException;
import domain.validators.ValidatorFactory;
import domain.validators.ValidatorStrategy;
import repository.InMemoryRepository;
import repository.Repository;
import service.grafuri.Neabstractizare;
import service.grafuri.ComponenteConexe;

import java.util.*;
import java.util.function.Function;

public class Service implements ServiceInterface {
    Repository<Long, Utilizator> repoUtilizatori;
    Repository<Tuple<Long, Long>, Prietenie> repoPrietenie;
    private static java.lang.Long ut_id = 1L;
    private static java.lang.Long pr_id = 1L;
    public Service(Repository utilizatori,Repository prietenie) {
        repoUtilizatori = utilizatori;
        repoPrietenie  = prietenie;
    }
    public Service() {
        Repository repoUtilizatori = new
                InMemoryRepository<java.lang.Long, Utilizator>
                (ValidatorFactory.getInstance().create(ValidatorStrategy.utilizator));
        Repository repoPrietenie  = new
                InMemoryRepository<Tuple<java.lang.Long, java.lang.Long>, Prietenie>
                (ValidatorFactory.getInstance().create(ValidatorStrategy.prietenie));
    }

    /**
     * @param firstName - prenumele utilizatorului ce urmeaza sa fie creat
     * @param lastName  - numele utilizatorului ce urmeaza sa fie creat
     * @return utilizatorul nou creat
     */
    public Optional<Utilizator> addUtilizator(String firstName, String lastName) {
        Utilizator new_utilizator = new Utilizator(firstName, lastName);
        new_utilizator.setId(ut_id);
        ut_id ++;
        return (Optional<Utilizator>) this.repoUtilizatori.save(new_utilizator);
    }

    /**
     * @param id1 - id-ul primului prieten
     * @param id2 - id-ul celui de-al doilea prieten
     * @return prietenia creata, daca nu exista deja o prietenie intre cei doi utilizatori
     * @return prietenia prietenia deja existenta, daca exista deja o prietenie intre cei doi utilizatori
     * @throws IsNullException   daca id1 sau id2 e null
     * @throws NotFoundException daca nu se gaseste cel putin un utilizator
     */
    public Optional<Prietenie> addPrietenie(Long id1, Long id2) {
        if (id1 == null || id2 == null) {
            throw new IsNullException("Id null");
        }
        Optional<Utilizator> u1 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id1);
        Optional<Utilizator> u2 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id2);
        if (u1.isEmpty() || u2.isEmpty()) {
            throw new NotFoundException("Unul dintre utilizatori nu a fost gasit");
        }
        if (repoPrietenie.findOne(new Tuple<Long, Long>(id1, id2)).isPresent() ||
                repoPrietenie.findOne(new Tuple<Long, Long>(id2, id1)).isPresent()) {
            return (Optional<Prietenie>) repoPrietenie.findOne(new Tuple<Long, Long>(id1, id2));
        }
        Prietenie prietenie = new Prietenie(u1.get(), u2.get());
        return (Optional<Prietenie>) this.repoPrietenie.save(prietenie);
    }

    /**
     * @param id - id-ul utilizatorului pe care il stergem
     * @return utilizatorul sters, daca a existat in lista de utilizatori
     * @return null, daca utilizatorul cu id-ul dat nu exista in lista de utilizatori
     * @throws IsNullException   daca id-ul este null
     * @throws NotFoundException daca nu s-a gasit utilizatorul cu id-ul dat
     */
    public Optional<Utilizator> rmUtilizator(Long id) {
        if (id == null) {
            throw new IsNullException("Id-ul este null");
        }
        if (((Optional<Utilizator>)this.repoUtilizatori.findOne(id)).isEmpty()) {
            throw new NotFoundException("Nu s-a gasit un utilizator cu id-ul dat");
        }
        var idPrieteni = ((Optional<Utilizator>)this.repoUtilizatori.findOne(id)).get().getIdFriends();
        idPrieteni.forEach(i -> rmPrietenie(id, i));
//        for (var i : idPrieteni) {
//            rmPrietenie(id, i);
//        }

//        for (Utilizator i : ((Utilizator)this.repoUtilizatori.findOne(id)).getFriends()) {
//            rmPrietenie(id, i.getId());
//            System.out.println(i.getId() + "*");
//            //System.out.println("(" + u1.getId() + ", " + u2.getId() + ")");
//        }
        return (Optional<Utilizator>) this.repoUtilizatori.delete(id);
    }

    public Optional<Prietenie> rmPrietenie(Long id1, Long id2) {
        if (id1 == null || id2 == null) {
            throw new IsNullException("Id null");
        }
        Optional<Utilizator> u1 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id1);
        Optional<Utilizator> u2 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id2);
        if (u1.isEmpty() || u2.isEmpty()) {
            throw new NotFoundException("Unul dintre utilizatori nu a fost gasit");
        }
//        Long id1f = Math.min(id1, id2);
//        Long id2f = Math.max(id1, id2);
        if (((Optional<Prietenie>) this.repoPrietenie.findOne(new Tuple<>(id1, id2))).isEmpty() &&
                ((Optional<Prietenie>) this.repoPrietenie.findOne(new Tuple<>(id2, id1))).isEmpty()) {
            throw new NotFoundException("Prietenia nu a fost gasita");
        }
        Optional<Prietenie> prietenie = (Optional<Prietenie>) this.repoPrietenie.delete(new Tuple<Long, Long>(id1, id2));
        if (prietenie.isEmpty()) {
            prietenie = (Optional<Prietenie>) this.repoPrietenie.findOne(new Tuple<>(id2, id1));
        }
        prietenie.get().rmFriend(u1.get(), u2.get());
        return prietenie;
    }

    @Override
    public String toString() {
        return this.repoUtilizatori.toString();
    }


    public long numarDeComunitati() {
        List<Utilizator> all = new ArrayList<>();
        repoUtilizatori.findAll().forEach(all::add);
//        for (var i : repoUtilizatori.findAll()) {
//            all.add((Utilizator) i);
//        }
        Map<Long, Boolean> vizitati = new HashMap<>();
        all.forEach(utilizator -> vizitati.put(utilizator.getId(), Boolean.FALSE));
//        for (Utilizator i : all) {
//            vizitati.put(i.getId(), Boolean.FALSE);
//        }
        return ComponenteConexe.nrComponenteConexe(Neabstractizare.abstractizareListaUtilizatori(all),
                vizitati, Neabstractizare::getVecini);
        //return algoritmNrDeComunitati(all, vizitati);
    }

    public List<Utilizator> ceaMaiSociabilaComunitate() {
        List<Utilizator> all = new ArrayList<>();
        repoUtilizatori.findAll().forEach(all::add);
//        for (var i : repoUtilizatori.findAll()) {
//            all.add((Utilizator) i);
//        }
        Map<Long, Boolean> vizitati = new HashMap<>();
        all.forEach(utilizator -> vizitati.put(utilizator.getId(), Boolean.FALSE));
//        for (Utilizator i : all) {
//            vizitati.put(i.getId(), Boolean.FALSE);
//        }
        ComponenteConexe.ceaMaiSociabilaComunitate(Neabstractizare.abstractizareListaUtilizatori(all),
                vizitati, Neabstractizare::getVecini);

        Function<Map<Long, Boolean>, ArrayList<Utilizator>> iaVizitati = m -> {
            ArrayList<Utilizator> rezultat = new ArrayList<>();
            vizitati.entrySet().forEach(r -> {
                if (r.getValue() == Boolean.TRUE) {
                    Optional<Utilizator> utilizator = repoUtilizatori.findOne(r.getKey());
                    utilizator.ifPresent(rezultat::add);
                }
            });
            return rezultat;
        };
        return iaVizitati.apply(vizitati);
    }


//    private void dfs(Utilizator ut, List<Utilizator> all, Map<Long, Boolean> vizitati) {
//        // parcurgere componenta conexa - interfata functionala
//        // bfs si dfs sunt implementari
//        vizitati.put(ut.getId(), Boolean.TRUE);
//        List<Utilizator> prieteni = ut.getFriends();
//        for (Utilizator i : prieteni) {
//            if (vizitati.get(i.getId()) == Boolean.FALSE) {
//                vizitati.put(i.getId(), Boolean.TRUE);
//                dfs(i, all, vizitati);
//            }
//        }
//    }

//    private int bfs(Utilizator ut, List<Utilizator> all, Map<Long, Boolean> vizitati) {
//        ArrayList<Utilizator> coada = new ArrayList<>();
//        int st = 0;
//        int dr = 1;
//        int drum = 0;
//        vizitati.put(ut.getId(), Boolean.TRUE);
//        coada.add(ut);
//        while(st < dr) {
//            Utilizator utilizator = coada.get(st);
//            st ++;
//
//            List<Utilizator> prieteni = utilizator.getFriends();
//            for (Utilizator i : prieteni) {
//                if (vizitati.get(i.getId()) == Boolean.FALSE) {
//                    vizitati.put(i.getId(), Boolean.TRUE);
//                    coada.add(i);
//                }
//            }
//            if (st >= dr) {
//                drum ++;
//                dr = coada.size();
//            }
//        }
//        return drum;
//    }

//    private List<Utilizator> bfs_list(Utilizator ut, List<Utilizator> all, Map<Long, Boolean> vizitati) {
//        ArrayList<Utilizator> coada = new ArrayList<>();
//        ArrayList<Utilizator> rezultat = new ArrayList<>();
//        rezultat.add(ut);
//        vizitati.put(ut.getId(), Boolean.TRUE);
//        int st = 0;
//        int dr = 1;
//        coada.add(ut);
//        while(st < dr) {
//            Utilizator utilizator = coada.get(st);
//            st ++;
//            List<Utilizator> prieteni = utilizator.getFriends();
//            for (Utilizator i : prieteni) {
//                if (vizitati.get(i.getId()) == Boolean.FALSE) {
//                    vizitati.put(i.getId(), Boolean.TRUE);
//                    coada.add(i);
//                    rezultat.add(i);
//                }
//            }
//            if (st >= dr) {
//                dr = coada.size();
//            }
//        }
//        return rezultat;
//    }

//    private Utilizator primulNevizitat(List<Utilizator> all, Map<Long, Boolean> vizitati) {
//        for (Utilizator i : all) {
//            if (vizitati.get(i.getId()) == Boolean.FALSE) {
//                vizitati.put(i.getId(), Boolean.TRUE);
//                return i;
//            }
//        }
//        return null;
//    }

//    private Long algoritmNrDeComunitati(List<Utilizator> all, Map<Long, Boolean> vizitati) {
//        Long nrDeComunitati = 0l;
//        Utilizator ut = primulNevizitat(all, vizitati);
//        while (ut != null) {
//            nrDeComunitati ++;
//            dfs(ut, all, vizitati);
//            ut = primulNevizitat(all, vizitati);
//        }
//        return nrDeComunitati;
//    }



//    private List<Utilizator> algoritmCeaMaiSociabilaComunitate(List<Utilizator> all, Map<Long, Boolean> vizitati) {
//        Utilizator rez = new Utilizator("", "");
//        rez.setId(0L);
//        int drum = 0;
//        for (var i : all) {
//            for (Utilizator ut : all) {
//                vizitati.put(ut.getId(), Boolean.FALSE);
//            }
//            vizitati.put(i.getId(), Boolean.TRUE);
//            int bfs_rez = bfs(i, all, vizitati);
//            if (bfs_rez > drum) {
//                drum = bfs_rez;
//                rez = i;
//            }
//        }
//        for (Utilizator ut : all) {
//            vizitati.put(ut.getId(), Boolean.FALSE);
//        }
//        vizitati.put(rez.getId(), Boolean.TRUE);
//        return bfs_list(rez, all, vizitati);
//    }
}
