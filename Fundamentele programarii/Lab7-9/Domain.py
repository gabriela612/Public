
class Student:
    nr_stud = 0
    def __init__(self,idS,numeS):
        '''
        :param idS: id-ul studentului
        :param numeS: numele studentului
        '''
        self.__idS = idS
        self.__numeS = numeS
        Student.nr_stud += 1
    def get_numeS(self):
        '''
        :return: numele studentului
        '''
        return self.__numeS
    def get_idS(self):
        '''
        :return: id-ul studentului
        '''
        return self.__idS
    def set_numeS(self, numeS):
        '''
        - in acesta functie inlocuim numele studentului curent cu numeS
        :param numeS: numele cu care se inlocuieste
        '''
        self.__numeS = numeS
    def set_idS(self, idS):
        '''
        - in acesta functie inlocuim id-ul studentului curent cu idS
        :param idS: numele cu care se inlocuieste
        '''
        self.__idS = idS
    def __eq__(self, other):
        '''
        - doua obiecte de tip Student sunt egale daca au acelasi id
        '''
        if self.__idS == other.get_idS():
            return 1
        return 0
    def __str__(self):
        return ' id '+self.__idS+' si nume '+self.__numeS
    @staticmethod
    def get_nr_stud():
        '''
        :return: numarul de studenti creati
        '''
        return Student.nr_stud

class Disciplina:
    nr_di = 0
    def __init__(self, idD, numeD, profD):
        '''
        :param idD: id-ul disciplinei
        :param numeD: numele disciplinei
        :param profD: profesorul disciplinei
        '''
        self.__idD = idD
        self.__numeD = numeD
        self.__profD = profD
        Disciplina.nr_di += 1
    def get_idD(self):
        '''
        :return: id-ul disciplinei
        '''
        return self.__idD
    def get_numeD(self):
        '''
        :return: numele disciplinei
        '''
        return self.__numeD
    def get_profD(self):
        '''
        :return: profesorul disciplinei
        '''
        return self.__profD
    def set_numeD(self, numeD):
        '''
        - in acesta functie inlocuim numele disciplinei curente cu numeD
        :param numeD: numele cu care se inlocuieste
        '''
        self.__numeD = numeD
    def set_idD(self, idD):
        '''
        - in acesta functie inlocuim id-ul disciplinei curente cu idD
        :param idD: id-ul cu care se inlocuieste
        '''
        self.__idD = idD
    def set_profD(self, profD):
        '''
        - in acesta functie inlocuim profesorul disciplinei curente cu profD
        :param profD: profesorul cu care se inlocuieste
        '''
        self.__profD = profD
    def __eq__(self, other):
        '''
        - doua elemente de tip Disciplina sunt egale daca au acelasi id
        '''
        if self.__idD == other.get_idD():
            return 1
        return 0
    def __str__(self):
        return " id "+self.__idD+", nume "+self.__numeD+" si profesor "+self.__profD
    @staticmethod
    def get_nr_di():
        '''
        :return: numarul de discipline create
        '''
        return Disciplina.nr_di

class Nota:
    def __init__(self, idS, idD, nota):
        self.__idS = idS
        self.__idD = idD
        self.__note = []
        for i in nota:
            self.__note.append(i)
    def __eq__(self, other):
        if self.__idS == other.get_idS() and self.__idD == other.get_idS and self.__note == other.get_note():
            return 1
        else:
            return 0
    def Adauga_nota(self, n):
        return self.__note.append(n)
    def get_media(self):
        '''
        - in acesta functie caulculam si returnam media notelor a unui student la o disciplina
        :return: media notelor a unui student la o disciplina
        '''
        media = 0
        for i in self.__note:
            media += float(i)
        return media * 1.0 / len(self.__note)
    def get_idS(self):
        '''
        :return:
        '''
        return self.__idS
    def get_idD(self):
        return self.__idD
    def get_note(self):
        return self.__note
    def get_notaS(self, idS):
        '''
        - in acesta functie returnam notele studentului cu idS
        :param idS: id-ul studentului
        :return: nota studentului cu idS
        '''
        return self.__note
    def get_notaD(self, idD):
        '''
        - in acesta functie returnam nota disciplinei cu idD
        :param idD: id-ul disciplinei
        :return: nota disciplinei cu idD
        '''
    def __str__(self):
        return "id student "+self.__idS+", id disciplina "+self.__idD+" si nota "+str(self.__note)

class Cer12:
    def __init__(self, idS, numeS, noteS):
        self.__idS = idS
        self.__numeS = numeS
        self.__noteS = noteS

    def get_numeS(self):
        return self.__numeS

    def get_idS(self):
        return self.__idS

    def get_noteS(self):
        return self.__noteS

    def __str__(self):
        return "id " + self.__idS + ", nume " + self.__numeS+", note " + str(self.__noteS)

class Cer14:
    def __init__(self, idS, numeS, media):
        self.__idS = idS
        self.__numeS = numeS
        self.__media = media
    def get_media(self):
        return self.__media
    def __str__(self):
        return "id " + self.__idS + ", nume " + self.__numeS + ", media " + str(self.__media)

class ValidatorS:
    def __init__(self):
        self.erori = []
    def Validare_idS(self, idS):
        nr_er = 0
        for i in idS:
            if idS < '0' or idS > '9':
                self.erori.append("Id-ul trebuie sa fie un numar natural. ")
                nr_er += 1
                break
        return nr_er
    def ValidareS(self, stud):
        nr_er = ValidatorS.Validare_idS(self, stud.get_idS())
        if nr_er:
            sir_erori = '\n'.join(self.erori)
            raise Exception(sir_erori)

class ValidatorD:
    def __init__(self):
        self.erori = []
    def Validare_idD(self, idD):
        nr_er = 0
        for i in idD:
            if idD < '0' or idD > '9':
                self.erori.append("Id-ul trebuie sa fie un numar natural. ")
                nr_er += 1
                break
        return nr_er
    def Validare_numeD(self, numeD):
        nr_er = 0
        for i in numeD:
            if i == ' ' or (i >= 'a' and i <= 'z') or (i >= 'A' and i <= 'Z') or (i >= '0' and i <= '9') or i == '-' or i == '+' or i == '&' or i == ':' or i == ',' or i == '/':
                pass
            else:
                self.erori.append("Numele disciplinei este incorect.")
                nr_er += 1
                break
        return nr_er
    def ValidareD(self, di):
        nr_er1 = ValidatorD.Validare_idD(self, di.get_idD())
        nr_er2 = ValidatorD.Validare_numeD(self, di.get_numeD())
        if nr_er1 != 0 or nr_er2 != 0:
            sir_erori = '\n'.join(self.erori)
            raise Exception(sir_erori)

class ValidatorN:
    def __init__(self):
        self.erori = []
    def ValidareN(self, no):
        nota = no.get_note()
        n = 0
        for i in nota:
            n = i
        nota = n
        try:
            if int(nota) > 0 and int(nota) < 11:
                return
        except:
            pass
        raise Exception("Nota trebuie sa fie un numar natural intre 0 si 10.")



