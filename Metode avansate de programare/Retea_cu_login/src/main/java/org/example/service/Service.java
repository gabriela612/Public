package org.example.service;

import org.example.domain.*;
import org.example.domain.StarePrietenie;
import org.example.domain.validators.IsNullException;
import org.example.domain.validators.NotFoundException;
import org.example.domain.validators.ValidatorFactory;
import org.example.domain.validators.ValidatorStrategy;
import org.example.repository.InMemoryRepository;
import org.example.repository.MesajDBRepository;
import org.example.repository.Repository;
import org.example.repository.paging.Page;
import org.example.repository.paging.Pageable;
import org.example.repository.paging.PagingRepository;
import org.example.service.grafuri.Neabstractizare;
import org.example.service.grafuri.ComponenteConexe;
import org.example.utils.event.*;
import org.example.utils.observer.Observable;
import org.example.utils.observer.Observer;

import java.sql.SQLException;
import java.time.LocalDateTime;
import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Service implements ServiceInterface, Observable<Event> {
    private List<Observer<Event>> observers = new ArrayList();
    Repository<Long, Utilizator> repoUtilizatori;
    Repository<Tuple<Long, Long>, Prietenie> repoPrietenie;
    Repository<Tuple<Long, Long>, Mesaj> repoMesaje;
    private static java.lang.Long ut_id = 1L;
    private static java.lang.Long pr_id = 1L;
    public Service(Repository utilizatori, Repository prietenie, Repository mesaje) {
        repoUtilizatori = utilizatori;
        repoPrietenie  = prietenie;
        repoMesaje = mesaje;
    }

    /**
     * @param firstName - prenumele utilizatorului ce urmeaza sa fie creat
     * @param lastName  - numele utilizatorului ce urmeaza sa fie creat
     * @return utilizatorul nou creat
     */
    public Optional<Utilizator> addUtilizator(String firstName, String lastName, String parola) throws SQLException {
        Utilizator new_utilizator = new Utilizator(firstName, lastName, parola);
//        new_utilizator.setId(ut_id);
//        ut_id ++;
        Optional<Utilizator> ut_rez = this.repoUtilizatori.save(new_utilizator);
        if(ut_rez.isPresent()) {
            notifyObservers(new UsersChangeEvent(UserChangeEventType.ADD, ut_rez.get()));
        }
        return ut_rez;
    }

    public Optional<Utilizator> updateUtilizator(String firstName, String lastName, Long id, String parola) throws SQLException {
        Utilizator new_utilizator = new Utilizator(firstName, lastName, parola);
        new_utilizator.setId(id);
//        new_utilizator.setId(ut_id);
//        ut_id ++;
        Optional<Utilizator> ut_vechi = this.repoUtilizatori.findOne(id);
        Optional<Utilizator> ut_rez = this.repoUtilizatori.update(new_utilizator);
        if(ut_rez.isPresent()) {
            notifyObservers(new UsersChangeEvent(UserChangeEventType.UPDATE, ut_rez.get(), ut_vechi.get()));
        }
        return ut_rez;
    }

    public String afisarePrieteni(Long id, int luna) {

        HashSet<Prietenie> all = (HashSet<Prietenie>) this.repoPrietenie.findAll();
        String s = all.stream()
                .filter(prietenie -> {
            if ((prietenie.getId().getLeft() == id || prietenie.getId().getRight() == id) &&
            luna == prietenie.getDate().getMonthValue())
                return true;
            return false;
        })
                .map(prietenie -> {
                    Long idp;
                    if (prietenie.getId().getLeft() != id)
                        idp = prietenie.getId().getLeft();
                    else
                        idp = prietenie.getId().getRight();
                    Utilizator pr = this.repoUtilizatori.findOne(idp).get();
                    return new Tuple<Utilizator, LocalDateTime>(pr, prietenie.getDate());
                })
                                .reduce("",
                                        (rezPartial, tuplu) -> rezPartial +
                                                tuplu.getLeft().getFullName() +
                                                " " + tuplu.getRight().toString() + "\n"
                                        , String::concat);

        return s;
    }


    /**
     * @param id1 - id-ul primului prieten
     * @param id2 - id-ul celui de-al doilea prieten
     * @return prietenia creata, daca nu exista deja o prietenie intre cei doi utilizatori
     * @return prietenia prietenia deja existenta, daca exista deja o prietenie intre cei doi utilizatori
     * @throws IsNullException   daca id1 sau id2 e null
     * @throws NotFoundException daca nu se gaseste cel putin un utilizator
     */

    public Optional<Prietenie> addPrietenie(Long id1, Long id2) throws SQLException {
        if (id1 == null || id2 == null) {
            throw new IsNullException("Id null");
        }
        Optional<Utilizator> u1 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id1);
        Optional<Utilizator> u2 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id2);
        if (u1.isEmpty() || u2.isEmpty()) {
            throw new NotFoundException("Unul dintre utilizatori nu a fost gasit");
        }
        if (repoPrietenie.findOneExact(new Tuple<Long, Long>(id1, id2)).isPresent()) {
            if (repoPrietenie.findOneExact(new Tuple<Long, Long>(id1, id2)).get().getStare() !=
                    StarePrietenie.rejected)
                return (Optional<Prietenie>) repoPrietenie.findOneExact(new Tuple<Long, Long>(id1, id2));
            else
                this.updatePrietenie(id1, id2, LocalDateTime.now(), StarePrietenie.pending);
        }
//        if (repoPrietenie.findOne(new Tuple<Long, Long>(id2, id1)).isPresent() &&
//                repoPrietenie.findOne(new Tuple<Long, Long>(id1, id2)).get().getId().getLeft() == id1)
//            if (repoPrietenie.findOne(new Tuple<Long, Long>(id2, id1)).get().getStare() !=
//            StarePrietenie.rejected)
//                return (Optional<Prietenie>) repoPrietenie.findOne(new Tuple<Long, Long>(id1, id2));
//            else
//                this.updatePrietenie(id1, id2, LocalDateTime.now(), StarePrietenie.pending);

        Prietenie prietenie = new Prietenie(u1.get(), u2.get());

        Optional<Prietenie> pr_rez = this.repoPrietenie.save(prietenie);
        if(pr_rez.isPresent()) {
            notifyObservers(new PrieteniChangeEvent(PrietenChangeEventType.ADD, pr_rez.get()));
        }
        return pr_rez;
    }

    public Optional<Prietenie> updatePrietenie(Long id1, Long id2, LocalDateTime data, StarePrietenie stare) throws SQLException {

        if (id1 == null || id2 == null) {
            throw new IsNullException("Id null");
        }
        Optional<Utilizator> u1 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id1);
        Optional<Utilizator> u2 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id2);
        if (u1.isEmpty() || u2.isEmpty()) {
            throw new NotFoundException("Unul dintre utilizatori nu a fost gasit");
        }

        Prietenie new_prietenie = new Prietenie(id1, id2, data, stare);
        Tuple<Long, Long> id = new Tuple<>(id1, id2);

        if (this.repoPrietenie.findOneExact(id).isEmpty())
            throw new NotFoundException("Prietenia nu a fost gasita");

        new_prietenie.setId(id);
//        new_utilizator.setId(ut_id);
//        ut_id ++;
        Optional<Prietenie> pr_veche = this.repoPrietenie.findOneExact(id);
        Optional<Prietenie> pr_rez = this.repoPrietenie.update(new_prietenie);
        if(pr_rez.isPresent()) {
            notifyObservers(new PrieteniChangeEvent(PrietenChangeEventType.UPDATE, pr_rez.get(), pr_veche.get()));
        }
        return pr_rez;
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

        Optional<Utilizator> ut_rez = this.repoUtilizatori.delete(id);
        if(ut_rez.isPresent()) {
            notifyObservers(new UsersChangeEvent(UserChangeEventType.DELETE, ut_rez.get()));
        }
        return ut_rez;
    }

    public Optional<Prietenie> rmPrietenie(Long id1i, Long id2i) {
        if (id1i == null || id2i == null) {
            throw new IsNullException("Id null");
        }
//        Long id1 = Math.min(id1i, id2i);
//        Long id2 = Math.max(id1i, id2i);
        Optional<Utilizator> u1 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id1i);
        Optional<Utilizator> u2 = (Optional<Utilizator>) this.repoUtilizatori.findOne(id2i);
        if (u1.isEmpty() || u2.isEmpty()) {
            throw new NotFoundException("Unul dintre utilizatori nu a fost gasit");
        }
//        Long id1f = Math.min(id1, id2);
//        Long id2f = Math.max(id1, id2);
        if (((Optional<Prietenie>) this.repoPrietenie.findOne(new Tuple<>(id1i, id2i))).isEmpty()) {
            throw new NotFoundException("Prietenia nu a fost gasita");
        }
        Optional<Prietenie> prietenie = (Optional<Prietenie>) this.repoPrietenie.delete(new Tuple<Long, Long>(id1i, id2i));
//        if (prietenie.isEmpty()) {
//            prietenie = (Optional<Prietenie>) this.repoPrietenie.findOne(new Tuple<>(id2i, id1));
//        }
        //prietenie.get().rmFriend(u1.get(), u2.get());

        if(prietenie.isPresent()) {
            notifyObservers(new PrieteniChangeEvent(PrietenChangeEventType.DELETE, prietenie.get()));
        }

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

    public Iterable<Utilizator> findAllUsers() {
        return repoUtilizatori.findAll();
    }

    public Page<Utilizator> findAllUsers(Pageable pageable) {
        return ((PagingRepository) repoUtilizatori).findAll(pageable);
    }

    public Iterable<Tuple<Utilizator, Prietenie>> findAllPrieteni(Long id) {
        HashSet<Prietenie> all = (HashSet<Prietenie>) this.repoPrietenie.findAll();
        List<Tuple<Utilizator, Prietenie>> rez = all.stream()
                .filter(prietenie -> {
                    if (prietenie.getId().getLeft() == id || prietenie.getId().getRight() == id)
                        return true;
                    return false;
                })
                .map(prietenie -> {
                    Long idp;
                    if (prietenie.getId().getLeft() != id)
                        idp = prietenie.getId().getLeft();
                    else
                        idp = prietenie.getId().getRight();
                    Utilizator pr = this.repoUtilizatori.findOne(idp).get();
                    return new Tuple<Utilizator, Prietenie>(pr, prietenie);
                })
                .collect(Collectors.toList());

        return rez;
    }

    @Override
    public void addObserver(Observer<Event> listener) {
        this.observers.add(listener);
    }

    @Override
    public void removeObserver(Observer<Event> listener) {
        this.observers.remove(listener);
    }

    @Override
    public void notifyObservers(Event t) {
        observers.forEach(o -> { o.update(t); });
    }

    public Optional<Mesaj> addMesaj(Long idExpeditor, List<Long> sendTo, String text, Long repliesTo)
            throws SQLException {
        if (idExpeditor == null || sendTo.size() == 0 || text == "") {
            throw new IsNullException("Date insuficiente");
        }

        if (repliesTo != null && (repoMesaje.findOne(new Tuple<>(repliesTo, null)).isEmpty()))
            throw new NotFoundException("Nu s-a gasit mesajul la care se da reply.");
        Mesaj reply = null;
        if (repliesTo != null) {
            reply = repoMesaje.findOne(new Tuple<>(repliesTo, null)).get();
            if (!reply.esteDestinatar(idExpeditor) && (!reply.esteDestinatar(sendTo.get(0)) || sendTo.size() > 1))
                throw new NotFoundException("Nu s-a gasit mesajul la care se da reply.");
        }

        Mesaj mesaj = new Mesaj(idExpeditor, text, repliesTo);
        sendTo.forEach(mesaj::addSendTo);

        Optional<Mesaj> msg_rez = this.repoMesaje.save(mesaj);
        if(msg_rez.isPresent()) {
            notifyObservers(new MesajeChangeEvent(MesajChangeEventType.ADD, msg_rez.get()));
        }
        return msg_rez;
    }

    public Optional<Mesaj> rmMesaj(Long id_mesaj, Long id_ut_dest) {
        if (id_mesaj == null || id_ut_dest == null) {
            throw new IsNullException("Cel putin un id este null");
        }
        Tuple<Long, Long> id = new Tuple<>(id_mesaj, id_ut_dest);
        if (((Optional<Mesaj>)this.repoMesaje.findOne(id)).isEmpty()) {
            throw new NotFoundException("Nu s-a gasit un mesaj cu id-ul dat");
        }

        Optional<Mesaj> msg_rez = this.repoMesaje.delete(id);
        if(msg_rez.isPresent()) {
            notifyObservers(new MesajeChangeEvent(MesajChangeEventType.DELETE, msg_rez.get()));
        }
        return msg_rez;
    }

    public Iterable<Mesaj> findAllMesaje(Long id_ut1, Long id_ut2) {
        HashSet<Mesaj> all = new HashSet<>();
        this.repoMesaje.findAll().forEach(all::add);
        List<Mesaj> rez = all.stream()
                .filter(mesaj -> {
                    if (mesaj.getIdExpeditor() == id_ut1 && mesaj.esteDestinatar(id_ut2))
                        return true;
                    if (mesaj.getIdExpeditor() == id_ut2 && mesaj.esteDestinatar(id_ut1))
                        return true;
                    return false;
                })
                .collect(Collectors.toList());

        return rez;
    }

    public Optional<Utilizator> findUser(Long id) {
        return this.repoUtilizatori.findOne(id);
    }
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
//}
