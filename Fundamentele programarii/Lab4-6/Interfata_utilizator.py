import Validare_date
import Utile
import Iu

def Citire_gresita(er, t):
    '''
    - in aceasta afisam mesajele de eroare din t, cand utilizatorul introduce niste date incorecte
    :param t: ne spune locul in care a aparut eroarea pentru a afisa mesaje potrivite
        type : unsigned int
    :param er: lista cu mesajele pentru erori
        type : list
    :return: nu se returneaza nimic
    '''
    print(er[t])
    pass

def Afisare_nr_mesaj(rez, s):
    '''
    - in acesta functie afisam sirul de caractere s, apoi numarul complex rez in forma matematica
    :param rez: numarul complex
    type : list
    :param s: sirul de caractere (mesajul) care se afiseaza inainte de numarul complex
    '''
    print(s, Utile.real(rez), " + ", Utile.imaginar(rez), "i", sep='')
    print(sep=' ')
    pass

def Afisare_parte_imaginara(l):
    '''
    - in acesta funtie se afiseaza lista cu partiele imaginare l
    :param l: lista cu partile imaginare
    '''
    print("Partile imaginare ale numerelor din secventa data sunt : ", l)
    pass

def Citire_pozitie(mx, mesaj, er):
    '''
    - in acesta functie citim pozitia si o returnam
    :param mx: pozitia trebuie sa apartina de intervalul [1, mx]
        type : unsigned int
    :param mesaj: mesajul care se afiseaza la citire
        type : string
    :return: pozitia
    '''
    try:
        poz = int(input(mesaj))
        Validare_date.Validare_numar(poz, 1, mx)
        return poz
    except ValueError:
        Citire_gresita(er, 5)
        poz = Citire_pozitie(mx, mesaj, er)
        return poz

def Pozif(l, er):
    '''
    - acesta functie citeste si returneaza pozitia de inceput si de final a unei secvente
    '''
    try:
        pozi = Citire_pozitie(len(l) - 1, "Introduceti pozitia de inceput : ", er)
        pozf = Citire_pozitie(len(l) - 1, "Introduceti pozitia de final : ", er)
        Validare_date.Validare_pozitii(pozi, pozf)
    except ValueError:
        Citire_gresita(er, 6)
        pozi, pozf = Pozif(l, er)
    return pozi, pozf
    pass

def Citire_optiune(nro, er):
    '''
    - in acesta functie citim optiunea pe care o alege utilizatorul si o returnam
    :param nro: numarul de optiuni din care utilizatorul poate alege
        type : unsigned int
    :return: optiunea aleasa
    '''
    try:
        o = int(input("Introduceti optiunea : "))
        Validare_date.Validare_numar(o, 1, nro)
        return o
    except ValueError:
        Citire_gresita(er, nro)
        o = Citire_optiune(nro, er)
        return o
    pass

def Citire_numar_intreg(mesaj):
    '''
    - in aceasta functie citim un numar, afisand mesajul mesaj la citire
    :param mesaj: mesajul pe care il afisam la citire
        type : string
    :return: numarul citit
    '''
    nr = int(input(mesaj))
    return nr
    pass

def Citire_numar_nat(mesaj, er):
    '''
    - in aceasta functie citim un numar, afisand mesajul mesaj la citire
    :param mesaj: mesajul pe care il afisam la citire
        type : string
    :return: numarul citit
    '''
    try:
        nr = Citire_numar_intreg(mesaj)
        Validare_date.Validare_nr_nat(nr)
        return nr
    except ValueError:
        Citire_gresita(er, 7)
        nr = Citire_numar_nat(mesaj, er)
        return nr
    pass

def Citire_numar_complex(mesaj1, mesaj2, er):
    '''
    - in acesta functie citim un numar complex, afisand mesajele mesaj1 si mesaj2
    :param mesaj1: mesajul afisat la citirea partii reale
        type : string
    :param mesaj2: mesajul afisat la citirea partii imaginare
        type : string
    :return: partea reala si partea imaginara a numarului
    '''
    try:
        pr, pi = Citire_numar_intreg(mesaj1), Citire_numar_intreg(mesaj2)
        return pr, pi
    except ValueError:
        Citire_gresita(er, 1)
        pr, pi = Citire_numar_complex(mesaj1, mesaj2, er)
        return pr, pi
    pass

def Ccer1(l, er):
    '''
    - in acesta functie citim si returnam un numar complex si pozitia pe care sa il punem in lista (daca este nevoie)
    :param l: lista in care sunt toate numerele complexe
           type : list
    :return: a = partea reala a numarului complex
             type : int
             b = partea imaginara a numarului complex
             type : int
             poz = pozitia pe care punem numarul complex
             type : unsigned int
    :pre: poz > 0
    '''
    a, b = Citire_numar_complex("Introduceti partea reala a numarului : ", "Introduceti partea imaginara a numarului : ", er)
    print("Aveti urmatoarele optiuni : ")
    print("1. Adaugati numarul la finalul listei.")
    print("2. Adaugati numarul pe o pozitie data.")
    o = Citire_optiune(2, er)
    if (o == '2'):
        poz = Citire_pozitie(len(l) - 1, "Introduceti pozitia pe care vreti sa adaugati numarul : ", er)
        return a, b, poz
    return a, b, (len(l)+1)
    pass

def Ccer2(er, l):
    '''
    - in acesta functie citim si returnam datele suplimentare necesare pentru cerinta 2
    :return: o = optiunea aleasa de catre utilizator
             pozi = pozitia de unde se incepe stergerea sirului
             pozf = pozitia pana unde se sterge
             vechia = partea reala a numarului care se inlocuieste
             vechib = partea imaginara a numarului care se inlocuieste
             noua = partea reala a numarului cu care se inlocuieste
             noub = partea imaginara a numarului cu care se inlocuieste
    int : o, pozi, pozf, vechia, vechib, noua, noub
    :pre: o = 1, 2, 3
          pozi, pozf > 0
    '''
    print("Aveti urmatoarele optiuni : ")
    print("1. Stergerea unui element de la o pozitie data.")
    print("2. Stergerea elementelor dintre doua pozitii date.")
    print("3. Inlocuirea unui numar complex cu alt numar complex.")
    o = Citire_optiune(3, er)
    if o == 1:
        pozi = Citire_pozitie(len(l) - 1, "Introduceti pozitia numarului : ", er)
        return o, pozi, pozi
    elif o == 2:
        pozi, pozf = Pozif(l, er)
        return o, pozi, pozf
    else:
        vechia, vechib = Citire_numar_complex("Introduceti partea reala a numarului pe care vreti sa il inlocuiti : ", "Introduceti partea imaginara numarului pe care vreti sa il inlocuiti : ", er)
        noua, noub = Citire_numar_complex("Introduceti partea reala a numarului cu care vreti sa inlocuiti : ", "Introduceti partea imaginara a numarului cu care vreti sa inlocuiti : ", er)
        return o, Utile.Creare_nr_complex(vechia, vechib), Utile.Creare_nr_complex(noua, noub)
    pass

def Ccer3(er, l):
    '''
    - in aceasta functie citim si returnam datele suplimentare necesare pentru cerinta 3
    :return: o = optiunea pe care utilizatorul o doreste
             functia Pozif returneaza capatul din stanga si dreapta al secventei de cautare
    o = 1, 2, 3
    '''
    print("Aveti urmatoarele optiuni : ")
    print("1. Tiparirea partii imaginare pentru numerele dintr-o anumita secventa.")
    print("2. Tiparirea numerelor al caror modul este mai mic decat 10.")
    print("3. Tiparirea numerelor al caror modul este egal cu 10.")
    o = Citire_optiune(3, er)
    if o == 1:
        pozi, pozf = Pozif(l, er)
        return o, pozi, pozf
    else:
        return o, -1, -1
    pass

def Ccer4(er, l):
    '''
    - in acesta functie citim datele suplimentare pentru cerinta 4
    :return: o = optiunea pe care utilizatorul o alege
             pi = pozitia de inceput pentru efectuarea sumei / produsului
             pf = pozitia de final pentru efectuarea sumei / produsului
    o = 1, 2, 3
    '''
    print("Aveti urmatoarele optiuni : ")
    print("1. Efectuarea sumei numerelor dintr-o secventa.")
    print("2. Efectuarea produsului numerelor dintr-o secventa.")
    print("3. Afisarea listei ordonate descrescator dupa partea imaginara.")
    o = Citire_optiune(3, er)
    if o != 3:
        pi, pf = Pozif(l, er)
        return o, pi, pf
    else:
        return o, -1, -1
    pass

def Ccer5(er):
    '''
    - in acesta functie citim si returnam datele suplimentare pentru cerinta 5
    :return: o = optiunea aleasa de catre utilizator
             o = 1, 2, 3
             nr = numarul cu care trebuie sa comparam modulele numerelor complexe din lista
    '''
    print("Aveti urmatoarele optiuni : ")
    print("1. Filtrarea (eliminarea) numerelor care au partea reala numar prim.")
    print("2. Filtrarea (eliminarea) numerelor care au modulul mai mic decat un numar dat.")
    print("3. Filtrarea (eliminarea) numerelor care au modulul egal cu un numar dat.")
    print("4. Filtrarea (eliminarea) numerelor care au modulul mai mare decat un numar dat.")
    o = Citire_optiune(4, er)
    if o == 1:
        return o, -1
    else:
        nr = Citire_numar_nat("Introduceti numarul: ", er)
        return o, nr
    pass

def Afisare_meniu():
    '''
    - in acesta functie se afiseaza meniul
    '''
    print("Cerinta 1 : Adaugarea unui numar complex in lista.")
    print("Cerinta 2 : Modificarea numerelor din lista (stergere si inlocuire).")
    print("Cerinta 3 : Cautarea numerelor in lista.")
    print("Cerinta 4 : Efectuarea unor operatii cu numerele din lista (suma si produsul dintr-o secventa si ordonarea listei).")
    print("Cerinta 5 : Filtrarea numerelor cu partea reala prima si in functie de modul.")
    print("Cerinta 6 : Refacearea ultimei operatii care a modificat lista.")

def Cit_cer(er):
    try:
        cer = int(input("Introduceti numarul ceritei : "))
        Validare_date.Validare_numar(cer, 1, 6)
    except ValueError:
        Citire_gresita(er, 0)
        cer = Cit_cer(er)
    return cer

def Afisare_lista(l, s):
    '''
    - acesta functie afiseaza numerele complexe din lista l in format matematic (a+bi), afisand inainte mesajul s
    :param l: lista de numere complexe
    '''
    print(s, end='')
    for i in range(1, len(l)):
        print(Utile.real(l[i]), " + ", Utile.imaginar(l[i]), "i", sep='', end=', ')
    print("",sep=' ', end='\n')
    pass

def Inceput(l, er):
    Iu.Afisare_meniun()
    Afisare_lista(l, "Lista de numere complexe este : ")
    return Iu.Cit_cern()
    pass
