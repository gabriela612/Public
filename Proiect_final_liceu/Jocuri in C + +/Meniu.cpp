#include <iostream>
#include <algorithm>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

istream&  ignore ( streamsize n = 1, int delim = EOF );

ifstream spin("cuvintesp.in");
ifstream tin("forme.in");
ifstream qin("intrebari.in");
ifstream scin("istoric.txt");
ifstream scout("istoric.txt");

int scj1, scj2, nrvieti, fr[200], nrlit, jocnou, randjocsp, n_lit_fol, sc, nrincercari, cuv_rand, scp, nrcuv, intr_rand, nr_intr, jucat, rand_co = 0, tt[35][35], nr_forme, fcu, stop_joc, nist, ata;
double rasp_dat, nrjoc, nrj;
char nume1[100], nume2[100], nume[100], cuv[100], lit_folosite[100], litsp, lista_cuv[200][20];

void Meniu();
void Citire_suplimentar();

struct Istoric
{
    int joc, scor;
    char num[105];
} ist[1005];

bool Sortare_ist(Istoric a, Istoric b)
{
    if (a.scor > b.scor)
        return 1;
    else
        return 0;
}

void Modificare_istoric(int j, char nume[100])
{
    if (sc > ist[nist].scor or nist < 100)
    {
        nist ++;
        ist[nist].joc = j;
        ist[nist].scor = sc;
        strcpy(ist[nist].num, nume);
    }
    fstream scout("istoric.txt", ios::out);
    for (int i = 1; i <= nist; i ++)
    {
        scout << ist[i].joc << " " << ist[i].scor << "\n" << ist[i].num << "\n";
    }
    sort(ist + 1, ist + 1 + nist, Sortare_ist);
    scout.close();
}

void Afisare_ist(int j)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n\n";
    cout << "    NUME ";
    for (int i = 1; i <= 20 - strlen("NUME"); i ++)
        cout << " ";
    cout << "SCOR\n";
    int w = 1;
    for (int i = 1; i <= nist; i ++)
    {
        if (ist[i].joc == j)
        {
            cout << w ++ << ".";
            if (w <= 10)
                cout << " ";
            if (w < 5)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            else
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << " " << ist[i].num << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            for (int j = 1; j <= 20 - strlen(ist[i].num); j ++)
            {
                cout << " ";
            }
            if (w < 5)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            else
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << ist[i].scor << "\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }

    }
    cout << "\n\n";
}

struct Patrat
{
    int ip, jp;
};

struct Forma
{
    Patrat coord[5]; /// coordonate
} forma[200], forma_curenta;

bool Testare_asezare_forma__tt()
{
    bool test = 1;
    for (int i = 1; i < 5; i ++)
    {
        if (tt[forma_curenta.coord[i].ip + 1][forma_curenta.coord[i].jp] == 1)
            return 1;
    }
    return 0;
}

void Schimbare_directie_tt(char x)
{
    if (x == 'S' or x == 's')
    {
        int test = 1;
        for (int i = 1; i < 5; i ++)
        {
            if (tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp - 1] == 1)
                test = 0;
        }
        if (test)
        {
            for (int i = 1; i < 5; i ++)
            {
                tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 0;
                forma_curenta.coord[i].jp --;
            }
            for (int i = 1; i < 5; i ++)
                tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 2;
        }
    }
    if (x == 'D' or x == 'd')
    {
        int test = 1;
        for (int i = 1; i < 5; i ++)
        {
            if (tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp + 1] == 1)
                test = 0;
        }
        if (test)
        {
            for (int i = 1; i < 5; i ++)
            {
                tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 0;
                forma_curenta.coord[i].jp ++;
            }
            for (int i = 1; i < 5; i ++)
                tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 2;
        }
    }
}

void Coborare_forma_tt()
{
    for (int i = 1; i < 5; i ++)
    {
        tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 0;
        forma_curenta.coord[i].ip ++;
    }
    for (int i = 1; i < 5; i ++)
    {
        tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 2;
    }
}

void Afisare_matrice_tt()
{
    for (int i = 1; i <= 30; i ++)
    {
        for (int j = 1; j <= 30; j ++)
        {
            if (!tt[i][j])
                cout << "  ";
            else if (tt[i][j] == 1)
            {
                if (i == 1 or j == 1 or i == 30 or j == 30)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);
                    cout << "  ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 101);
                    cout << "  ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                }
            }
            else if (tt[i][j] == 2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
                cout << "  ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            }
        }
        cout << "\n";
    }
}

bool Testare_joc_terminat_tt()
{
    for (int i = 2; i < 5; i ++)
    {
        for (int j = 2; j < 30; j ++)
        {
            if (tt[i][j] == 1)
                return 1;
        }
    }
    return 0;
}

void Asezare_forma_tt()
{
    for (int i = 1; i < 5; i ++)
    {
        tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 1;
    }
    sc += 4;
    Beep(300,150);
}

void Alegere_forma_tt()
{
    fcu = rand() % nr_forme;
    for (int i = 1; i < 5; i ++)
    {
        forma_curenta.coord[i].ip = forma[fcu].coord[i].ip;
        forma_curenta.coord[i].jp = forma[fcu].coord[i].jp;
        tt[forma_curenta.coord[i].ip][forma_curenta.coord[i].jp] = 2;
    }
}

void Eliminare_rand_tt(int x)
{
    system ("CLS");
    for (int i = 1; i <= 30; i ++)
    {
        for (int j = 1; j <= 30; j ++)
        {
            if (!tt[i][j])
                cout << "  ";
            else if (tt[i][j] == 1)
            {
                if (i != x)
                {
                    if (i == 1 or j == 1 or i == 30 or j == 30)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);
                        cout << "  ";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                    }
                    else
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 101);
                        cout << "  ";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                    }
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 60);
                    cout << "  ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                }
            }
            else if (tt[i][j] == 2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
                cout << "  ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
            }
        }
        cout << "\n";
    }
    Beep(300,150);
    Beep(600,200);
    for (int i = x; i > 2; i --)
    {
        for (int j = 2; j < 30; j ++)
        {
            tt[i][j] = tt[i - 1][j];
        }
    }
    for (int j = 2; j < 3; j ++)
        tt[2][j] = 0;
    sc += 60;
}

void Rand_complet_tt()
{
    int test;
    for (int i = 1; i < 5; i ++)
    {
        test = 1;
        for (int j = 2; j < 30; j ++)
        {
            test *= tt[forma_curenta.coord[i].ip][j];
        }
        if (test)
            Eliminare_rand_tt(forma_curenta.coord[i].ip);
    }
}

void Tetris()
{
    if (jucat)
    {
        for (int i = 2; i < 30; i ++)
        {
            for (int j = 2; j < 30; j ++)
            {
                tt[i][j] = 0;
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << nume << ", ai facut " << sc << " puncte.\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\nIntrodu 1 daca vrei sa continui jocul curent sau 0 daca vrei sa joci un alt joc : ";
        Citire_suplimentar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cin >> jocnou;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        if (!jocnou)
        {
            cout << "\nIntrodu 1 daca vrei sa apari in tabela cu scoruri, sau 0 in caz contrar : ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            Citire_suplimentar();
            cin >> ata;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            if (ata)
            {
                Modificare_istoric(2, nume);
                Afisare_ist(2);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "Introdu o litera si apoi apasa pe enter pentru a merge la meniu.";
                char ptcit;
                Citire_suplimentar();
                cin >> ptcit;
            }
            jucat = 0;
            sc = 0;
            Meniu();
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Ati ales Tetris.\n";
        cout << "Introduceti numele dumneavoastra: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        Citire_suplimentar();
        cin.get(nume, 100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        jucat = 1;
        system ("CLS");
        cout << "Jocul se va juca folosind literele ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "s";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << " (sau ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "S";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << ") si ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "d";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "(sau ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "D";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "), pentru a face forma sa se deplaseze in stanga, respectiv dreapta.\n";
        cout << nume << ", primesti 4 puncte pentru asezarea unei forme si 60 pentru completarea unui rand.";
    }
    sc = 0;
    cout << "\n\nApasa pe o litera, apoi pe enter pentru a incepe jocul.";
    int w;
    Citire_suplimentar();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cin >> w;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    sc = 0;
    system ("CLS");
    Alegere_forma_tt();
    stop_joc = 0;
    while (!stop_joc)
    {

        system ("CLS");
        Afisare_matrice_tt();
        if (_kbhit())
            Schimbare_directie_tt(_getch());
        if (!Testare_asezare_forma__tt())
        {
            if (_kbhit())
                Schimbare_directie_tt(_getch());
            Coborare_forma_tt();
            if (_kbhit())
                Schimbare_directie_tt(_getch());
        }
        else
        {
            Asezare_forma_tt();
            Rand_complet_tt();
            if (Testare_joc_terminat_tt())
            {
                stop_joc = 1;
            }
            else
            {
                Alegere_forma_tt();
            }
        }
    }
    system ("CLS");
    Tetris();
}

struct Intrebare
{
    bool fol = 0;
    char intr[1000], rasp[5][50], sursa[100];
    int rco;
} qz[100];

void Citire_suplimentar()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

bool Testare_qz()
{
    for (int i = 0; i < nr_intr; i ++)
    {
        if (qz[i].fol)
            return 0;
    }
    return 1;
}

void Resetare_intrebari_qz()
{
    for (int i = 0; i < nr_intr; i ++)
    {
        qz[i].fol = 0;
    }
}

void Quiz()
{
    if (jucat)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\nAi " << sc << " puncte.\n";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\nIntrodu 1 daca vrei sa continui jocul curent sau 0 daca vrei sa joci un alt joc : ";
        Citire_suplimentar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cin >> jocnou;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        if (!jocnou)
        {
            cout << "\nIntrodu 1 daca vrei sa apari in tabela cu scoruri, sau 0 in caz contrar : ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            Citire_suplimentar();
            cin >> ata;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            if (ata)
            {
                Modificare_istoric(3, nume);
                Afisare_ist(3);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << "\nIntrodu o litera si apoi apasa pe enter pentru a merge la meniu.";
                char ptcit;
                Citire_suplimentar();
                cin >> ptcit;
            }
            jucat = 0;
            sc = 0;
            Meniu();
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Ati ales jocul Quiz.\n";
        cout << "Introduceti numele dumneavoastra: ";
        Citire_suplimentar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cin.get(nume, 100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        sc = 0;
        jucat = 1;
        rand_co = 0;
        system ("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << nume << ", primesti 1 punct pentru fiecare raspuns corect si pierzi 2 puncte la fiecare raspuns gresit.";
        cout << "\nPunctajul minim pe care il vei putea avea este 0.";
        cout << "\n\nIntrodu o litera, apoi apasa enter pentru a incepe jocul.";
        char ptcit;
        Citire_suplimentar();
        cin >> ptcit;
    }
    system ("CLS");
    intr_rand = rand() % nr_intr;
    if (Testare_qz())
        Resetare_intrebari_qz();
    while (qz[intr_rand].fol)
    {
        intr_rand = rand() % nr_intr;
    }
    qz[intr_rand].fol = 1;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << qz[intr_rand].intr << "\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    for (int i = 1; i <= 4; i ++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << i;
        cout << ": ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << qz[intr_rand].rasp[i] << "\n\n";
    }
    cout << "\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << nume << ", introdu numarul raspunsului corect : ";
    Citire_suplimentar();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cin >> rasp_dat;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n";
    while (rasp_dat < 1 or rasp_dat > 4 or (int)(rasp_dat) != (double)(rasp_dat))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "Numarul introdus nu este valid.\nIntrodu alt numar : ";
        Citire_suplimentar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cin >> rasp_dat;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\n";
    }
    if (rasp_dat == qz[intr_rand].rco)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "Felicitari ! Ai raspuns corect !\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        sc ++;
        rand_co ++;
        if (rand_co == 5)
        {
            sc += 5;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << "Ai raspuns corect la 5 intrebari consecutive. Ai primit 5 puncte bonus.\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        if (rand_co % 10 == 0 and rand_co > 9)
        {
            sc += 10;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << "Ai raspuns corect la " << rand_co << " intrebari consecutive. Ai primit 10 puncte bonus.\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "Sursa informatiei : " << qz[intr_rand].sursa << ".\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        Beep(500, 500);
        Beep(700, 850);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Ai raspuns gresit !\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "Raspunsul corect este ,,";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << qz[intr_rand].rasp[qz[intr_rand].rco];
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "'' (" << qz[intr_rand].rco << ").\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "Sursa informatiei : " << qz[intr_rand].sursa << ".\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        sc -= 2;
        if (sc < 0)
            sc = 0;
        rand_co = 0;
        Beep(500,500);
        Beep(300,850);
    }
    Quiz();
}

void Afisare_omulet_sp()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n\n    ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
    cout << " ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n";
    if (nrvieti > 2)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 200);
    }
    cout << "    ";
    if (nrvieti > 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 200);
    }
    cout << " ";
    if (nrvieti > 3)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 200);
    }
    cout << "    ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n";
    cout << "   ";
    if (nrvieti > 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 200);
    }
    cout << "   ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "\n";
    for (int i = 3; i > 0; i --)
    {
        for (int j = 1; j <= i; j ++)
            cout << " ";
        if (nrvieti > 4)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 200);
        }
        cout << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        if (i == 3)
        {
            if (nrvieti > 1)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 200);
            }
        }
        cout << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        for (int j = 3; j > i; j --)
            cout << "  ";
        if (nrvieti == 6)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 230);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 200);
        }
        cout << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

bool Cuv_corect_sp()
{
    for (int i = 0; i < strlen(cuv); i ++)
        if (cuv[i] < 'a' or cuv[i] > 'z')
            return 0;
    return 1;
}

bool Testare_sp()
{
    for (int i = 0; i <= nrcuv; i ++)
        if (lista_cuv[i] != NULL)
            return 0;
    return 1;
}

void Sp2()
{
    if (scj1 or scj2)
    {
        cout << "Scorul : \n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "    " << nume1 << " : ";
        for (int i = 1; i <= 20 - strlen(nume1); i ++)
            cout << " ";
        cout << scj1 << "\n";
        cout << "    " << nume2 << " : ";
        for (int i = 1; i <= 20 - strlen(nume2); i ++)
            cout << " ";
        cout << scj2 << "\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\nIntroduceti 1 daca vreti sa continuati jocul curent sau 0 daca vreti sa jucati un alt joc : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        Citire_suplimentar();
        cin >> jocnou;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        while (jocnou < 0 or jocnou > 1 or (int)(jocnou) != (double)(jocnou))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "Nu ati introdus un numar valid. Va rugam sa introduceti alt numar : ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            Citire_suplimentar();
            cin >> jocnou;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        system ("CLS");
        if (!jocnou)
        {
            scj1 = 0;
            scj2 = 0;
            Meniu();
        }
    }
    else
    {
        randjocsp = 0;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Introduceti numele pentru primul jucator : ";
        Citire_suplimentar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cin.get(nume1, 100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "\n";
        cout << "Introduceti numele pentru al doilea jucator : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        Citire_suplimentar();
        cin.get(nume2, 100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        scj1 = 0;
        scj2 = 0;
        system ("CLS");
    }
    for (int i = 0; i < 100; i ++)
        fr[i] = 0;
    nrvieti = 6;
    nrlit = 0;
    for (int i = 0; i <= n_lit_fol; i ++)
        lit_folosite[i] = NULL;
    n_lit_fol = 0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    if (!randjocsp)
        cout << nume1;
    else
        cout << nume2;
    cout << ", trebuie sa introduci un cuvant.\nCuvantul pe care il vei introduce trebuie sa contina doar litere mici ale alfabetului englez, iar acestea trebuie sa fie minim 5.";
    cout << "\n\nIntrodu cuvantul : ";
    Citire_suplimentar();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cin.get(cuv, 100);
    while (strlen(cuv) < 5 or !Cuv_corect_sp())
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        if (!randjocsp)
            cout << nume1;
        else
            cout << nume2;
        cout << ", cuvantul scris nu este valid. Introdu un alt cuvant : ";
        Citire_suplimentar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cin.get(cuv, 100);
    }
    system ("CLS");
    while (nrvieti and nrlit != strlen(cuv))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        if (!randjocsp)
            cout << nume2;
        else
            cout << nume1;
        cout << ", trebuie sa ghicesti cuvantul : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
        for (int i = 0; i < strlen(cuv); i ++)
        {
            if (fr[i])
                cout << cuv[i] << " ";
            else
                cout << "_ ";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\nAi ";
        if (nrvieti == 6 or nrvieti == 5)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        }
        else
        {
            if (nrvieti == 4)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            }
            else
            {
                if (nrvieti == 3)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                }
                else
                {
                    if (nrvieti == 2)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    }
                    else
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    }
                }
            }
        }
        cout << nrvieti;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << " vieti ramase.";
        if (n_lit_fol)
        {
            cout << "\nLiterele pe care le-ai introdus pana acum sunt : ";
            for (int i = 0; i < n_lit_fol; i ++)
            {
                if (strchr(cuv, lit_folosite[i]))
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    cout << lit_folosite[i];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << lit_folosite[i];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                if (i != n_lit_fol - 1)
                    cout << ", ";
            }
        }
        Afisare_omulet_sp();
        cout << "\nIntrodu o litera : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        Citire_suplimentar();
        cin >> litsp;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        while (strchr(lit_folosite, litsp) != NULL or strchr(lit_folosite, litsp + 'a' - 'A') != NULL or strchr(lit_folosite, litsp + 'A' - 'a') != NULL or !((litsp >= 'A' and litsp <= 'Z') or (litsp >= 'a' and litsp <= 'z')))
        {
            cout << "\n";
            if (!randjocsp)
                cout << nume2;
            else
                cout << nume1;
            if (!((litsp >= 'A' and litsp <= 'Z') or (litsp >= 'a' and litsp <= 'z')))
                cout << ", nu ai introdus o litera. Introdu o litera : ";
            else
                cout << ", ai mai introdus litera " << litsp << ". Introdu alta litera : ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            Citire_suplimentar();
            cin >> litsp;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        lit_folosite[n_lit_fol ++] = litsp;
        int e = 0;
        for (int i = 0; i < strlen(cuv); i ++)
        {
            if (cuv[i] == litsp or cuv[i] - ('a' - 'A') == litsp or cuv[i] + ('a' - 'A') == litsp)
            {
                nrlit ++;
                fr[i] ++;
                e = 1;
            }
        }
        system ("CLS");
        if (!e)
        {
            cout << "Litera ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << litsp;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << " nu apare in cuvant.\n";
            nrvieti --;
        }
    }
    if (!nrvieti)
    {
        if (!randjocsp)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << nume2 << ", ai pierdut!";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            scj1 ++;
            cout << "\nCuvantul scris de " << nume1 << " este ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << cuv;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << ".";
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << nume1 << ", ai pierdut!";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            scj2 ++;
            cout << "\nCuvantul scris de " << nume2 << " este ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            cout << cuv;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << ".";
        }
        Beep(500,500);
        Beep(300,850);
    }
    else
    {
        if (!randjocsp)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << nume2 << ", ai castigat!";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            scj2 ++;
            cout << "\nCuvantul scris de " << nume1 << " este ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << cuv;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << ".";
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << nume1 << ", ai castigat!";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            scj1 ++;
            cout << "\nCuvantul scris de " << nume2 << " este ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << cuv;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << ".";
        }
        Beep(500, 500);
        Beep(700, 850);
    }
    cout << "\n";
    randjocsp = !randjocsp;
    Sp2();
}

void Sp1()
{
    if (scp)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "Ai ghicit " << sc << " din " << scp << " cuvinte.\n\n";
        cout << "Introdu 1 daca vrei sa continui jocul curent sau 0 daca vrei sa joci un alt joc : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        Citire_suplimentar();
        cin >> jocnou;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        while (jocnou < 0 or jocnou > 1 or (int)(jocnou) != (double)(jocnou))
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << "Nu ai introdus un numar valid. Te rugam sa introduci alt numar : ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            Citire_suplimentar();
            cin >> jocnou;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        system ("CLS");
        if (!jocnou)
        {
            scp = 0;
            sc = 0;
            Meniu();
        }
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Introduceti numele dumneavoastra: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        Citire_suplimentar();
        cin.get(nume, 100);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        sc = 0;
        system ("CLS");
    }
    for (int i = 0; i < 100; i ++)
        fr[i] = 0;
    nrvieti = 6;
    nrlit = 0;
    for (int i = 0; i <= n_lit_fol; i ++)
        lit_folosite[i] = NULL;
    n_lit_fol = 0;
    cuv_rand = rand() % nrcuv;
    if (Testare_sp())
    {
        system ("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Nu mai sunt cuvinte. Te rugam sa alegei alt joc.";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        sc = 0;
        scp = 0;
        Meniu();
    }
    while (lista_cuv[cuv_rand] == NULL)
        cuv_rand = rand() % nrcuv;
    strcpy(cuv, lista_cuv[cuv_rand]);
    lista_cuv[cuv_rand][0] = NULL;
    while (nrvieti and nrlit != strlen(cuv))
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << nume << ", trebuie sa ghicesti cuvantul : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
        for (int i = 0; i < strlen(cuv); i ++)
        {
            if (fr[i])
            {
                cout << cuv[i];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
                cout << " ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
            }

            else
            {
                cout << "_";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << " ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\nAi ";
        if (nrvieti == 6 or nrvieti == 5)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        }
        else
        {
            if (nrvieti == 4)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            }
            else
            {
                if (nrvieti == 3)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                }
                else
                {
                    if (nrvieti == 2)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    }
                    else
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    }
                }
            }
        }
        cout << nrvieti;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << " vieti ramase.";
        if (n_lit_fol)
        {
            cout << "\nLiterele pe care le-ai introdus pana acum sunt : ";
            for (int i = 0; i < n_lit_fol; i ++)
            {
                if (strchr(cuv, lit_folosite[i]))
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    cout << lit_folosite[i];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    cout << lit_folosite[i];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                }
                if (i != n_lit_fol - 1)
                    cout << ", ";
            }
        }
        Afisare_omulet_sp();
        cout << "\nIntrodu o litera : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        Citire_suplimentar();
        cin >> litsp;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        while (strchr(lit_folosite, litsp) != NULL or strchr(lit_folosite, litsp + 'a' - 'A') != NULL or strchr(lit_folosite, litsp + 'A' - 'a') != NULL or !((litsp >= 'A' and litsp <= 'Z') or (litsp >= 'a' and litsp <= 'z')))
        {
            cout << "\n";
            if (!((litsp >= 'A' and litsp <= 'Z') or (litsp >= 'a' and litsp <= 'z')))
                cout << nume << ", nu ai introdus o litera. Introdu o litera : ";
            else
                cout << nume << ", ai mai introdus litera " << litsp << ". Introdu alta litera : ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            Citire_suplimentar();
            cin >> litsp;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        }
        lit_folosite[n_lit_fol ++] = litsp;
        int e = 0;
        for (int i = 0; i < strlen(cuv); i ++)
        {
            if (cuv[i] == litsp or cuv[i] - ('a' - 'A') == litsp or cuv[i] + ('a' - 'A') == litsp)
            {
                nrlit ++;
                fr[i] ++;
                e = 1;
            }
        }
        system ("CLS");
        if (!e)
        {
            cout << "Litera ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << litsp;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            cout << " nu apare in cuvant.\n";
            nrvieti --;
        }
    }
    if (!nrvieti)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << nume << ", ai pierdut!";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "\nCuvantul pe care trebuia sa-l ghicesti este ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << cuv;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << ".";
        Beep(500,500);
        Beep(300,850);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << nume << ", ai castigat!";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        sc ++;
        cout << "\nCuvantul pe care trebuia sa-l ghicesti este ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << cuv;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << ".";
        Beep(500, 500);
        Beep(700, 850);
    }
    cout << "\n";
    scp ++;
    Sp1();
}

void Sp()
{
    cout << "Ati ales jocul spanzuratoarea.\n";
    cout << "Tastati 1 daca jucati singur sau 2 daca jucati cu inca o persoana : ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    Citire_suplimentar();
    cin >> nrj;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    while (nrj < 1 or nrj > 2 or (int)(nrj) != (double)(nrj))
    {
        cout << "\nNumarul introdus nu este valid. Introduceti alt numar : ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        Citire_suplimentar();
        cin >> nrj;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    }
    system ("CLS");
    if (nrj == 1)
    {
        Sp1();
    }
    else
    {
        Sp2();
    }
}

void Meniu()
{
    system ("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "Hello world!\n";
    cout << "Avem urmatoarele jocuri : \n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "    1 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "- ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Spanzuratoarea (1p/2p)\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "    2 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "- ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Tetris\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "    3 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "- ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Quiz\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\nIntroduceti numarul jocului pe care doriti sa il jucati : ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cin >> nrjoc;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    while (nrjoc > 3 or nrjoc < 1 or (double)(nrjoc) != (int)(nrjoc))
    {

        cout << "Nu ati introdus un numar valid. Va rugam sa introduceti alt numar : ";
        Citire_suplimentar();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cin >> nrjoc;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    }
    system ("CLS");
    if (nrjoc == 1)
    {
        Sp();
    }
    if (nrjoc == 2)
    {
        Tetris();
    }
    if (nrjoc == 3)
    {
        Quiz();
    }
}

void Inceput()
{
    /// Sp
    int i;
    for (i = 0; spin >> lista_cuv[i]; i ++)
    {
        spin.get();
    }
    nrcuv = i;

    /// Quiz
    i = 0;
    while (qin.get(qz[i].intr, 1000))
    {
        qin.get();
        qin.get();
        for (int j = 1; j <= 4; j ++)
        {
            qin.get(qz[i].rasp[j], 50);
            qin.get();
            qin.get();
        }
        qin >> qz[i].rco;
        qin.get();
        qin.get();
        qin.get(qz[i].sursa, 100);
        qin.get();
        qin.get();
        qin.get();
        qin.get();
        i ++;
    }
    nr_intr = i;
    for (i = 0; i < nr_intr; i ++)
    {
        int r = qz[i].rco % 10 + qz[i].rco / 100;
        r %= 5;
        qz[i].rco = r;
    }

    /// Tetris
    for (int i = 1; i <= 30; i ++)
    {
        tt[i][1] = 1;
        tt[i][30] = 1;
        tt[1][i] = 1;
        tt[30][i] = 1;
    }
    nr_forme = 0;
    while (tin >> forma[nr_forme].coord[1].ip)
    {
        tin >> forma[nr_forme].coord[1].jp;
        forma[nr_forme].coord[1].ip ++;
        forma[nr_forme].coord[1].jp += 14;
        for (int j = 2; j < 5; j ++)
        {
            tin >> forma[nr_forme].coord[j].ip;
            tin >> forma[nr_forme].coord[j].jp;
            forma[nr_forme].coord[j].ip ++;
            forma[nr_forme].coord[j].jp += 14;
        }
        nr_forme ++;
    }

    ///Istoric
    fstream scin("istoric.txt", ios::in);
    i = 1;
    while (scin >> ist[i].joc)
    {
        scin >> ist[i].scor;
        scin.get();
        scin.get(ist[i].num, 100);
        i ++;
    }
    nist = i - 1;
    sort(ist + 1, ist + 1 + nist, Sortare_ist);
    scin.close();
}

int main()
{
    Inceput();
    Meniu();
    return 0;
}
