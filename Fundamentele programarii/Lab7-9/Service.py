from Domain import Student
from Domain import Disciplina
from Domain import Nota
from Repository import Repo_cer12
from Repository import Repo_cer14
from Repository import RepoN

class ServS:
    def __init__(self, repoS, valiS):
        '''
        :param repoS: lista de studenti
            type : RepoS
        :param valiS: lista de erori
            type : ValidatorS
        '''
        self.__repoS = repoS
        self.__valiS = valiS
    def __str__(self):
        return str(self.__repoS)
    def AddS_ser(self, idS, numeS):
        '''
        - in acesta functie adaugam un student in lista, daca datele sunt corecte
        :param idS: id-ul studentului
            type : string
        :param numeS: numele studentului
            type : string
        :return: studentul care a fost adaugat
        '''
        stud = Student(idS, numeS)
        self.__valiS.ValidareS(stud)
        self.__repoS.Exista_dejaS(idS)
        self.__repoS.Adauga_in_lista(stud)
        return stud
    def AddS_rand(self, nr):
        '''
        - in acesta functie generam si adaugam nr studenti in lista de studenti
        :param nr: numarul de studenti pe care ii vom genera si adauga la lista
        '''
        import string
        import random
        litere = string.ascii_letters
        i = 0
        j = 100
        while i < nr and j != 0:
            idS = str(random.choice(range(1, 100)))
            nr_lit = int(random.choice(range(5, 20)))
            numeS = "".join(random.choices(litere, k = nr_lit))
            try:
                self.AddS_ser(idS, numeS)
                i += 1
            except:
                j -= 1
        if j == 0:
            raise Exception("S-au adaugat doar "+str(i)+" studenti.")
    def StergeS_ser(self, idS):
        '''
        - in acesta functie stergem un student din lista, daca id-ul e corect
        :param idS: id-ul studentului
            type : string
        '''
        self.__repoS.StergeS(idS)
    def nr_stud(self):
        '''
        - in acesta functie calculam numarul de studenti din lista
        :return: numarul de studenti din lista
        '''
        return self.__repoS.get_nr_stud()
    def Inlocuieste_numeS(self, idS, nume_nou):
        '''
        - in acesta functie inlocuim numele studentului care are IdS, cu nume_nou
        :param idS: id-ul studentului
            type : string
        :param nume_nou: numele cu care inlocuim
            type : string
        '''
        self.__repoS.Inlocuieste_numeS(idS, nume_nou)
    def CautareS_ser(self, idS):
        '''
        - in acesta functie cautam studentul cu id-ul idS
        :param idS: id-ul studentului cautat
            type : string
        :return: studentul cautat (tip student)
        '''
        return self.__repoS.get_stud(idS)

class ServD:
    def __init__(self, repoD, valiD):
        '''
        :param repoD: lista de studenti
            type : RepoD
        :param valiD: lista de erori
            type : ValidatorD
        '''
        self.__repoD = repoD
        self.__valiD = valiD
    def __str__(self):
        return str(self.__repoD)
    def nr_di(self):
        '''
        - in acesta functie calculam numarul de discipline din lista
        :return: numarul de discipline din lista
        '''
        return self.__repoD.get_nr_di()
    def AddD_ser(self, idD, numeD, profD):
        '''
        - in acesta functie adaugam o disciplina in lista, daca datele sunt corecte
        :param idD: id-ul disciplinei
            type : string
        :param numeD: numele disciplinei
            type : string
        :param profD: profesorul disciplinei
            type : string
        :return: studentul care a fost adaugat
        '''
        di = Disciplina(idD, numeD, profD)
        self.__valiD.ValidareD(di)
        self.__repoD.Exista_dejaD(idD)
        self.__repoD.Adauga_in_lista(di)
        return di
    def AddD_rand(self, nr):
        '''
        - in acesta functie generam si adaugam nr discipline in lista de discipline
        :param nr: numarul de discipline pe care le vom genera si adauga la lista
        '''
        import string
        import random
        litere = string.ascii_letters
        i = 0
        j = 100
        while i < nr and j != 0:
            idD = str(random.choice(range(1, 100)))
            nr_lit = int(random.choice(range(5, 20)))
            numeD = "".join(random.choices(litere, k = nr_lit))
            profD = "".join(random.choices(litere, k = nr_lit))
            try:
                self.AddD_ser(idD, numeD, profD)
                i += 1
            except:
                j -= 1
        if j == 0:
            raise Exception("S-au adaugat doar "+str(i)+" studenti.")
    def StergeD_ser(self, idD):
        '''
        - in acesta functie stergem o disciplina din lista, daca id-ul e corect
        :param idD: id-ul disciplinei
            type : string
        '''
        self.__repoD.StergeD(idD)
    def Inlocuieste_profD(self, idD, prof_nou):
        '''
        - in acesta functie inlocuim profesorul disciplinei care are IdD, cu prof_nou
        :param idD: id-ul disciplinei
            type : string
        :param prof_nou: profesorul cu care inlocuim
            type : string
        '''
        self.__repoD.Inlocuieste_profD(idD, prof_nou)
    def CautareD_ser(self, idD):
        return self.__repoD.get_di(idD)

class ServN:
    def __init__(self, repoN, valiN, repoS, repoD):
        '''
        :param repoN: lista de note
            type : RepoN
        :param valiN: lista de erori
            type : ValidatorN
        :param repoS: lista de studenti
            type : RepoS
        :param repoS: lista de discipline
            type : RepoD
        '''
        self.__repoN = repoN
        self.__valiN = valiN
        self.__repoS = repoS
        self.__repoD = repoD
    def __str__(self):
        return str(self.__repoN)
    def AddN_ser(self, idS, idD, nota):
        '''
        - in acesta functie adaugam o nota in lista, daca datele sunt corecte
        :param idS: id-ul studentului
            type : string
        :param idD: id-ul disciplinei
            type : string
        '''
        self.__repoS.get_stud(idS)
        self.__repoD.get_di(idD)
        no = Nota(idS, idD, [nota])
        self.__valiN.ValidareN(no)
        try:
            poz = self.__repoN.Cautare_pozitie_idS_idD_rec(idS, idD, 0)
            self.__repoN.Adaugare_nota_la_lista_de_note(poz, nota)
        except Exception as er:
            no = Nota(idS, idD, [nota])
            self.__repoN.AdaugareN(no)
    def Compara_liste_note(self, a, b):
        '''
        - in acesta functie comparam lista a cu lista b si returnam 1 daca a > b
        :param a: prima lista
            type : list
        :param b: a doua lista
            type : list
        :return: 1 daca a > b
                 0 daca a < b
        '''
        a = sorted(a)
        b = sorted(b)
        lungime = min(len(a), len(b))
        for i in range(0, lungime):
            if a[i] < b[i]:
                return 0
        return 1

    def Comparare_medie(self, x, y):
        if x.get_media() > y.get_media():
            return 1
        if x.get_media() < y.get_media():
            return 0
        return 2

    def Comparare_nume_note(self, x, y):
        '''
        - returneaza 1 daca x < y, 2 daca sunt egale si 0 daca x > y
        :param x:
        :param y:
        :return:
        '''
        if x.get_numeS() < y.get_numeS():
            return 1
        else:
            if x.get_numeS() == y.get_numeS():
                if x.get_noteS() > x.get_noteS():
                    return 1
                if x.get_noteS() == x.get_noteS():
                    return 2
                if x.get_noteS() < x.get_noteS():
                    return 0
            else:
                return 0

    def GnomeSort(self, lista, cmp):
        n = len(lista)
        i = 0
        while i < n:
            if i == 0:
                i = i + 1
            if cmp(lista[i - 1], lista[i]) == 0:
                aux = lista[i - 1]
                lista[i - 1] = lista[i]
                lista[i] = aux
                i = i - 1
            else:
                i = i + 1
        return lista

    def QuickSort(self, lista, cmp):
        if len(lista) > 1:
            mici = []
            mari = []
            egale = []
            pivot = lista[-1]
            for i in lista:
                if cmp(i, pivot) == 1:
                    mici.append(i)
                elif cmp(i, pivot) == 2:
                    egale.append(i)
                else:
                    mari.append(i)
            return self.QuickSort(mici, cmp) + egale + self.QuickSort(mari, cmp)
        return lista

    def Sortare_alf_nota(self, note_di):
        '''
        - in acesta functie sortam note_di alfabetic dupa numele studentilor si dupa notele lor
        :param note_di: lista cu toate notele la o singura disciplina
            type: RepoN
        :return: returnam lista sortata
        '''
        for i in range(0, note_di.get_len()):
            for j in range (i+1, note_di.get_len()):
                idSi = note_di.get_id_stud_poz(i)
                studi = self.__repoS.get_stud(idSi)
                numei = studi.get_numeS()
                idSj = note_di.get_id_stud_poz(j)
                studj = self.__repoS.get_stud(idSj)
                numej = studj.get_numeS()
                if numei == numej:
                    noteSi = note_di.get_note_stud_poz(i)
                    noteSj = note_di.get_note_stud_poz(j)
                    if self.Compara_liste_note(noteSi, noteSj):
                        note_di.Interschimba(i, j)
                elif (numei > numej):
                    note_di.Interschimba(i, j)
        return note_di
    def Transformare_idS_numeS_noteS_rec(self, note_di, rez, i):
        if i == note_di.get_len():
            return ""
        idS = note_di.get_id_stud_poz(i)
        stud = self.__repoS.get_stud(idS)
        numeS = stud.get_numeS()
        noteS = note_di.get_note_stud_poz(i)
        rez += "id " + str(idS) + ", nume " + str(numeS) + ", note " + str(noteS) + ";\n"
        i += 1
        return rez+self.Transformare_idS_numeS_noteS_rec(note_di, rez, i)
    def Transformare_idS_numeS_noteS(self, note_di):
        '''
        - in acesta functie cream un string pentru afisare
        :param note_di: o lista cu id-urile unor note
        :return: stringul care se va afisa
        '''
        rez = ""
        for i in range(0, note_di.get_len()):
            idS = note_di.get_id_stud_poz(i)
            stud = self.__repoS.get_stud(idS)
            numeS = stud.get_numeS()
            noteS = note_di.get_note_stud_poz(i)
            rez += "id "+str(idS)+", nume "+ str(numeS)+", note "+str(noteS)+";\n"
        return rez

    def Creare_obiect_12(self, note_di):
        return Repo_cer12(note_di, self.__repoS).get_all_values()

    def Studentii_la_idD_ord_alf_ref(self, idD):
        note_di = self.__repoN.Cautare_note_idD(idD)
        note = self.Creare_obiect_12(note_di)
        note_sortate = self.GnomeSort(note, self.Comparare_nume_note)
        return note_sortate

    def Studentii_la_idD_ord_alf(self, idD):
        '''
        - in acesta functie ordonam alfabetic (si dupa nota) stundetii care au note la disciplina cu id-ul idD
        :param idD: id-ul disciplinei
        :return: lista de studenti, care au note la diciplina cu idD, ordonati alfabetic dupa nume si dupa nota
        '''
        self.__repoD.get_di(idD)
        note_di = self.__repoN.Cautare_note_idD(idD) # toate notele la disciplina cu idD (tip : RepoN)
        note_di = self.Sortare_alf_nota(note_di)
        rez = self.Transformare_idS_numeS_noteS_rec(note_di, '', 0)
        return rez
    def Sortare_di_nr_stud_cu_nota(self, all_di, nr_stud_cu_note):
        '''
        - in acesta functei sortam all_di si nr_stud_cu_note in functie de numarul de elevi cu note la fiecare disciplina
        :param all_di: id-urile de la toate disciplinele
            type : list
        :param nr_stud_cu_note: numarul de elevi cu note pentru fiecare disciplina
            type : list
        :return: listele sortate
        '''
        for i in range(0, len(all_di)):
            for j in range(i + 1, len(all_di)):
                if nr_stud_cu_note[i] < nr_stud_cu_note[j]:
                    aux = nr_stud_cu_note[i]
                    nr_stud_cu_note[i] = nr_stud_cu_note[j]
                    nr_stud_cu_note[j] = aux
                    aux = all_di[i]
                    all_di[i] = all_di[j]
                    all_di[j] = aux
        return all_di, nr_stud_cu_note
    def Transformare_idD_numeD_NrStudCuNote_rec(self, all_di, nr_stud_cu_note, rez, i):
        if i == len(all_di):
            return ''
        idD = all_di[i]
        di = self.__repoD.get_di(idD)
        numeD = di.get_numeD()
        nr_stud = nr_stud_cu_note[i]
        rez += "id " + str(idD) + ", nume " + str(numeD) + " si " + str(nr_stud) + " studenti cu note;\n"
        return rez+self.Transformare_idD_numeD_NrStudCuNote_rec(all_di, nr_stud_cu_note, rez, i)
    def Transformare_idD_numeD_NrStudCuNote(self, all_di, nr_stud_cu_note):
        '''
        - in acesta functie cream un string pentru afisare
        :param all_di: o lista cu id-urile disciplinelor
            type : list
        :param nr_stud_cu_note: contine numarul de elevi cu note pentru fiecare disciplina din all_di
            type : list
        :return: stringul care se va afisa
        '''
        rez = ""
        for i in range(0, len(all_di)):
            idD = all_di[i]
            di = self.__repoD.get_di(idD)
            numeD = di.get_numeD()
            nr_stud = nr_stud_cu_note[i]
            rez += "id "+str(idD)+", nume "+str(numeD)+" si "+str(nr_stud)+" studenti cu note;\n"
        return rez
    def Disciplinele_ord_nrstud(self):
        '''
        - in acesta functie sortam descrescator disciplinele in functie de numarul de studenti care au note
        '''
        all_di = self.__repoD.get_all_idD()
        nr_stud_cu_note = []
        for i in range(0, len(all_di)):
            nr_stud_cu_note.append(self.__repoN.get_nr_stud_pt_di(all_di[i]))
        all_di, nr_stud_cu_note = self.Sortare_di_nr_stud_cu_nota(all_di, nr_stud_cu_note)
        rez = self.Transformare_idD_numeD_NrStudCuNote(all_di, nr_stud_cu_note)
        return rez
    def Sortare_medie(self, all_stud, medii):
        '''
        - in acesta functie sortam studentii descrescator dupa medie
        :param all_stud: id-urile tuturor studentilor
            type : list
        :param medii: media tuturor studentilor din all_stud
            type : list
        :return: listele sortate
        '''
        for i in range(0, len(all_stud)):
            for j in range(i + 1, len(all_stud)):
                if medii[i] < medii[j]:
                    aux = medii[i]
                    medii[i] = medii[j]
                    medii[j] = aux
                    aux = all_stud[i]
                    all_stud[i] = all_stud[j]
                    all_stud[j] = aux
        return all_stud, medii
    def Transformare_idS_numeS_medieS(self, all_stud, medii_stud):
        '''
        - in acesta functie cream un string pentru afisare
        :param all_stud: o lista cu id-urile studentilor
            type : list
        :param medii_stud: contine media fiecarui elev
            type : list
        :return: stringul care se va afisa
        '''
        rez = ""
        lungime = len(all_stud)
        lungime /= 5
        lungime = int(lungime)
        for i in range(0, lungime):
            idS = all_stud[i]
            stud = self.__repoS.get_stud(idS)
            numeS = stud.get_numeS()
            media = medii_stud[i]
            rez += "id student "+str(idS)+", nume "+str(numeS)+" si media "+str(media)+";\n"
        return rez

    def Stud_ord_medie_sem_ref(self):
        all_stud = self.__repoS.get_all_idS()
        studenti = Repo_cer14(all_stud, self.__repoS, self.__repoN).get_all_values()
        studentii_ordonati = self.GnomeSort(studenti, self.Comparare_medie)
        lungime = len(studentii_ordonati) // 5 # 20%
        return studentii_ordonati[0:lungime]

    def Stud_ord_medie_sem(self):
        '''
        - in acesta functie sortam studentii crescator dupa media lor si returnam un string pentru afisare care contine primii 20%
        '''
        all_stud = self.__repoS.get_all_idS()
        note_stud = []
        for i in all_stud:
            try:
                repoN = RepoN()
                note_stud.append(self.__repoN.Cautare_note_idS_rec(i, 0, repoN, 0)) # lista de obiecte RepoN
            except:
                note_stud.append("")
        medii_stud = []
        for i in note_stud:
            try:
                medii_stud.append(i.Medie_semestru())
            except:
                medii_stud.append(0)
        all_stud, medii_stud = self.Sortare_medie(all_stud, medii_stud)
        rez = self.Transformare_idS_numeS_medieS(all_stud, medii_stud)
        return rez