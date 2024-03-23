
def Cit_cern():
    ccer = input("Introduceti cerita : ")
    cer = ccer.split()
    c = []
    if cer[0] == 'Adauga':
        c.append(0)
    else:
        c.append(1)
    for i in range(1, len(cer)):
        c.append(cer[i])
    return c

def Afisare_meniun():
    print("Cerinta 1 : Adaugarea unui numar complex in lista.")
    print("Cerinta 2 : Modificarea numerelor din lista (stergere).")
