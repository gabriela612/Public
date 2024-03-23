def real(nr):
    '''
    - in acesta functie returnam partea intreaga a numarului nr
    :param nr: numarul complex
            type : dictionar
    :return: partea reala a numarului complex nr
    '''
    return nr["real"]

def imaginar(nr):
    '''
    - in acesta functie returnam partea imaginara a numarului nr
    :param nr: numarul complex
            type : dictionar
    :return: partea imaginara a numarului complex nr
    '''
    return nr["img"]

def Creare_nr_complex(a, b):
    '''
    - in acesta functie returnam un dictionare care contine numarul complex a+bi
    :param a: partea reala a numarului
        tupe : int
    :param b: partea imaginara a numarului
        type : int
    :return: un dictionar de forma {'real':a, 'img':b}
    '''
    return {'real':a, 'img':b}

def Transformare_cerinta(cer):
    pass