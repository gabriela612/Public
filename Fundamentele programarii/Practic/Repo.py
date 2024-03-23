
from Domain import Melodie

class Repo:
    def __init__(self, nume):
        self.__repo = []
        self.__nume = nume
    def get_nume(self):
        '''
        :return: numele fisierului
        '''
        return self.__nume
    def get_all(self):
        '''
        :return: lista de melodii
        '''
        return self.__repo
    def Adauga_melodie(self, melodie):
        '''
        - in acesta functie se adauga o melodie
        :param melodie: melodia care e adaugata (melodie)
        '''
        self.__repo.append(melodie)
    def __str__(self):
        rez = ""
        for i in self.__repo:
            rez += str(i)
        return rez
    def Citire_fisier(self):
        '''
        - in acesta functie se citesc din fisier datele initiale
        '''
        f = open(self.__nume, "r")
        for i in f.readlines():
            titlu, artist, gen, data = i.split(", ")
            melodie = Melodie(titlu, artist, gen, data)
            self.Adauga_melodie(melodie)
        f.close()
    def Scriere_fisier(self, nume):
        '''
        - in acesta functie se scrie lista curenta de melodii in fisierul nume
        :param nume: fisierul in care se scrie lista curenta de melodii
        '''
        f = open(self.__nume, "w+")
        f.close()
        f = open(self.__nume, "a")
        for i in self.__repo:
            f.write(str(i))
        f.close()
    def Modificare_melodie(self, melodie):
        '''
        - in acesta functie se modifica o melodie
        :param melodie: melodia modificata
        - se ridica o eroare daca melodia cu id-ul si artistul melodiei nu exista
        '''
        exista = 0
        for i in self.__repo:
            if i.get_id() == melodie.get_id():
                i.set_gen(melodie.get_gen())
                i.set_data(melodie.get_data())
                exista = 1
                break
        if exista == 0:
            raise Exception("Nu exista nicio melodie care sa aiba titlul dat si artistul dat.")


def teste():
    repo = Repo("test.txt")
    repo.Citire_fisier()
    melodie = Melodie("M1", "A1", "Rock", "01.01.2001")
    repo.Modificare_melodie(melodie)
    melodie.set_gen("Jazz")
    assert melodie.get_gen(), "Jazz"
    repo.Modificare_melodie(melodie)

teste()





