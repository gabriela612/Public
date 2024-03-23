def Validare_numar(nr, st, dr):
    '''
    - in aceasta functie cream o eroare daca nr nu face parte din intervalul [st, dr]
    :param nr: numarul
    :param st: capatul din stanga al intervalului
    :param dr: capatul din dreapta al intervalului
    :return: nu returneaza nimic
    - daca nr nu apartine intervalului, se creaza o eroare
    '''
    if nr < st or nr > dr:
        raise ValueError()
    pass

def Validare_pozitii(st, dr):
    '''
    - in acesta functie cream o eroare daca st > dr
    :param st: capatul din stanga al intervalului
    :param dr: capatul din dreapta al intervalului
    :return: nu se returneaza nimic
    - se creaza o eroare daca st > dr
    '''
    if st > dr:
        raise ValueError()

def Validare_nr_nat(nr):
    '''
    - in acesta functie cream o eroare daca nr nu este numar natural
    :param nr: numarul
    :return: nu se returneaza nimic
    - cream o eroare daca nr nu este numar natural
    '''
    if nr < 0:
        raise ValueError()
