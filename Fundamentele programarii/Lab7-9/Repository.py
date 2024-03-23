from Domain import Student
from Domain import Disciplina
from Domain import Nota
from Domain import Cer12
from Domain import Cer14

class RepoS:
    def __init__(self):
        '''
        self.__listaS : lista de studenti, care initial, nu contine studenti
        '''
        self.__listaS = {}
    def __str__(self):
        a = ''
        for i in self.__listaS.values():
            a = a + str(i)
            a = a + ','
        return a
    def get_all_values(self):
        return self.__listaS.values()
    def get_all_idS(self):
        rez = []
        for i in self.__listaS.keys():
            rez.append(i)
        return rez
    def get_stud(self, idS):
        '''
        - in acesta functie returnam studentul cu id-ul idS
        :param idS: id-ul studentului
        '''
        try:
            return self.__listaS[idS]
        except:
            raise Exception("Id-ul studentului nu exista.")

    def get_nr_stud(self):
        '''
        - calculeaza si returneaza numarul de studenti din lista
        :return: numarul de studenti din lista
        '''
        return len(self.__listaS)

    def Exista_dejaS(self, idS):
        '''
        - in acesta functie cream o exceptie pentru cazul in care este deja un student care are idS
        :param idS: id-ul pe care il cautam
        '''
        try:
            a = self.__listaS[idS]
        except:
            return
        raise Exception("Id-ul studentului exista deja.")

    def Adauga_in_lista(self, stud):
        '''
        - in acesta functie adaugam un student in lista
        :param stud: studentul care se adauga la lista
        '''
        self.__listaS[stud.get_idS()] = stud
        return self.__listaS
    def StergeS(self, idS):
        '''
        - in acesta funtie stergem studentul care are id-ul egal cu idS
        :param idS: id-ul studentuli care urmeaza sa fie sters
        '''
        try:
            del self.__listaS[idS]
        except:
            raise Exception("Id-ul studentului nu exista.")
    def Inlocuieste_numeS(self, idS, nume_nou):
        '''
        - in acesta functie inlocuim numele studentului cu id-ul idS, cu nume_nou
        :param idS: id-ul studentului al carui nume il modificam
            type : unsigned int
        :param nume_nou: numele cu care inlocuim
            type : string
        '''
        try:
            self.__listaS[idS].set_numeS(nume_nou)
        except:
            raise Exception("Id-ul studentului nu exista.")

class RepoSf(RepoS):
    def Citire_fisier(self):
        f = open("Studenti.txt", "r+")
        for i in f.readlines():
            idS, numeS = i.split("; ")
            l = len(numeS) - 1
            numeS = numeS[0:l]
            stud = Student(idS, numeS)
            RepoS.Adauga_in_lista(self, stud) # se adauga numai in lista din program
        f.close()
    def Rescriere_fisier(self):
        f = open("Studenti.txt", "w")
        for i in self.get_all_values():
            f.write(i.get_idS()+"; "+i.get_numeS()+"\n")
        f.close()
    def Adauga_in_lista(self, stud):
        RepoS.Adauga_in_lista(self, stud)
        f = open("Studenti.txt", "a")
        f.write(stud.get_idS()+"; "+stud.get_numeS()+"\n")
        f.close()
    def StergeS(self, idS):
        RepoS.StergeS(self, idS)
        self.Rescriere_fisier()
    def Inlocuieste_numeS(self, idS, nume_nou):
        RepoS.Inlocuieste_numeS(self, idS, nume_nou)
        self.Rescriere_fisier()

class RepoD:
    def __init__(self):
        '''
        self.__listaD : lista de discipline, care initial, nu contine discipline
        '''
        self.__listaD = {}
    def __str__(self):
        a = ''
        for i in self.__listaD.values():
            a = a + str(i)
            a = a + ';'
        return a
    def get_all_values(self):
        return self.__listaD.values()
    def get_all_idD(self):
        rez = []
        for i in self.__listaD.keys():
            rez.append(i)
        return rez

    def get_di(self, idD):
        '''
        - in acesta functie returnam disciplina cu id-ul idD
        :param idD: id-ul disciplinei
        '''
        try:
            return self.__listaD[idD]
        except:
            raise Exception("Id-ul disciplinei nu exista.")
    def get_nr_di(self):
        '''
        - calculeaza si returneaza numarul de discipline din lista
        :return: numarul de discipline din lista
        '''
        return len(self.__listaD)
    def Exista_dejaD(self, idD):
        '''
        - in acesta functie cream o exceptie pentru cazul in care este deja un student care are idS
        :param idD: id-ul pe care il cautam
        '''
        try:
            a = self.__listaD[idD]
        except:
            return
        raise Exception("Id-ul disciplinei exista deja.")
    def Adauga_in_lista(self, di):
        '''
        - in acesta functie adaugam o disciplina in lista
        :param di: disciplina care se adauga la lista
        '''
        self.__listaD[di.get_idD()] = di
    def StergeD(self, idD):
        '''
        - in acesta funtie stergem disciplina care are id-ul egal cu idD
        :param idD: id-ul disciplinei care urmeaza sa fie stearsa
        '''
        try:
            del self.__listaD[idD]
        except:
            raise Exception("Id-ul disciplinei nu exista.")
    def Inlocuieste_profD(self, idD, prof_nou):
        '''
        - in acesta functie inlocuim profesorul disciplinei cu id-ul idD, cu prof_nou
        :param idD: id-ul disciplinei a carei profesor trebuie sa il inlocuim
            type : string
        :param prof_nou: profesorul cu care inlocuim
            type : string
        '''
        try:
            self.__listaD[idD].set_profD(prof_nou)
        except:
            raise Exception("Id-ul disciplinei nu exista.")

class RepoDf(RepoD):
    def Citire_fisier(self):
        f = open("Discipline.txt", "r+")
        for i in f.readlines():
            idD, numeD, profD = i.split("; ")
            l = len(profD) - 1
            profD = profD[0:l]
            di = Disciplina(idD, numeD, profD)
            RepoD.Adauga_in_lista(self, di) # se adauga numai in lista din program
        f.close()
    def Rescriere_fisier(self):
        f = open("Discipline.txt", "w")
        for i in self.get_all_values():
            f.write(i.get_idD()+"; "+i.get_numeD()+"; "+i.get_profD()+"\n")
        f.close()
    def Adauga_in_lista(self, di):
        RepoD.Adauga_in_lista(self, di)
        f = open("Discipline.txt", "a")
        f.write(di.get_idD() + "; " + di.get_numeD() + "; " + di.get_profD() + "\n")
        f.close()
    def StergeD(self, idD):
        RepoD.StergeD(self, idD)
        self.Rescriere_fisier()
    def Inlocuieste_profD(self, idD, prof_nou):
        RepoD.Inlocuieste_profD(self, idD, prof_nou)
        self.Rescriere_fisier()

class RepoN: #Catalog
    def __init__(self):
        self.__listaN = []
    def __str__(self):
        a = ''
        for i in self.__listaN:
            a = a + str(i)
            a = a + '; '
        return a
    def __eq__(self, other):
        for i in range(min(len(self.__listaN), len(other.get_all_values()))):
            if self.__listaN[i] != other.get_all_values()[i]:
                return 0
        return 1
    def get_all_values(self):
        return self.__listaN
    def get_len(self):
        return len(self.__listaN)
    def get_id_stud_poz(self, poz):
        nota = self.__listaN[poz]
        return nota.get_idS()
    def get_note_stud_poz(self, poz):
        nota = self.__listaN[poz]
        return nota.get_note()
    def get_nr_stud_pt_di(self, idD):
        rez = 0
        for i in self.__listaN:
            if i.get_idD() == idD:
                rez += 1
        return rez
    def AdaugareN(self, nota):
        '''
        - in acesta functie adaugam o nota la lista
        :param nota: nota pe care o adaugam (contine valoarea notei, id-ul disciplinei si id-ul studentului)
            type : Nota
        '''
        self.__listaN.append(nota)
    def Interschimba(self, poz1, poz2):
        aux = self.__listaN[poz1]
        self.__listaN[poz1] = self.__listaN[poz2]
        self.__listaN[poz2] = aux

    def Cautare_note_idS_rec(self, idS, i, repoN, e):
        if i >= len(self.__listaN):
            if e == 0:
                raise Exception("Studentul cu id-ul dat nu are note.")
            else:
                return repoN
        if self.__listaN[i].get_idS() == idS:
            repoN.AdaugareN(self.__listaN[i])
            e = 1
        return self.Cautare_note_idS_rec(idS, i + 1, repoN, e)

    def Cautare_note_idS(self, idS):
        '''
        - in acesta functie cautam notele studentului cu id-ul idS
        :param idS: id-ul studentului
            type : string
        :return: notele studentului cu id-ul idS (se returneaza un obiect de tip RepoN)
        '''
        rez = RepoN()
        exista = 0
        for i in self.__listaN:
            if i.get_idS() == idS:
                rez.AdaugareN(i)
                exista = 1
        if exista == 0:
            raise Exception("Studentul cu id-ul dat nu are note.")
        return rez
    def Cautare_note_idD(self, idD):
        '''
        - in acesta functie cautam notele de la disciplina cu id-ul idD
        :param idD: id-ul disciplinei
            type : string
        :return: notele disciplinei cu id-ul idD (se returneaza un obiect de tip RepoN)
        '''
        rez = RepoN()
        exista = 0
        for i in self.__listaN:
            if i.get_idD() == idD:
                rez.AdaugareN(i)
                exista = 1
        if exista == 0:
            raise Exception("Disciplina cu id-ul dat nu are note.")
        return rez

    def Cautare_pozitie_idS_idD_rec(self, idS, idD, i):
        if i >= len(self.__listaN):
            raise Exception("Studentul dat nu are nicio nota la disciplina data.")
        if self.__listaN[i].get_idS() == idS and self.__listaN[i].get_idD() == idD:
            return i
        return self.Cautare_pozitie_idS_idD_rec(idS, idD, i + 1)

    def Cautare_pozitie_idS_idD(self, idS, idD):
        '''
        - in acesta functie cautam si returnam pozitia pe care se afla elementul cu idS si idD ca id stud si id di
        :param idS: id-ul studentului
        :param idD: id-ul disciplinei
        :return: returnam pozitia pe care se afla elementul cu idS si idD ca id stud si id di
        '''
        for i in range(0, len(self.__listaN)):
            if self.__listaN[i].get_idS() == idS and self.__listaN[i].get_idD() == idD:
                return i
        raise Exception("Studentul dat nu are nicio nota la disciplina data.")
    def Adaugare_nota_la_lista_de_note(self, poz, nota):
        '''
        - in acesta functie adaugam o nota la lista de note a unui student la o disciplina
        :param nota: nota pe care o adaugam
        '''
        self.__listaN[poz].Adauga_nota(nota)
    def Medie_semestru(self):
        '''
        :return: media pentru semestru la toate elementele din lista
        '''
        media = 0
        for i in self.__listaN:
            media += i.get_media()
        return media * 1.0 / len(self.__listaN)

class RepoNf(RepoN):
    def Citire_fisier(self):
        f = open("Note.txt", "r+")
        for i in f.readlines():
            idS, idD, nota = i.split("; ")
            l = len(nota) - 2
            nota = nota[0:l]
            if ',' in nota:
                nota = nota.split(",")
            else:
                nota = [nota]
            no = Nota(idS, idD, nota)
            RepoN.AdaugareN(self, no) # se adauga numai in lista din program
        f.close()
    def Rescriere_fisier(self):
        f = open("Note.txt", "w")
        f.write("")
        f.close()
        f = open("Note.txt", "a")
        for i in self.get_all_values():
            f.write(i.get_idS()+"; "+i.get_idD()+"; ")
            note = i.get_note()
            for i in note:
                f.write(i+",")
            f.write("\n")
        f.close()
    def AdaugareN(self, no):
        try:
            RepoN.AdaugareN(self, no)
            f = open("Note.txt", "a")
            note = no.get_note()
            f.write(no.get_idS() + "; " + no.get_idD() + "; ")
            for i in note:
                f.write(i+", ")
            f.write("\n")
            f.close()
        except Exception as er:
            print(er)
    def Adaugare_nota_la_lista_de_note(self, poz, nota):
        RepoN.Adaugare_nota_la_lista_de_note(self, poz, nota)
        self.Rescriere_fisier()

class Repo_cer12:
    def __init__(self, note_di, repoS):
        self.__note_di = []
        self.Adaugare_note(note_di, repoS)
    def Adaugare_note(self, note_di, repoS):
        for i in range(0, note_di.get_len()):
            idS = note_di.get_id_stud_poz(i)
            stud = repoS.get_stud(idS)
            numeS = stud.get_numeS()
            noteS = note_di.get_note_stud_poz(i)
            noteS.sort()
            self.__note_di.append(Cer12(idS, numeS, noteS))
    def get_all_values(self):
        return self.__note_di
    def __str__(self):
        rez = ""
        for i in self.__note_di:
            rez = rez + str(i) + "\n"
        return rez

class Repo_cer14:
    def __init__(self, id_studenti, repoS, repoN):
        self.__serv14 = []
        self.Adaugare_studenti(id_studenti, repoS, repoN)
    def Adaugare_studenti(self, id_studenti, repoS, repoN):
        for i in id_studenti:
            stud = repoS.get_stud(i)
            nume_stud = stud.get_numeS()
            try:
                repoNo = RepoN()
                note_stud = repoN.Cautare_note_idS_rec(i, 0, repoNo, 0) # se returneaza un obiect de tip RepoN
            except:
                note_stud = ''
            try:
                media = note_stud.Medie_semestru()
            except:
                media = 0
            self.__serv14.append(Cer14(i, nume_stud, media))
    def get_all_values(self):
        return self.__serv14
    def __str__(self):
        rez = ''
        for i in self.__serv14:
            rez += str(i) + "\n"
        return rez

def Test_addS_repo():
    dictionar = RepoS()
    s1 = Student('1', 'Gabi')
    dictionar.Adauga_in_lista(s1)
    assert str(dictionar) == " id 1 si nume Gabi,"
    s2 = Student('1', 'Gabriela')
    dictionar.Adauga_in_lista(s2)
    assert str(dictionar) == " id 1 si nume Gabriela," # verificarea daca id-ul exista se face in service
    s3 = Student('2', 'G')
    dictionar.Adauga_in_lista(s3)
    assert str(dictionar) == " id 1 si nume Gabriela, id 2 si nume G,"

def Test_stergeS_repo():
    dictionar = RepoS()
    s1 = Student('1', 'Gabi')
    dictionar.Adauga_in_lista(s1)
    s3 = Student('2', 'G')
    dictionar.Adauga_in_lista(s3)
    dictionar.StergeS('1')
    assert str(dictionar) == " id 2 si nume G,"
    dictionar.StergeS('2')
    assert str(dictionar) == ""

def Test_inlocuieste_numeS():
    dictionar = RepoS()
    s1 = Student('1', 'Gabi')
    dictionar.Adauga_in_lista(s1)
    s3 = Student('2', 'G')
    dictionar.Adauga_in_lista(s3)
    dictionar.Inlocuieste_numeS('1', 'Gabriela')
    assert str(dictionar) == " id 1 si nume Gabriela, id 2 si nume G,"
    dictionar.Inlocuieste_numeS('1', 'Gabi')
    assert str(dictionar) == " id 1 si nume Gabi, id 2 si nume G,"

def Test_addD_repo():
    dictionar = RepoD()
    di1 = Disciplina('1', 'Info', 'Gabi')
    dictionar.Adauga_in_lista(di1)
    assert str(dictionar) == " id 1, nume Info si profesor Gabi;"
    di2 = Disciplina('1', 'Info', 'Gabriela')
    dictionar.Adauga_in_lista(di2)
    assert str(dictionar) == " id 1, nume Info si profesor Gabriela;" # verificarea daca id-ul exista se face in service
    di3 = Disciplina('2','Info', 'G')
    dictionar.Adauga_in_lista(di3)
    assert str(dictionar) == " id 1, nume Info si profesor Gabriela; id 2, nume Info si profesor G;"

def Test_stergeD_repo():
    dictionar = RepoD()
    di1 = Disciplina('1', 'Info', 'Gabi')
    dictionar.Adauga_in_lista(di1)
    di3 = Disciplina('2', 'Info', 'G')
    dictionar.Adauga_in_lista(di3)
    dictionar.StergeD('1')
    assert str(dictionar) == " id 2, nume Info si profesor G;"
    dictionar.StergeD('2')
    assert str(dictionar) == ""

def Test_inlocuieste_profD():
    dictionar = RepoD()
    di1 = Disciplina('1', 'Info', 'Gabi')
    dictionar.Adauga_in_lista(di1)
    di3 = Disciplina('2', 'Info', 'G')
    dictionar.Adauga_in_lista(di3)
    dictionar.Inlocuieste_profD('1', 'Gabriela')
    assert str(dictionar) == " id 1, nume Info si profesor Gabriela; id 2, nume Info si profesor G;"
    dictionar.Inlocuieste_profD('1', 'Gabi')
    assert str(dictionar) == " id 1, nume Info si profesor Gabi; id 2, nume Info si profesor G;"

def Teste_repo():
    Test_addS_repo()
    Test_addD_repo()
    Test_stergeS_repo()
    Test_stergeD_repo()
    Test_inlocuieste_numeS()
    Test_inlocuieste_profD()


