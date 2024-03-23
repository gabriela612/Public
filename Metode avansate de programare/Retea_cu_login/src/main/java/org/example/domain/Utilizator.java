package org.example.domain;


import javax.swing.text.html.HTMLDocument;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

public class Utilizator extends Entity<Long> {
    private String firstName;
    private String lastName;
    private List<Utilizator> friends;
    private String parola;

    public void setFriends(List<Utilizator> friends) {
        this.friends = friends;
    }

    public String getParola() {
        return parola;
    }

    public void setParola(String parola) {
        this.parola = parola;
    }

    public Utilizator(String firstName, String lastName, String parola) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.parola = parola;
        this.friends = new ArrayList<>();
    }

    public int searchFriend(Utilizator friend) {
        return friends.indexOf(friend);
    }

    public void addFriend(Utilizator new_friend) {
        if (searchFriend(new_friend) == -1 && !new_friend.equals(this)) {
            this.friends.add(new_friend);
        }
    }

    public void rmFriend(Utilizator ex_friend) {
        this.friends.remove(ex_friend);
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getFullName() {
        return firstName + " " + lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public List<Utilizator> getFriends() {
        return friends;
    }

    public List<Long> getIdFriends() {
        List<Long> ids = new ArrayList<>();
        this.friends.forEach(f -> ids.add(f.getId()));
//        for (var i : friends) {
//            ids.add(i.getId());
//        }
        return ids;
    }

    public String getFriendsNames() {
        String[] friendsNames = new String[1];
        friendsNames[0] = "";
        this.friends.forEach(f -> {
            friendsNames[0] += "'" + f.getFullName() + "', ";
        });
//        for (var friend : this.friends) {
//            friendsNames[0] += "\'" + friend.getFirstName() + " " + friend.getLastName() + "\', ";
//        }
        return friendsNames[0];
    }

    @Override
    public String toString() {
        return "Id " + this.getId() +
                ", firstName = '" + firstName + '\'' +
                ", lastName = '" + lastName + '\'';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator)) return false;
        Utilizator that = (Utilizator) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName()) &&
                getFriends().equals(that.getFriends());
    }
    public boolean equalsName(Object o) {
        if (this == o) return true;
        if (!(o instanceof Utilizator)) return false;
        Utilizator that = (Utilizator) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName(), getFriends());
    }

}