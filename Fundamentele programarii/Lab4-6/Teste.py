import Functii
import Utile

def T_c1():
    l = [{'real':0, 'img':0}]
    assert Functii.Adauga(l, 3, 4, 1) == [{'real':0, 'img':0}, {'real':3, 'img':4}]
    assert Functii.Adauga(l, 0, 0, 5) == [{'real':0, 'img':0}, {'real':3, 'img':4}, {'real':0, 'img':0}]
    assert Functii.Adauga(l, 1, 1, 3) == [{'real':0, 'img':0}, {'real':3, 'img':4}, {'real':0, 'img':0}, {'real':1, 'img':1}]
    assert Functii.Adauga(l, 1, 2, 1) == [{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':3, 'img':4}, {'real':0, 'img':0}, {'real':1, 'img':1}]

def T_c3_1():
    assert Functii.Returnare_secventa_parte_imaginara([{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':5, 'img':6}, {'real':2, 'img':2}], 1, 2) == [2, 6]
    assert Functii.Returnare_secventa_parte_imaginara([{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':5, 'img':6}, {'real':2, 'img':2}, {'real':7, 'img':3}], 2, 3) == [6, 2]
    assert Functii.Returnare_secventa_parte_imaginara([{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':5, 'img':6}, {'real':2, 'img':2}, {'real':7, 'img':3}], 4, 4) == [3]
    pass

def T_c3_2_3():
    assert Functii.Lista_modul_10([{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':5, 'img':6}, {'real':20, 'img':20}], 2) == [{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':5, 'img':6}]
    assert Functii.Lista_modul_10([{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':8, 'img':6}, {'real':2, 'img':2}, {'real':7, 'img':3}], 3) == [{'real':0, 'img':0}, {'real':8, 'img':6}]
    assert Functii.Lista_modul_10([{'real':0, 'img':0}, {'real':1, 'img':2}, {'real':2, 'img':1}, {'real':2, 'img':2}, {'real':6, 'img':8}], 3) == [{'real':0, 'img':0}, {'real':6, 'img':8}]
    assert Functii.Lista_modul_10([{'real':0, 'img':0}, {'real':8, 'img':6}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':7, 'img':3}], 3) == [{'real':0, 'img':0}, {'real':8, 'img':6}]
    pass

def T_Sterge():
    assert Functii.Sterge([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':3, 'img':3}], 1, 1) == [{'real':0, 'img':0}, {'real':2, 'img':2}, {'real':3, 'img':3}]
    assert Functii.Sterge([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':3, 'img':3}], 1, 3) == [{'real':0, 'img':0}]
    assert Functii.Sterge([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':3, 'img':3}], 1, 2) == [{'real':0, 'img':0}, {'real':3, 'img':3}]
    assert Functii.Sterge([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':3, 'img':3}], 2, 3) == [{'real':0, 'img':0}, {'real':1, 'img':1}]
    pass

def T_Prim():
    assert Functii.Prim(4) == 0
    assert Functii.Prim(1) == 0
    assert Functii.Prim(5) == 1
    assert Functii.Prim(2) == 1
    pass

def T_Filtrare_prim():
    assert Functii.Filtrare_prim([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':3, 'img':3}]) == [{'real':0, 'img':0}, {'real':1, 'img':1}]
    assert Functii.Filtrare_prim([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':4, 'img':3}]) == [{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':4, 'img':3}]
    assert Functii.Filtrare_prim([{'real':0, 'img':0}, {'real':9, 'img':3}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':4, 'img':3}]) == [{'real':0, 'img':0}, {'real':9, 'img':3}, {'real':1, 'img':1}, {'real':4, 'img':3}]
    pass

def T_Filtrare_modul():
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':4, 'img':3}], 2, 10) == [{'real':0, 'img':0}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}], 2, 10) == [{'real':0, 'img':0}, {'real':6, 'img':8}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}, {'real':8, 'img':6}], 3, 10) == [{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':4, 'img':3}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':6, 'img':8}, {'real':4, 'img':3}, {'real':20, 'img':20}], 3, 10) == [{'real':0, 'img':0}, {'real':4, 'img':3}, {'real':20, 'img':20}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}], 4, 10) == [{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}, {'real':20, 'img':20}], 4, 10) == [{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':20, 'img':20}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}], 4, 10) == [{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':6, 'img':8}, {'real':4, 'img':3}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':6, 'img':6}, {'real':6, 'img':8}, {'real':20, 'img':20}], 2, 10) == [{'real':0, 'img':0}, {'real':6, 'img':8}, {'real':20, 'img':20}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':6, 'img':6}, {'real':6, 'img':8}, {'real':20, 'img':20}], 3, 10) == [{'real':0, 'img':0}, {'real':6, 'img':6}, {'real':20, 'img':20}]
    assert Functii.Filtrare_modul([{'real':0, 'img':0}, {'real':6, 'img':6}, {'real':6, 'img':8}, {'real':20, 'img':20}], 4, 9) == [{'real':0, 'img':0}, {'real':6, 'img':6}]
    pass

def T_Inlocuieste():
    assert Functii.Inlocuieste([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':3, 'img':3}, {'real':1, 'img':1}], {'real':1, 'img':1}, {'real':5, 'img':5}) == [{'real':0, 'img':0}, {'real':5, 'img':5}, {'real':2, 'img':2}, {'real':3, 'img':3}, {'real':5, 'img':5}]
    assert Functii.Inlocuieste([{'real':0, 'img':0}, {'real':1, 'img':1}, {'real':2, 'img':2}, {'real':1, 'img':1}, {'real':3, 'img':3}, {'real':1, 'img':1}], {'real':1, 'img':1}, {'real':5, 'img':5}) == [{'real':0, 'img':0}, {'real':5, 'img':5}, {'real':2, 'img':2}, {'real':5, 'img':5}, {'real':3, 'img':3}, {'real':5, 'img':5}]
    pass

def T_Suma():
    assert Functii.SsauP([{'real': 0, 'img': 0}, {'real': 1, 'img': 1}, {'real': 6, 'img': 8}, {'real': 4, 'img': 3}, {'real': 20, 'img': 20}], 1, 1, 1) == {'real': 1, 'img': 1}
    assert Functii.SsauP([{'real': 0, 'img': 0}, {'real': 1, 'img': 1}, {'real': 6, 'img': 8}, {'real': 4, 'img': 3}, {'real': 20, 'img': 20}], 4, 4, 1) == {'real': 20, 'img': 20}
    assert Functii.SsauP([{'real': 0, 'img': 0}, {'real': 1, 'img': 1}, {'real': 6, 'img': 8}, {'real': 4, 'img': 3}, {'real': 20, 'img': 20}], 2, 3, 1) == {'real': 10, 'img': 11}
    assert Functii.SsauP([{'real': 0, 'img': 0}, {'real': 1, 'img': 1}, {'real': 6, 'img': 8}, {'real': 4, 'img': 3}, {'real': 20, 'img': 20}], 1, 1, 2) == {'real': 1, 'img': 1}
    assert Functii.SsauP([{'real': 0, 'img': 0}, {'real': 1, 'img': 1}, {'real': 6, 'img': 8}, {'real': 4, 'img': 3}, {'real': 20, 'img': 20}], 4, 4, 2) == {'real': 20, 'img': 20}
    assert Functii.SsauP([{'real': 0, 'img': 0}, {'real': 1, 'img': 1}, {'real': 6, 'img': 8}, {'real': 4, 'img': 3}, {'real': 20, 'img': 20}], 2, 3, 2) == {'real': 0, 'img': 50}

def T_Copiere():
    l = [Utile.Creare_nr_complex(0, 0), Utile.Creare_nr_complex(1, 1)]
    t = Functii.Copiere_lista(l)
    assert t == l
    l.append(Utile.Creare_nr_complex(0, 0))
    t.append(Utile.Creare_nr_complex(5, 5))
    assert t != l

def T_Sortare():
    assert Functii.Sortare([{'real': 0, 'img': 0}, {'real': 1, 'img': 1}, {'real': 6, 'img': 8}, {'real': 15, 'img': 3}, {'real': 20, 'img': 20}]) == [{'real': 0, 'img': 0}, {'real': 20, 'img': 20}, {'real': 6, 'img': 8}, {'real': 15, 'img': 3}, {'real': 1, 'img': 1}]
    assert Functii.Sortare([{'real': 0, 'img': 0}, {'real': 15, 'img': 3}]) == [{'real': 0, 'img': 0}, {'real': 15, 'img': 3}]
    pass

def T_Adauga_ist():
    c = []
    l = [{'real':5, 'img':2}, {'real':4, 'img':2}]
    c = Functii.Adauga_ist(l, c)
    assert c == [[{'real':5, 'img':2}, {'real':4, 'img':2}]]
    l.append(Utile.Creare_nr_complex(2, 2))
    c = Functii.Adauga_ist(l, c)
    assert c == [[{'real':5, 'img':2}, {'real':4, 'img':2}], [{'real':5, 'img':2}, {'real':4, 'img':2}, {'real':2, 'img':2}]]
    pass

def T_undo():
    c = [[{'real': 5, 'img': 2}, {'real': 4, 'img': 2}], [{'real': 5, 'img': 2}, {'real': 4, 'img': 2}, {'real': 2, 'img': 2}]]
    l, c = Functii.undo(c)
    assert l == [{'real': 5, 'img': 2}, {'real': 4, 'img': 2}, {'real': 2, 'img': 2}]
    assert c == [[{'real': 5, 'img': 2}, {'real': 4, 'img': 2}]]
    l, c = Functii.undo(c)
    assert l == [{'real': 5, 'img': 2}, {'real': 4, 'img': 2}]
    assert c == []
    pass

def Toate_testele():
    T_c1()
    T_Prim()
    T_c3_1()
    T_c3_2_3()
    T_Sterge()
    T_Filtrare_prim()
    T_Filtrare_modul()
    T_Inlocuieste()
    T_Suma()
    T_Copiere()
    T_Sortare()
    T_Adauga_ist()
    T_undo()
    pass

'''
adaugare
stergere
split
'''