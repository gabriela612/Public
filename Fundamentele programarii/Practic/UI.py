
class Consola:
    def __init__(self, serv):
        self.__serv = serv

    def Modificare_melodie(self):
        '''
        - in acesta functie modificam melodia cu titlul si artistul
        '''
        titlu = input("Introduceti titlul : ")
        artist = input("Introduceti artistul : ")
        gen = input("Introduceti genul : ")
        data = input("Introduceti data : ")
        try:
            self.__serv.Modificare_melodie(titlu, artist, gen, data)
        except Exception as er:
            print(er)

    def Exporta_melodii(self):
        '''
        - in acesta functie se exporta lista curenta de melodii
        :return:
        '''
        nume = input("Introduceti numele fisierului : ")
        self.__serv.Exporta_melodii(nume)

    def Afisare_meniu(self):
        '''
        - in acesta functie se afiseaza meniul
        '''
        print("1. Modificare melodie.")
        print("2. Exporta melodii sortate.")
        print("3. Creeaza aleator melodii.")

    def Creaza_aleator_melodii(self):
        '''
        - in acesta functie se creaza aleeator melodii
        '''
        numar = input("Introduceti numarul de melodii : ")

    def Afisare_melodii(self):
        '''
        - in acesta functie se afiseaza melodiile
        '''
        print("Melodiile sunt : ")
        print(self.__serv)

    def Citire_cerinta(self):
        '''
        - in acesta functie se citeste cerinta
        '''
        c = input("Introduceti cerinta : ")
        return c

    def Inceput(self):
        '''
        - acesta este functia de inceput
        '''
        cer = [self.Modificare_melodie, self.Exporta_melodii, self.Creaza_aleator_melodii]
        while True:
            self.Afisare_melodii()
            self.Afisare_meniu()
            try:
                c = self.Citire_cerinta()
                cer[int(c) - 1]()
            except Exception as er:
                print(er)

