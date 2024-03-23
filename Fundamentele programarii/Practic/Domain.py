
def Creare_data(zi, luna, an):
    '''
    :param zi: ziua (int)
    :param luna: luna (int)
    :param an: anul (int)
    :return: o data formata din ziua, luna si anul primite ca parametrii (data)
    '''
    import datetime
    data = datetime.date(an, luna, zi)
    return data

class Melodie:
    def __init__(self, titlu, artist, gen, data):
        self.__titlu = titlu
        self.__artist = artist
        self.__gen = gen
        self.__data = data
        self.__id = titlu + artist
    def __str__(self):
        return self.__titlu + ", " + self.__artist + ", " + self.__gen + ", " + str(self.__data)
    def get_titlu(self):
        '''
        :return: titlul melodiei
        '''
        return self.__titlu
    def get_artist(self):
        '''
            :return: artistul melodiei
        '''
        return self.__artist
    def get_gen(self):
        '''
        :return: genul melodiei
        '''
        return self.__gen
    def get_data(self):
        '''
        :return: data melodiei
        '''
        return self.__data
    def get_id(self):
        '''
        :return: id-ul melodiei
        '''
        return self.__id
    def set_gen(self, gen):
        '''
        :param gen: noul gen al melodiei
        '''
        self.__gen = gen
    def set_data(self, data):
        '''
        :param data: noua data a melodiei
        '''
        self.__data = data + "\n"

class Validator:
    def __init__(self):
        self.__erori = ""
    def Validare(self, melodie):
        '''
        - in acesta functie verificam daca melodia este una valida
        :param melodie: melodia pe care o verificam (melodie)
        - ridicam erorile daca exista (daca melodia nu e valida)
        '''
        if melodie.get_gen() not in ["Rock", "Pop", "Jazz"]:
            self.__erori += "Genul dat este gresit.\n"
        zi, luna, an = melodie.get_data().split(".")
        try:
            zi = int(zi)
            luna = int(luna)
            an = int(an)
            Creare_data(zi, luna, an)
        except Exception:
            self.__erori += "Data este incorecta.\n"
        if self.__erori != "":
            a = self.__erori
            self.__erori = ""
            raise Exception(a)

def teste():
    melodie = Melodie("M1", "A1", "Rock", "01.01.2001")
    vali = Validator()
    vali.Validare(melodie)
    melodie = Melodie("M1", "A1", "G", "01.01.2001")
    try:
        vali.Validare(melodie)
        assert True, False
    except:
        assert True, True
    melodie = Melodie("M1", "A1", "Jazz", "01.a.2001")
    try:
        vali.Validare(melodie)
        assert True, False
    except:
        assert True, True
    melodie = Melodie("M1", "A1", "Jazz", "01.30.2001")
    try:
        vali.Validare(melodie)
        assert True, False
    except:
        assert True, True
teste()