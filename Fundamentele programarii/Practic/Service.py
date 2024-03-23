import Domain
import Repo


class Serv:
    def __init__(self, repo, vali):
        self.__repo = repo
        self.__vali = vali
    def __str__(self):
        return str(self.__repo)
    def Modificare_melodie(self, titlu, artist, gen, data):
        '''
        - in acesta functie se modifica o melodie care are titlul si id-ul egale cu cele date
        :param titlu: titlul dat
        :param artist: artistul dat
        :param gen: genul dat
        :param data: data data
        - se ridica erori daca datele sunt incorecte sau daca nu exista vreo melodie cu titlul si artistul date
        '''
        melodie = Domain.Melodie(titlu, artist, gen, data)
        self.__vali.Validare(melodie)
        self.__repo.Modificare_melodie(melodie)
        self.__repo.Scriere_fisier(self.__repo.get_nume())

    def cmp(self, a, b):
        '''
        - in acesta functie comparam datele de la obiectele a si b de tip melodie
        :param a: o melodie
        :param b: o melodie
        :return: True daca data lui a <= data lui b, False in caz contrar
        '''
        # true = a <= b
        dataa = a.get_data()
        datab = b.get_data()
        from Domain import Creare_data
        zia, lunaa, ana = dataa.split(".")
        dataa = Creare_data(int(zia), int(lunaa), int(ana))
        zib, lunab, anb = datab.split(".")
        datab = Creare_data(int(zib), int(lunab), int(anb))
        return min(dataa, datab) == dataa

    def Merge_sort(self, l, cmp):
        '''
        - implementarea functiei de Merge Sort cu cmp
        :param l: lista
        :param cmp: functia de comparare
        :return: lista sortata
        '''
        if len(l) < 2:
            return l
        mi = len(l) // 2
        st = self.Merge_sort(l[:mi], cmp)
        dr = self.Merge_sort(l[mi:], cmp)
        i = j = 0
        rez = []
        if st == []:
            return dr
        if dr == []:
            return st
        while i < len(st) and j < len(dr):
            if cmp(st[i], dr[j]):
                rez.append(st[i])
                i += 1
            else:
                rez.append(dr[j])
                j += 1
        rez += st[i:]
        rez += dr[j:]
        return rez


    def Exporta_melodii(self, nume):
        '''
        - in acesta functie exportam melodiile sortate dupa data
        :param nume: numele fisierului in care exportam lista curenta de melodii
        '''
        rez = self.Merge_sort(self.__repo.get_all(), self.cmp) # lista de melodii (domain)
        from Repo import Repo
        repo_sortat = Repo(nume)
        for i in rez:
            repo_sortat.Adauga_melodie(i)
        repo_sortat.Scriere_fisier(nume)

def teste():
    from Domain import Melodie
    melodie1 = Melodie("M1", "A1", "Jazz", "01.01.2001")
    melodie2 = Melodie("M2", "A2", "Jazz", "01.02.2000")
    melodie3 = Melodie("M3", "A3", "Rock", "01.01.2000")
    l = [melodie1, melodie2, melodie3]
    repo = Repo.Repo("test.txt")
    vali = Domain.Validator()
    serv = Serv(repo, vali)
    l = serv.Merge_sort(l, serv.cmp)
    m = l[0]
    assert m.get_data(), "01.01.2000\n"

teste()

