
class Consola:
    def __init__(self, srvS, srvD, srvN):
        '''
        :param srvS: lista de studenti + validator
            type : ServS
        :param srvD: lista de discipline + validator
            type : ServD
        '''
        self.__srvS = srvS
        self.__srvD = srvD
        self.__srvN = srvN

    def AddS_ui(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 1
        '''
        idS = input("Introduceti id-ul studentului : ")
        numeS = input("Introduceti numele studentului : ")
        try:
            stud_adaugat = self.__srvS.AddS_ser(idS, numeS)
            print("Studentul cu", stud_adaugat, "a fost adaugat cu succes!")
        except Exception as er:
            print(er)
        pass

    def AddS_iu_rand(self):
        '''
        - in acesta functie este partea de ui pentru adaugarea unor studenti generati
        '''
        nr = input("Introduceti numarul de studenti care doriti sa fie adaugati : ")
        try:
            nr = int(nr)
        except Exception:
            print("Trebuia sa introduceti un numar.")
        try:
            self.__srvS.AddS_rand(nr)
        except Exception as er:
            print(er)

    def DelS_ui(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 3
        '''
        idS = input("Introduceti id-ul studentului : ")
        try:
            self.__srvS.StergeS_ser(idS)
            print("Studentul a fost sters cu succes.")
        except Exception as er:
            print(er)
        pass

    def CautareS_ui(self):
        '''
        - in acesta functie cautam studentul cu un id citit de la tastatura, apoi il afisam, daca este gasit
        '''
        idS = input("Introduceti id-ul studentului : ")
        try:
            stud = self.__srvS.CautareS_ser(idS)
            print("Studentul cu", str(stud).strip(), "a fost gasit.")
        except Exception as er:
            print("Studentul nu a fost gasit.")

    def AddD_ui(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 2
        '''
        idD = input("Introduceti id-ul disciplinei : ")
        numeD = input("Introduceti numele disciplinei : ")
        profD = input("Introduceti profesorul disciplinei : ")
        try:
            di_adaugata = self.__srvD.AddD_ser(idD, numeD, profD)
            print("Disciplina cu", di_adaugata, "a fost adaugata cu succes!")
        except Exception as er:
            print(er)

    def AddD_iu_rand(self):
        '''
        - in acesta functie este partea de ui pentru adaugarea unor discipline generate
        '''
        nr = input("Introduceti numarul de discipline care doriti sa fie adaugate : ")
        try:
            nr = int(nr)
        except:
            print("Trebuia sa introduceti un numar.")
        try:
            self.__srvD.AddD_rand(nr)
        except Exception as er:
            print(er)

    def DelD_ui(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 5
        :return:
        '''
        idD = input("Introduceti id-ul disciplinei : ")
        try:
            self.__srvD.StergeD_ser(idD)
            print("Disciplina a fost stearsa cu succes.")
        except Exception as er:
            print(er)
        pass

    def CautareD_ui(self):
        '''
        - in acesta functie cautam disciplina cu un id citit de la tastatura, apoi o afisam, daca este gasita
        '''
        idD = input("Introduceti id-ul disciplinei : ")
        try:
            di = self.__srvD.CautareD_ser(idD)
            print("Disciplina cu", str(di).strip(), "a fost gasita.")
        except Exception as er:
            print("Disciplina nu a fost gasita.")

    def AddN_ui(self):
        '''
        - in acesta functie este partea de ui pentru adaugarea unei note la o disciplina si un student
        '''
        idS = input("Introduceti id-ul studentului : ")
        idD = input("Introduceti id-ul disciplinei : ")
        nota = input("Introduceti nota : ")
        try:
            self.__srvN.AddN_ser(idS, idD, nota)
            print("Nota a fost adaugata cu succes.")
        except Exception as er:
            print(er)


    @staticmethod
    def Afisare_meniu():
        '''
        - in acesta functie afisam meniul
        '''
        print("1. Adaugarea unui elev.")
        print("2. Adaugarea unei discipline.")
        print("3. Stergerea unui elev.")
        print("4. Stergerea unei discipline.")
        print("5. Inlocuirea numelui unui student.")
        print("6. Inlocuirea profesorului unei discipline.")
        print("7. Adaugarea unor studenti generati.")
        print("8. Adaugarea unor discipline generate.")
        print("9. Cautarea unui student.")
        print("10. Cautarea unei discipline.")
        print("11. Adaugarea unei note.")
        print("12. Afisarea studentilor (si notele acestora) de la o anumita disciplina ordonati alfabetic dupa nume si dupa nota.")
        print("13. Afisarea disciplinelor in functie de numarul de studenti cu note.")
        print("14. Afisarea primilor 20% de studenti ordontati dupa media la toate disciplinele.")

    @staticmethod
    def Citire_cerinta():
        '''
        - in acesta functie se citeste cerinta
        '''
        cer_cit = input("Introduceti cerinta : ")
        return int(cer_cit)

    @staticmethod
    def Af_msg_er_cer(nr_cer):
        '''
        - in acesta functie afisam un mesaj de eroare cand cerinta este incorecta
        :param nr_cer: numarul maxim pe care cerinta il poate avea
        '''
        print("Trebuia sa introduceti un numar natural intre 1 si", nr_cer)

    def Afisare_studenti(self):
        '''
        - in acesta functie vom afisa lista de studenti
        '''
        print("Studenti :", self.__srvS)

    def Afisare_discipline(self):
        '''
        - in acesta functie vom afisa lista de discipline
        '''
        print("Discipline :", self.__srvD)

    def Afisare_note(self):
        '''
        - in acesta functie vom afisa lista de discipline
        '''
        print("Note :", self.__srvN)

    def Inlocuire_numeS(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 5
        '''
        idS = input("Introduceti id-ul studentului : ")
        nume_nou = input("Introduceti numele nou : ")
        try:
            self.__srvS.Inlocuieste_numeS(idS, nume_nou)
            print("Inlocuirea a fost efectuata cu succes.")
        except Exception as er:
            print(er)

    def Inlocuire_profD(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 6
        '''
        idD = input("Introduceti id-ul disciplinei : ")
        prof_nou = input("Introduceti profesorul nou : ")
        try:
            self.__srvD.Inlocuieste_profD(idD, prof_nou)
            print("Inlocuirea a fost efectuata cu succes.")
        except Exception as er:
            print(er)

    def Studentii_la_idD_ord_alf_ui(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 12
        '''
        idD = input("Introduceti id-ul disciplinei : ")
        try:
            lista_ord = self.__srvN.Studentii_la_idD_ord_alf_ref(idD)
            print("Lista este:\n")
            for i in lista_ord:
                print(i)
        except Exception as er:
            print(er)

    def Disciplinele_ord_nrstud_ui(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 13
        '''
        try:
            lista_di_ord = self.__srvN.Disciplinele_ord_nrstud()
            print("Lista este:\n", lista_di_ord)
        except Exception as er:
            print(er)

    def Stud_ord_medie_sem_ui(self):
        '''
        - in acesta functie este partea de ui pentru rezolvarea cerintei 14
        '''
        try:
            lista_stud_ord = self.__srvN.Stud_ord_medie_sem_ref()
            print("Lista este:\n")
            for i in lista_stud_ord:
                print(i)
        except Exception as er:
            print(er)

    def Inceput_ui(self):
        '''
        - in acesta functie citim cerinta si apelam o functie care va conduce la efectuarea rezolvarii cerintei
        '''
        while True:
            print("\n")
            self.Afisare_studenti()
            self.Afisare_discipline()
            self.Afisare_note()
            cerinte = [0, self.AddS_ui, self.AddD_ui, self.DelS_ui, self.DelD_ui, self.Inlocuire_numeS, self.Inlocuire_profD, self.AddS_iu_rand, self.AddD_iu_rand, self.CautareS_ui, self.CautareD_ui, self.AddN_ui, self.Studentii_la_idD_ord_alf_ui, self.Disciplinele_ord_nrstud_ui, self.Stud_ord_medie_sem_ui]
            Consola.Afisare_meniu()
            try:
                cer_cit = Consola.Citire_cerinta()
                if type(cer_cit) != int or cer_cit < 1 or cer_cit > len(cerinte) + 1:
                    raise Exception
                cerinte[cer_cit]()
            except Exception:
                Consola.Af_msg_er_cer(len(cerinte) - 1)



