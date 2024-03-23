import Interfata_utilizator
import Functii
import Teste
import Utile

l = [Utile.Creare_nr_complex(0, 0)]
ist = []

def Cer1(cer, l):
    '''
    - in aceasta functie se rezolva cerinta 1 : adaugarea unui numar complex in lista l
    :param l: lista de numere complexe
    type : list
    a, b = partea reala, respectiv partea imaginara a numarului adaugat in lista
    poz = pozitia la care se adauga numarul in lista
    :return : l - lista de numere complexe
    '''
    a, b, poz = Functii.Desfacere1(cer, l)
    l = Functii.Adauga(l, a, b, poz)
    return l
    pass

def Cer2(cer, l):
    '''
    - in acesta functie se rezolva cerinta 2 : modificarea listei (stergere si inlocuire)
    :param l: lista de numere complexe
        type : list
    :return : l - lista de numere complexe
    o = optiunea aleasa de utilizator
    p1, p2 = parametri pentru stergere sau inlocuire (pozitiile intre care se sterge sau numarul inlocuit si inlocuitor)
    o = 1,2,3
    p1,p2 > 0
    '''
    c2 = [Functii.Sterge, Functii.Sterge, Functii.Inlocuieste]
    o, p1, p2 = Functii.Desfacere2(cer, l)
    o -= 1
    l = c2[o](l, p1, p2)
    return l
    pass

def Cer3(l):
    '''
    - in aceasta functie rezolvam cerinta 3 : cautarea numerelor in lista
    :param l: lista de numere complexe
    o = optiunea aleasa de utilizator
    st = capatul de unde se incepe cautarea
    dr = capatul unde se opreste cautarea
    o = 1, 2, 3
    st, dr > 0
    t = sirul care trebuie afisat
    type : list
    :return : l - lista de numere complexe
    '''
    o, st, dr = Interfata_utilizator.Ccer3(er, l)
    t = []
    if o == 1:
        t = Functii.Returnare_secventa_parte_imaginara(l, st, dr)
        Interfata_utilizator.Afisare_parte_imaginara(t)
    else:
        t = Functii.Lista_modul_10(l, o)
        Interfata_utilizator.Afisare_lista(t, "Numerele cautate sunt : ")
    return l
    pass

def Cer4(l):
    '''
    - in aceasta functie rezolvam cerinta 4 : Efectuarea unor operatii cu numerele din lista (suma si produsul dintr-o secventa si ordonarea listei).
    :param l: lista numerelor complexe
    type : list
    o = optiunea pe care a ales-o utilizatorul
    type : unsigned int
    st, dr = capetele secventei din lista pentru care se fac operatiile
    type : unsigned int
    t = sirul ordonat descrescator
    type = list
    var = suma sau produsul cautat
    type dictionar
    o = 1,2,3
    st, dr > 0
    :return : l - lista de numere complexe
    '''
    o, st, dr = Interfata_utilizator.Ccer4(er, l)
    if o == 3:
        t = Functii.Sortare(l)
        Interfata_utilizator.Afisare_lista(t, "Lista ordonata descrescator dupa partea imaginara este : ")
    else:
        var = Functii.SsauP(l, st, dr, o)
        if o == 1:
            Interfata_utilizator.Afisare_nr_mesaj(var, "Suma este ")
        else:
            Interfata_utilizator.Afisare_nr_mesaj(var, "Produsul este ")
    return l
    pass

def Cer5(l):
    '''
    - in acesta functie rezolvam cerinta 5 : Filtrarea
    :param l: lista de numere complexe
    o = optiunea pe care o alege utilizatorul
    o = 1, 2, 3, 4
    nr = numarul care trebuie comparat cu modulele numerelor din sir
    type : unsigned int
    :return : l - lista de numere complexe
    '''
    o, nr = Interfata_utilizator.Ccer5(er)
    if nr == -1:
        l = Functii.Filtrare_prim(l)
    else:
        l = Functii.Filtrare_modul(l, o, nr)
    return l
    pass

def Cer6(l, ist):
    '''
    - in acesta functie rezolvam cerinta 6
    :param l: lista de numere complexe
    :param ist: lista cu toate listele anterioare
    :return : l - lista de numere complexe
              ist - istoricul cu toate variantele listei
    '''
    l, ist = Functii.undo(ist)
    return l, ist
    pass

def Apelare_cerinta(cer_citita, l, ist):
    cer = [Cer1, Cer2, Cer3, Cer4, Cer5, Cer6]
    if cer_citita in [1,2,5]:
        ist = Functii.Adauga_ist(l, ist)
    if cer_citita == 6:
        l, ist = (cer[cer_citita - 1])(l, ist)
    else:
        l = (cer[cer_citita - 1])(l)
    return l

def Apelare_cerintan(cer_citata, l):
    cer = [Cer1, Cer2]
    l = cer[cer_citata[0]](cer_citita, l)
    return l
    pass

Teste.Toate_testele()
er = Functii.Formare_lista_mesaje_erori()
while True:
    try:
        cer_citita = Interfata_utilizator.Inceput(l, er)
        l = Apelare_cerintan(cer_citita, l)
    except:
        print("Cerinta incorecta.")
