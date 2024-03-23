#include "UI.h"
#include "Service.h"

void AfisareMeniu()
{
    printf("0. Iesire.");
    printf("\n1. Adaugare oferta.");
    printf("\n2. Stergere oferta.");
    printf("\n3. Actualizare oferta.");
    printf("\n4. Afisare oferte ordonate dupa pret si destinatie.");
    printf("\n5. Filtrare dupa un criteriu dat.");
    printf("\n6. Undo.");
    printf("\n7. Afisare oferte.\n");
}

int CitireCerinta()
{
    int cerinta;
    printf("Introduceti cerinta : ");
    scanf_s("%d", &cerinta);
    return cerinta;
}

void AdaugareUI(OferteS* ofertes)
{
    int pret, eroare;
    char tip[20], data[20], dest[20];
    printf("Introduceti tipul : ");
    scanf_s("%s", tip, sizeof(tip));
    printf_s("Introduceti pretul : ");
    scanf_s("%d", &pret);
    printf("Introduceti data : ");
    scanf_s("%s", data, sizeof(data));
    printf("Introduceti destinatia : ");
    scanf_s("%s", dest, sizeof(dest));

    eroare = AdaugareServ(ofertes, tip, pret, data, dest);
    switch (eroare)
    {
    case 0:
        printf("Adaugarea a fost efectuata cu succes!\n");
        break;
    case 1:
        printf("Tipul trebuie sa fie ,,munte``, ,,mare`` sau ,,city_break``.\n");
        break;
    case 2:
        printf("Pretul trebuie sa fie un numar natural.\n");
        break;
    case 3:
        printf("Data trebuie sa fie una valida si de forma zz.ll.aaaa .\n");
        break;
    case 4:
        printf("Oferta exista deja.\n");
    }
}

void StergereIU(OferteS* ofertes)
{
    int pret, eroare;
    char tip[20], data[20], dest[20];
    printf("Introduceti tipul : ");
    scanf_s("%s", tip, sizeof(tip));
    printf_s("Introduceti pretul : ");
    scanf_s("%d", &pret);
    printf("Introduceti data : ");
    scanf_s("%s", data, sizeof(data));
    printf("Introduceti destinatia : ");
    scanf_s("%s", dest, sizeof(dest));

    eroare = StergereServ(ofertes, tip, pret, data, dest);
    switch (eroare)
    {
    case 0:
        printf("Stergerea a fost efectuata cu succes!\n");
        break;
    case 1:
        printf("Tipul trebuie sa fie ,,munte``, ,,mare`` sau ,,city_break``.\n");
        break;
    case 2:
        printf("Pretul trebuie sa fie un numar natural.\n");
        break;
    case 3:
        printf("Data trebuie sa fie una valida si de forma zz.ll.aaaa .\n");
        break;
    case 4:
        printf("Oferta nu exista.\n");
    }
}

void ActualizareIU(OferteS* ofertes)
{
    int pretn, pretv, eroare;
    char tipn[20], datan[20], tipv[20], datav[20], destv[20], destn[20];
    printf("Introduceti tipul vechi : ");
    scanf_s("%s", tipv, sizeof(tipv));
    printf_s("Introduceti pretul vechi : ");
    scanf_s("%d", &pretv);
    printf("Introduceti data veche : ");
    scanf_s("%s", datav, sizeof(datav));
    printf("Introduceti destinatia veche : ");
    scanf_s("%s", destv, sizeof(destv));

    printf("Introduceti tipul nou : ");
    scanf_s("%s", tipn, sizeof(tipn));
    printf_s("Introduceti pretul nou : ");
    scanf_s("%d", &pretn);
    printf("Introduceti data noua : ");
    scanf_s("%s", datan, sizeof(datan));
    printf("Introduceti destinatia noua : ");
    scanf_s("%s", destn, sizeof(destn));

    eroare = ActualizareServ(ofertes, tipv, pretv, datav, destv, tipn, pretn, datan, destn);
    switch (eroare)
    {
    case 0:
        printf("Actualizarea a fost efectuata cu succes!\n");
        break;
    case 1:
        printf("Tipul trebuie sa fie ,,munte``, ,,mare`` sau ,,city_break``.\n");
        break;
    case 2:
        printf("Pretul trebuie sa fie un numar natural.\n");
        break;
    case 3:
        printf("Data trebuie sa fie una valida si de forma zz.ll.aaaa .\n");
        break;
    case 4:
        printf("Oferta nu exista.\n");
        break;
    case 5:
        printf("Actualizare neefectuata. Exista deja oferta actualizata.\n");
        break;
    }
}

void AfisareOferte(OferteS* ofertes)
{
    printf("Ofertele sunt :\n");
    printf("%10s %12s %10s %17s %10s", "Tip", "Pret", "Data", "Destinatie", "\n");
    for (int i = 1; i <= GetRepo(ofertes)->lg; i++)
    {
        Oferta *of = GetOfertaPoz2(GetRepo(ofertes), i);
        if (of->tip == 1)
            printf("       munte        %d %15s %10s\n", of->pret, of->data, of->dest);
        if (of->tip == 2)
            printf("       mare         %d %15s %10s\n", of->pret, of->data, of->dest);
        if (of->tip == 3)
            printf("       city_break   %d %15s %10s\n", of->pret, of->data, of->dest);
    }

}

void SortarePretDestinatieUI(OferteS* ser)
{
    int desc;
    printf("Introduceti 0 daca vreti o sortare crescatoare si 1 daca vreti o sortare descrescatoare : ");
    scanf_s("%d", &desc);
    if (desc)
        SortarePretDestinatieDescrescator(ser);
    else
        SortarePretDestinatieCrescator(ser);
    AfisareOferte(ser);
}

void FiltrareUI(OferteS* ser)
{
    int opt;
    printf("1. Filtrare dupa destinatie (toate oferte care au destinatia data).\n");
    printf("2. Filtrare dupa pret (toate ofertele care au pretul mai mic sau egal cu cel dat).\n");
    printf("3. Filtrare dupa tip (toate ofertele care au tipul dat).\n");
    printf("4. Filtrare dupa destinatie si tip.\n");
    printf("Introduceti optiunea : ");
    scanf_s("%d", &opt);
    OferteS offil;
    if (opt == 1)
    {
        char dest[20];
        printf("Introduceti destinatia : ");
        scanf_s("%s", dest, sizeof(dest));
        FiltrareDest(ser, dest, &offil);
    }
    if (opt == 2)
    {
        int pret;
        printf("Introduceti pretul : ");
        scanf_s("%d", &pret);
        if (pret < 0)
        {
            printf("Pretul trebuie sa fie un numar pozitiv.\n");
            return;
        }
        FiltrarePret(ser, pret, &offil);
    }
    if (opt == 3)
    {
        char tip[20];
        printf("Introduceti tipul : ");
        scanf_s("%s", tip, sizeof(tip));
        printf("Introduceti tipul : ");
        if (strcmp(tip, "munte") != 0 && strcmp(tip, "mare") != 0 && strcmp(tip, "city_break") != 0)
        {
            printf("Tipul trebuie sa fie, , munte``,, , mare`` sau, , city_break``.\n");
            return;
        }
        FiltrareTip(ser, tip, &offil);
    }

    if (opt == 4)
    {
        char dest[20];
        printf("Introduceti destinatia : ");
        scanf_s("%s", dest, sizeof(dest));
        
        char tip[20];
        printf("Introduceti tipul : ");
        scanf_s("%s", tip, sizeof(tip));
        printf("Introduceti tipul : ");
        if (strcmp(tip, "munte") != 0 && strcmp(tip, "mare") != 0 && strcmp(tip, "city_break") != 0)
        {
            printf("Tipul trebuie sa fie, , munte``,, , mare`` sau, , city_break``.\n");
            return;
        }

        FiltrareDestTip(ser, dest, &offil, tip);
    }

    if (opt != 1 && opt != 2 && opt != 3 && opt != 4)
        return;
    AfisareOferte(&offil);
    free(offil.repo->elem);
    free(offil.repo);
    DistrugeListaGen(offil.li);
}

void UndoUI(OferteS* ser)
{
    int eroare = Undo(ser);
    if (eroare)
        printf("Nu s-a putut face undo.\n");
}

void ApelareCerinta(int cer, OferteS* ser)
{
    switch (cer)
    {
    case 1:
        AdaugareUI(ser);
        break;
    case 2:
        StergereIU(ser);
        break;
    case 3:
        ActualizareIU(ser);
        break;
    case 4:
        SortarePretDestinatieUI(ser);
        break;
    case 5:
        FiltrareUI(ser);
        break;
    case 6:
        UndoUI(ser);
        break;
    case 7:
        AfisareOferte(ser);
        break;
    }
}

void Inceput(OferteS* ser)
{
    while (1)
    {
        AfisareMeniu();
        int cer = CitireCerinta();
        if (cer == 0)
            break;
        printf("\n");
        ApelareCerinta(cer, ser);
        printf("\n");
    }
}



