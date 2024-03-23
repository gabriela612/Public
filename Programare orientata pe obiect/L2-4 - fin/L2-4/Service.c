#include "Service.h"

void CreareListaGoalaServ(OferteS* ofertes)
{
    ofertes->repo = (Oferte*)malloc(sizeof(Oferte));
    CreareListaGoala(ofertes->repo, 5);
    ofertes->li = CreareListaGen(5);
}

Oferte* GetRepo(OferteS* service)
{
    return service->repo;
}

void DistrugereListaServ(OferteS* service)
{
    DistrugereOferte(GetRepo(service));
    for (int i = 1; i <= service->li->lg; i++)
    {
        DistrugereOferte(service->li->elem[i]);
    }
    DistrugeListaGen(service->li);
}

int TestareResdimensionareServ(OferteS* ofertes)
{
    if (GetRepo(ofertes)->lg == GetRepo(ofertes)->cap - 1)
        return 1;
    return 0;
}

void RedimensionareServ(OferteS* service)
{
    Oferte* nou;
    nou = (Oferte*)malloc(sizeof(Oferte));
    CreareListaGoala(nou, 2 * GetRepo(service)->cap);
    CopiereLista(GetRepo(service), nou);
    nou->lg = GetRepo(service)->cap - 1;
    free(GetRepo(service)->elem);
    free(GetRepo(service));
    service->repo = nou;
    // lista de undo
}

int AdaugareServ(OferteS* service, char* tip, int pret, char* data, char * dest)
{
    int eroare;
    eroare = Validare(tip, pret, data, dest);
    if (eroare)
    {
        return eroare;
    }
    Oferta* of;
    of = (Oferta*)malloc(sizeof(Oferta));
    CreareOferta(of, TransformareTip(tip), pret, data, dest);
    assert(TransformareTip("mare") == 2);
    assert(TransformareTip("city_break") == 3);

    if (CautaOferta(*GetRepo(service), *of) != -1)
    {
        free(of);
        return 4;
    }
    
    Oferte *oferte = DeepCopyRepo(service->repo);
    AdaugaListaGen(service->li, oferte);

    Adaugare(GetRepo(service), of);
    if (TestareResdimensionareServ(service))
    {
        RedimensionareServ(service);
    }
    return 0;
}

int StergereServ(OferteS* service, char* tip, int pret, char* data, char * dest)
{
    int eroare;
    eroare = Validare(tip, pret, data, dest);
    if (eroare)
    {
        return eroare;
    }
    Oferta* of;
    of = (Oferta*)malloc(sizeof(Oferta));
    CreareOferta(of, TransformareTip(tip), pret, data, dest);
    int poz;
    poz = CautaOferta(*GetRepo(service), *of);
    free(of);
    if (poz == -1)
    {
        return 4;
    }

    Oferte* oferte = DeepCopyRepo(service->repo);
    AdaugaListaGen(service->li, oferte);

    Stergere(GetRepo(service), poz);
    return 0;
}

int ActualizareServ(OferteS* service, char* tipv, int pretv, char* datav, char * destv, char* tipn, int pretn, char* datan, char * destn)
{
    int eroare;
    eroare = Validare(tipv, pretv, datav, destv);
    if (eroare)
    {
        return eroare;
    }
    eroare = Validare(tipn, pretn, datan, destn);
    if (eroare)
    {
        return eroare;
    }
    Oferta* ofv;
    ofv = (Oferta*)malloc(sizeof(Oferta));
    CreareOferta(ofv, TransformareTip(tipv), pretv, datav, destv);
    Oferta* ofn;
    ofn = (Oferta*)malloc(sizeof(Oferta));
    CreareOferta(ofn, TransformareTip(tipn), pretn, datan, destn);
    int poz;
    poz = CautaOferta(*GetRepo(service), *ofn);
    if (poz != -1)
    {
        free(ofn);
        free(ofv);
        return 5;
    }
    poz = CautaOferta(*GetRepo(service), *ofv);
    free(ofv);
    if (poz == -1)
    {
        free(ofn);
        return 4;
    }

    Oferte* oferte = DeepCopyRepo(service->repo);
    AdaugaListaGen(service->li, oferte);

    Stergere(GetRepo(service), poz);
    Adaugare(GetRepo(service), ofn);
    return 0;
}

void SortarePretDestinatieCrescator(OferteS* ofertes)
{
    Oferte* oferte;
    oferte = GetRepo(ofertes);
    Oferta* of1;
    Oferta* of2;
    for (int i = 1; i <= oferte->lg; i++)
    {
        for (int j = i + 1; j <= oferte->lg; j++)
        {
            of1 = GetOfertaPoz2(oferte, i);
            of2 = GetOfertaPoz2(oferte, j);
            if (of1->pret > of2->pret)
                Interschimba(i, j, oferte);
            else
                if (of1->pret == of2->pret && strcmp(of1->dest, of2->dest) > 0)
                    Interschimba(i, j, oferte);
        }
    }
}

void SortarePretDestinatieDescrescator(OferteS* ofertes)
{
    Oferte* oferte;
    oferte = GetRepo(ofertes);
    Oferta* of1;
    Oferta* of2;
    for (int i = 1; i <= oferte->lg; i++)
    {
        for (int j = i + 1; j <= oferte->lg; j++)
        {
            of1 = GetOfertaPoz2(oferte, i);
            of2 = GetOfertaPoz2(oferte, j);
            if (of1->pret < of2->pret)
                Interschimba(i, j, oferte);
            else
                if (of1->pret == of2->pret && strcmp(of1->dest, of2->dest) < 0)
                    Interschimba(i, j, oferte);
        }
    }
}

void FiltrareDest(OferteS* ofertes, char* dest, OferteS* offil)
{
    CreareListaGoalaServ(offil);
    for (int i = 1; i <= GetRepo(ofertes)->lg; i++)
    {
        if (strcmp(GetRepo(ofertes)->elem[i]->dest, dest) == 0)
        {
            GetRepo(offil)->lg++;
            GetRepo(offil)->elem[GetRepo(offil)->lg] = GetRepo(ofertes)->elem[i];
            if (TestareResdimensionareServ(offil))
                RedimensionareServ(offil);
        }
    }
}

void FiltrarePret(OferteS* ofertes, int pret, OferteS* offil)
{
    CreareListaGoalaServ(offil);
    for (int i = 1; i <= GetRepo(ofertes)->lg; i++)
    {
        if (GetRepo(ofertes)->elem[i]->pret <= pret)
        {
            GetRepo(offil)->lg++;
            GetRepo(offil)->elem[GetRepo(offil)->lg] = GetRepo(ofertes)->elem[i];
            if (TestareResdimensionareServ(offil))
                RedimensionareServ(offil);
        }
    }
}

void FiltrareTip(OferteS* ofertes, char* tip, OferteS* offil)
{
    int t = TransformareTip(tip);
    CreareListaGoalaServ(offil);
    for (int i = 1; i <= GetRepo(ofertes)->lg; i++)
    {
        if (GetRepo(ofertes)->elem[i]->tip == t)
        {
            GetRepo(offil)->lg++;
            GetRepo(offil)->elem[GetRepo(offil)->lg] = GetRepo(ofertes)->elem[i];
            if (TestareResdimensionareServ(offil))
                RedimensionareServ(offil);
        }
    }
}

void FiltrareDestTip(OferteS* ofertes, char* dest, OferteS* offil, char* tip)
{
    int t = TransformareTip(tip);
    CreareListaGoalaServ(offil);
    for (int i = 1; i <= GetRepo(ofertes)->lg; i++)
    {
        if (strcmp(GetRepo(ofertes)->elem[i]->dest, dest) == 0 && GetRepo(ofertes)->elem[i]->tip == t)
        {
            GetRepo(offil)->lg++;
            GetRepo(offil)->elem[GetRepo(offil)->lg] = GetRepo(ofertes)->elem[i];
            if (TestareResdimensionareServ(offil))
                RedimensionareServ(offil);
        }
    }
}

int Undo(OferteS* ser)
{
    if (ser->li->lg == 1)
    {
        return 1;
    }
    DistrugereOferte(ser->repo);
    ser->repo = GetStergeUltimulElemGen(ser->li);
    return 0;
}

void TesteUndo()
{
    OferteS ser;
    CreareListaGoalaServ(&ser);
    AdaugareServ(&ser, "munte", 12, "21.01.2021", "Romania");
    assert(ser.li->lg == 1);
    ActualizareServ(&ser, "munte", 12, "21.01.2021", "Romania", "mare", 12, "21.01.2021", "Romania");
    assert(ser.li->lg == 2);
    AdaugareServ(&ser, "city_break", 12, "21.01.2021", "Romania");
    assert(ser.li->lg == 3);
    StergereServ(&ser, "city_break", 12, "21.01.2021", "Romania");
    assert(ser.repo->lg == 1);
    assert(ser.li->lg == 4);

    Undo(&ser);
    assert(ser.li->lg == 3);
    assert(ser.repo->lg == 2);
    Oferta of;
    CreareOferta(&of, 3, 12, "21.01.2021", "Romania");
    assert(CautaOferta(*ser.repo, of) != -1);
    CreareOferta(&of, 2, 12, "21.01.2021", "Romania");
    assert(CautaOferta(*ser.repo, of) != -1);

    Undo(&ser);
    assert(ser.repo->lg == 1);
    assert(ser.li->lg == 2);
    CreareOferta(&of, 3, 12, "21.01.2021", "Romania");
    assert(CautaOferta(*ser.repo, of) == -1);
    CreareOferta(&of, 2, 12, "21.01.2021", "Romania");
    assert(CautaOferta(*ser.repo, of) != -1);

    DistrugereListaServ(&ser);
}

void TesteS()
{
    OferteS ser;
    CreareListaGoalaServ(&ser);
    assert(GetRepo(&ser)->lg == 0);
    Oferte* oferte;
    Oferta* of = NULL;
    of = (Oferta*)malloc(sizeof(Oferta));
    CreareOferta(of, 1, 100, "12.10.2021", "Romaina");
    oferte = GetRepo(&ser);
    Adaugare(oferte, of); // schimbare
    AdaugareServ(&ser, "munte", 200, "12.10.2020", "Romania");
    assert(GetRepo(&ser)->lg == 2);
    assert(CautaOferta(*oferte, *of) == 1);
    assert(GetPret(*GetOfertaPoz2(oferte, 2)) == 200);

    AdaugareServ(&ser, "munte", 201, "12.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 202, "12.10.2020", "Romania");
    AdaugareServ(&ser, "m", 202, "12.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 203, "12.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 203, "12.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 204, "12.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 205, "12.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 203, "13.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 203, "13.10.2020", "Roma");
    AdaugareServ(&ser, "munte", 203, "14.10.2020", "Romania");
    AdaugareServ(&ser, "munte", 203, "14.10.2020", "R");
    AdaugareServ(&ser, "munte", 203, "14.10.2020", "Ra");
    AdaugareServ(&ser, "munte", 203, "14.10.2020", "Rb");
    AdaugareServ(&ser, "munte", 203, "14.10.2020", "Rc");
    AdaugareServ(&ser, "munte", 203, "14.10.2020", "Rd");;
    AdaugareServ(&ser, "munte", 203, "15.10.2020", "Romania");
    StergereServ(&ser, "munte", 201, "12.10.2021", "Romania");
    StergereServ(&ser, "munte", 203, "12.10.2021", "Romania");
    StergereServ(&ser, "m", 203, "12.10.2021", "Romania");
    StergereServ(&ser, "munte", 203, "15.10.2020", "Romania");
    ActualizareServ(&ser, "munte", 201, "12.10.2020", "Romania", "munte", 2000, "12.10.2020", "Romania");
    ActualizareServ(&ser, "m", 201, "12.10.2020", "Romania", "munte", 2000, "12.10.2020", "Romania");
    ActualizareServ(&ser, "munte", 201, "12.10.2020", "Romania", "m", 2000, "12.10.2020", "Romania");
    ActualizareServ(&ser, "munte", 20120, "15.10.2020", "Romania", "munte", 205, "12.10.2021", "Romania");
    ActualizareServ(&ser, "munte", 201, "12.10.2020", "Romania", "munte", 205, "12.10.2020", "Romania");

    ActualizareServ(&ser, "city_break", 201, "12.10.2020", "Roma", "city_break", 203, "13.10.2020", "Roma");

    SortarePretDestinatieCrescator(&ser);
    SortarePretDestinatieDescrescator(&ser);
    OferteS ofertes;
    FiltrareDest(&ser, "Romania", &ofertes);
    DistrugereLista(ofertes.repo);
    free(ofertes.repo);
    DistrugeListaGen(ofertes.li);
    FiltrarePret(&ser, 203, &ofertes);
    free(ofertes.repo->elem);
    free(ofertes.repo);
    DistrugeListaGen(ofertes.li);
    FiltrareTip(&ser, "munte", &ofertes);
    free(ofertes.repo->elem);
    free(ofertes.repo);
    DistrugeListaGen(ofertes.li);
    FiltrareDestTip(&ser, "munte", &ofertes, "Romania");
    free(ofertes.repo->elem);
    free(ofertes.repo);
    DistrugeListaGen(ofertes.li);
    Oferta of2;
    CreareOferta(&of2, 1, 201, "12.10.2021", "Romania");

    assert(CautaOferta(*GetRepo(&ser), of2) == -1);

    assert(GetRepo(&ser)->cap == 20);

    DistrugereListaServ(&ser);

    TesteUndo();
}

