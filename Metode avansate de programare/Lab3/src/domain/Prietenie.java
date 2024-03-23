package domain;

import domain.validators.IsNullException;

import java.time.LocalDateTime;


public class Prietenie extends Entity<Tuple<Long,Long>> {
    LocalDateTime friendsFrom;

    /**
     * creeaza o prieteie si il adauga ut1 in lista de prieteni a lui ut2 si pe ut2 in lista de prieteni a lui ut1
     * @param ut1 - primul prieten
     * @param ut2 - al doilea prieten
     * @throws IsNullException daca cel putin un utilizator sau id de utilizator e null
     */
    public Prietenie(Utilizator ut1, Utilizator ut2) {
        if (ut1 == null || ut2 == null)
            throw new IsNullException("Cel putin un utilizator este null");
        if (ut1.getId() == null || ut2.getId() == null)
            throw new IsNullException("Cel putin un utilizator are id-ul null");
        this.friendsFrom = LocalDateTime.now();
//        Long id1 = Math.min(ut1.getId(), ut2.getId());
//        Long id2 = Math.max(ut1.getId(), ut2.getId());
        setId(new Tuple<Long, Long>(ut1.getId(), ut2.getId()));
        addFriend(ut1, ut2);
    }

    /**
     * il adauga ut1 in lista de prieteni a lui ut2 si pe ut2 in lista de prieteni a lui ut1
     * @param ut1 - primul prieten
     * @param ut2 - al doilea prieten
     */
    public void addFriend(Utilizator ut1, Utilizator ut2) {
        ut1.addFriend(ut2);
        ut2.addFriend(ut1);
    }

    /**
     * il sterge pe ut1 din lista de prieteni a lui ut2 si pe ut2 din lista de prieteni a lui ut1
     * @param ut1 - primul prieten
     * @param ut2 - al doilea prieten
     * @throws IsNullException daca cel putin un utilizator sau id de utilizator e null
     */
    public void rmFriend(Utilizator ut1, Utilizator ut2) {
        if (ut1 == null || ut2 == null)
            throw new IsNullException("Cel putin un utilizator este null");
        if (ut1.getId() == null || ut2.getId() == null)
            throw new IsNullException("Cel putin un utilizator are id-ul null");

        ut1.rmFriend(ut2);
        ut2.rmFriend(ut1);
    }

    /**
     *
     * @return the date when the friendship was created
     */
    public LocalDateTime getDate() {
        return friendsFrom;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator)) return false;
        Prietenie that = (Prietenie) o;
        if (that.getId() == null) {
            return false;
        }
        Long id1 = that.getId().getLeft();
        Long id2 = that.getId().getRight();
        if (id1 == null || id2 == null) {
            return false;
        }
        if (id1.equals(this.getId().getLeft()) && id2.equals(this.getId().getRight())) {
            return true;
        }
        if (id2.equals(this.getId().getLeft()) && id1.equals(this.getId().getRight())) {
            return true;
        }
        return false;
    }
}
