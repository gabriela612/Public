package org.example.ui;

import org.example.service.Service;

import java.util.Scanner;

public class UI implements UIInterface{

    Service service;
    public UI() {
        this.service = new Service(null, null, null);
    }
    public UI(Service service) {
        this.service = service;
    }

    public void adaugaUtilizator() {
        System.out.print("Firstname : ");
        Scanner scanner = new Scanner(System.in);
        String firstName = scanner.nextLine();
        System.out.print("Lastname : ");
        String lastName = scanner.nextLine();
        try {
            if (service.addUtilizator(firstName, lastName).isEmpty())
                System.out.println("Adaugarea nu s-a putut efectua.");
            else
                System.out.println("Adaugarea s-a efectuat cu succes.");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void adaugaPrietenie() {
        System.out.print("Id utilizator1 : ");
        Scanner scanner = new Scanner(System.in);
        Long id1 = scanner.nextLong();
        System.out.print("Id utilizator2 : ");
        Long id2 = scanner.nextLong();
        try {
            if (service.addPrietenie(id1, id2).isEmpty())
                System.out.println("Adaugarea nu s-a putut efectua.");
            else
                System.out.println("Adaugarea s-a efectuat cu succes.");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void stergeUtilizator() {
        System.out.print("Id utilizator : ");
        Scanner scanner = new Scanner(System.in);
        Long id = scanner.nextLong();
        try {
            service.rmUtilizator(id);
            System.out.println("Stergerea s-a efecuat cu succes.");

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void stergePrietenie() {
        System.out.print("Id utilizator1 : ");
        Scanner scanner = new Scanner(System.in);
        Long id1 = scanner.nextLong();
        System.out.print("Id utilizator2 : ");
        Long id2 = scanner.nextLong();
        try {
            service.rmPrietenie(id1, id2);
            System.out.println("Stergerea s-a efectuat cu succes.");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void numarulDeComunitati() {
        System.out.println("Numarul de comunitati este : " + this.service.numarDeComunitati());
    }

    public void ceaMaiSociabilaComunitate() {
        System.out.print("Cea mai sociabila comunitate : ");
        service.ceaMaiSociabilaComunitate().forEach(i -> System.out.print(i.getFullName() + ", "));
//        for (var i : service.ceaMaiSociabilaComunitate()) {
//            System.out.print(i.getFullName() + ", ");
//        }
        System.out.println(" ");
    }

    @Override
    public int citireCerinta() {
        try {
            System.out.print("Introduceti cerinta : ");
            Scanner scanner = new Scanner(System.in);
            int cerinta = scanner.nextInt();
            return cerinta;
        } catch (Exception e) {
            System.out.println(e);
            return citireCerinta();
        }
    }

    @Override
    public void apelareCerinta(int cerinta) {
        switch (cerinta) {
            case 1: {
                afisareUtilizatori();
                break;
            }
            case 2: {
                adaugaUtilizator();
                break;
            }
            case 3: {
                adaugaPrietenie();
                break;
            }
            case 4: {
                stergeUtilizator();
                break;
            }
            case 5: {
                stergePrietenie();
                break;
            }
            case 6: {
                numarulDeComunitati();
                break;
            }
            case 7: {
                ceaMaiSociabilaComunitate();
                break;
            }
            case 8: {
                afisarePrieteni();
                break;
            }
        }
    }

    @Override
    public void afisareUtilizatori() {
        System.out.println(service);
    }

    public void afisarePrieteni() {
        System.out.print("Id utilizator : ");
        Scanner scanner = new Scanner(System.in);
        Long id = scanner.nextLong();
        System.out.print("Luna : ");
        Integer luna = scanner.nextInt();
        if (luna < 1 || luna > 12) {
            System.out.println("Luna trebuie sa fie intre 1 si 12.");
            return;
        }
        System.out.println("\nPrietenii utilizatorului facuti in luna data sunt : ");
        System.out.println(service.afisarePrieteni(id, luna));
    }

    @Override
    public void afisareMeniu() {
        System.out.println("0. Exit.");
        System.out.println("1. Afisarea listei de utilizatori.");
        System.out.println("2. Adaugarea unui utilizator.");
        System.out.println("3. Adaugarea unei prietenii.");
        System.out.println("4. Stergerea unui utilizator.");
        System.out.println("5. Stergerea unei prietenii.");
        System.out.println("6. Numarul de comunitati.");
        System.out.println("7. Cea mai sociabila comunitate.");
        System.out.println("8. Afisarea prietenilor unui utilizator dintr-o anumita luna.");
    }

    @Override
    public void start() {
        int cerinta;
        while (Boolean.TRUE) {
            afisareMeniu();
            cerinta = citireCerinta();
            if (cerinta == 0) {
                break;
            }
            else {
                apelareCerinta(cerinta);
            }
        }
    }
}
