import math
import Utile

def Formare_lista_mesaje_erori():
    '''
    - in acesta functie cream si returnam o lista cu mesajele de eroare
    :return: er = lista cu mesajele de eroare
        type : list
    '''
    er = []
    er.append("Trebuia sa introduceti un numar natural intre 1 si 6.") # 0
    er.append("Partea reala si partea imaginara trebuie sa fie numere intregi.") # 1
    er.append("Optiunea trebuie sa fie 1 sau 2.") # 2
    er.append("Optiunea trebuie sa fie intre 1 si 3.") # 3
    er.append("Optiunea trebuie sa fie intre 1 si 4.") # 4
    er.append("Pozitia trebuie sa fie intre 1 si lungimea listei de numere complexe.") # 5
    er.append("Pozitia de inceput trebuie sa fie mai mica sau egala decat pozitia de final.") # 6
    er.append("Numarul trebuie sa fie natural.")
    return er
    pass

def Copiere_lista(l):
    '''
    - in acesta functie cream si returnam o copie a listei cu numere complexe l
    :param l: lista de numere complexa care va fi copiata
        type : list
    :return: c =  o copie a listei l
        type : list
    '''
    c = []
    for i in l:
        pr = Utile.real(i) # partea reala
        pi = Utile.imaginar(i) # partea imaginara
        nr_c = Utile.Creare_nr_complex(pr, pi)
        c.append(nr_c)
    return c
    pass

def Adauga(l, a, b, poz):
    '''
    - in acesta functie adaugam dictionarul {'real' : a, 'img' : b} in lista l pe pozitia poz
    :param l: lista cu numerele compleze
    type : list
    :param a: partea reala a numarului a+bi
    type : int
    :param b: partea imaginara a numarului a+bi
    type : int
    :param poz: pozitia pe care se adauga numarul complex in lista l
    type : unsigned int
    :pre: poz > 0
    '''
    l.insert(poz, Utile.Creare_nr_complex(a, b))
    return l
    pass

def Sterge(l, st, dr):
    '''
    - in acesta functie stergem elementele dintre pozitiile st si dr in lista l
    :param l: lista de numere complexe
            type : list
    :param st: capatul din stanga al secventei ce trebuie stearsa din l
            type : unsigned int
    :param dr: capatul din dreapta al secventei ce trebuie stearsa din l
    :return: lista l dupa stergere
    pre : st <= dr
    '''
    l[st:] = l[dr+1:]
    return l
    pass

def Inlocuieste(l, vechi, nou):
    '''
    - in acesta functie inlocuim, in lista l, toate aparitiile numarului vechi cu numarul nou
    :param l: lista de numere complexe
        type : list
    :param vechi: numarul care trebuie inlocuit
        type : dictionar
    :param nou: numarul cu care se inlocuieste vechi
        type : dictionar
    :return: se returneaza sirul modificat
    '''
    for i in range(len(l)):
        if l[i] == vechi:
            l[i] = nou
    return l
    pass

def Returnare_secventa_parte_imaginara(l, st, dr):
    '''
    - in acesta functie returnam partile imaginare ale numerelor din lista l din secventa marginita de pozitia st si dr
    :param l: lista de numere complexe
    type : list
    :param st: capatul din stanga al secventei
    type : unsigned int
    :param dr: capatul din dreapta al secventei
    type : unsigned inte
    t = lista cu partile imaginare din secventa
    type : list
    :return: partile imaginare ale numerelor din lista l din secventa marginita de pozitia st si dr
    '''
    t = []
    for i in range(st, dr + 1):
        t.append(Utile.imaginar(l[i]))
    return t
    pass

def Modulp(nr):
    '''
    - in acesta functie calculam patratul modului lui nr si il returnam
    :param nr: numarul complex
           type : dict
    :return: modul
             type : unsigned int
    '''
    modul = (Utile.real(nr)**2)+(Utile.imaginar(nr)**2)
    return modul
    pass

def Comparare_modul(nr, c):
    '''
        - in acesta functie comparam modul lui nr cu c si returnam numere sugestive
        :param nr: numar complex
                type : dict
        :param: c: numarul cu care comparam modulul
                type : unsigned int
        :return: -1 daca modului lui nr e mai mic decat c
                 0 daca madului lui nr este egal cu c
                 1 daca modului lui nr este mai mare decat c
    '''
    m = Modulp(nr)
    if m < c * c:
        return -1
    elif m == c * c:
        return 0
    else:
        return 1

def Lista_modul_10(l, semn):
    '''
    - in acesta functie returnam lista de numere complexe in care modulul este mai mic sau egal cu 10
    :param l: lista de numere complexe
            type : list
    :param semn: este 2 sau 3 ce reprezinta mai mic, respectiv egal (ne zice cum trebuie sa fie in comparatie cu 10)
            semn = 2, 3
    :return: t = lista de numere complexe care indeplinesc conditia (modulul sa fie mai mic sau egal cu 10)
            type : list
    '''
    semn -= 3
    t = [Utile.Creare_nr_complex(0, 0)]
    for i in range(1, len(l)):
        if Comparare_modul(l[i], 10) == semn:
            t = Adauga(t, Utile.real(l[i]), Utile.imaginar(l[i]), len(t)+1)
    return t
    pass

def Suma2nr(a, b):
    '''
    - in aceasta functie calculam suma a doua numere complexe
    :param a: primul numar complex
        type : dictionar
    :param b: al doilea numar complex
        type : dictionar
    :return: un numar complex ce reprezinta suma lui a si b
        type : dictionar
    '''
    pr = Utile.real(a) + Utile.real(b) # partea reala
    pi = Utile.imaginar(a) + Utile.imaginar(b) # partea imaginara
    return Utile.Creare_nr_complex(pr, pi)
    pass

def Produs2nr(a, b):
    '''
        - in aceasta functie calculam produsul a doua numere complexe
        :param a: primul numar complex
            type : dictionar
        :param b: al doilea numar complex
            type : dictionar
        :return: un numar complex ce reprezinta produsul lui a si b
            type : dictionar
        '''
    pr = (Utile.real(a) * Utile.real(b)) - (Utile.imaginar(a) * Utile.imaginar(b)) # partea reala a produsului
    pi = Utile.real(a) * Utile.imaginar(b) + Utile.real(b) * Utile.imaginar(a) # partea imaginara a produsului
    return Utile.Creare_nr_complex(pr, pi)
    pass

def SsauP(l, st, dr, op):
    '''
    - in acesta functie calculam suma (op = 1) sau produsul (op = 2) numerelor din sir intre pozitiile st si dr
    :param l: lista din care se ia secventa pentru care calculam suma sau produsul
        type : list
    :param st: pozitia de unde incepem sa calculam suma
        type : unsigned int
    :param dr: pozitia pana la care se calculeaza suma
        type : unsigned int
    :param op: ne zice daca se efectueaza suma sau produsul
        op = 1 sau 2
    :return: rez = suma (op=1) sau produsul (op=2) numerelor din sir intre pozitiile st si dr
        type : dictionar
    '''
    c = [Suma2nr, Produs2nr]
    op -= 1
    rez = Utile.Creare_nr_complex(op, 0)
    for i in range(st, dr+1):
        rez = c[op](l[i], rez)
    return rez
    pass

def Descrescator(a, b):
    '''
    - in aceasta functie verificam daca a si b (numere intregi) sunt in ordine descrescatoare (daca a >= b)
    :param a: primul numar intreg
    :param b: al doilea numar intreg
    :return: 1, daca a >= b
             0, daca a < b
    '''
    return a >= b
    pass

def Sortare(l): # se creaza o lista noua care se sorteaza si returneaza
    '''
    - in acesta functie sortam descrescator (in functie de partea imaginara) o copie a listei l si o returnam
    :param l: lista de numere complexe
        type : list
    :return: d = lista l ordonata descrescator in functie de partea imaginara
        type : list
    '''
    d = Copiere_lista(l)
    for i in range(1, len(d)):
        for j in range(i, len(d)):
            if Descrescator(Utile.imaginar(d[i]), Utile.imaginar(d[j])) == 0:
                aux = Utile.Creare_nr_complex(Utile.real(d[i]), Utile.imaginar(d[i]))
                d[i] = Utile.Creare_nr_complex(Utile.real(d[j]), Utile.imaginar(d[j]))
                d[j] = Utile.Creare_nr_complex(Utile.real(aux), Utile.imaginar(aux))
    return d
    pass

def Prim(n):
    '''
    - in acesta functie verificam daca n este numar prim
    :param n: numarul care se verifica
        type : int
    :return: 1, daca n este prim
             0, daca n nu este prim
    '''
    if n < 2:
        return 0
    else:
        for d in range(2, int(math.sqrt(n)) + 1):
            if n % d == 0:
                return 0
        return 1

def Filtrare_prim(l):
    i = 1
    while i < len(l):
        if Prim(Utile.real(l[i])) == 1:
            l = Sterge(l, i, i)
        else:
            i += 1
    return l
    pass

def Filtrare_modul(l, op, nr):
    '''
    - in acesta functie stergem toate numere din lista care au modulul <, = sau > decat 10
    :param l: lista de numere complexe
            type : list
    :param op: = -1 - trebuie sa stergem numerele cu modulul mai mic decat 10
               = 0 - trebuie sa stergem numerele cu modulul egal cu 10
               = 1 - trebuie sa stergem numerele cu modulul mai mare decat 10
    :param: nr = numarul care trebuie comparat cu modulul numerelor din lista
            type : unsigned int
    :return: lista modificata
    '''
    i = 1
    op -= 3
    while i < len(l):
        if Comparare_modul(l[i], nr) == op:
            l = Sterge(l, i, i)
        else:
            i += 1
    return l
    pass

def Adauga_ist(l, ist):
    '''
    - in acesta functie adaugam, la finalul listei ist, lista l (adaugam ultima varianta a listei in istoric inainte de modificare)
    :param l: lista care va fi adaugata
        type : list
    :param ist: lista la care adaugam
        type : list
    :return: ist = lista ist care contine pe ultima pozitie lista l
        type : list
    '''
    c_l = Copiere_lista(l)
    ist.append(c_l)
    return ist
    pass

def undo(ist):
    '''
    - in acesta functie efectuam operatia undo (inlocuim lista curenta cu lista anterioara), apoi stergem ultima lista din ist
    :param ist: Vector cu toate listele de numere complexe avute pana acum
        typr : list
    :return: li = lista de numere complexe inainte de efectuarea ultimei operatii
        type : list
             ist = lista de istoric fara ultimul element (lista l)
        type : list
    '''
    n_ist = len(ist)
    n_ist -= 1 # pozitia ultimului element din lista ist (pozitia listei (din ist) pe care o vom returna)
    li = Copiere_lista(ist[n_ist])
    Sterge(ist, n_ist, n_ist)
    return li, ist
    pass

def Desfacere1(cer, l):
    a = int(cer[1])
    b = int(cer[2])
    if cer[3] == '1':
        poz = len(l)
    else:
        poz = int(cer[4])
    return a, b, poz
    pass

def Desfacere2(cer, l):
    o = int(cer[0])
    if cer[1] == '1':
        p1 = int(cer[2])
        p2 = p1
    else:
        p1 = int(cer[2])
        p2 = int(cer[3])
    return o, p1, p2
    pass