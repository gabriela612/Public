#pragma once
#include "Repo.h"
#include "Lista.c"

typedef struct
{
	Oferte* repo;
	Li* li;
}OferteS;

void CreareListaGoalaServ(OferteS* ofertes);
/// <summary>
/// In acesta functie creeam o lista goala la adresa ofertes
/// </summary>
/// <param :
/// - ofertes = adresa la care creeam lista goala
/// < prec :
/// - ofertes = adresa unei variabile de tip OferteS

void DistrugereListaServ(OferteS* service);
/// <summary>
/// In acesta functie dam free la elementele variabilei service alocate dinamic
/// </summary>
/// <param :
/// - service = adresa unei variabile de tip OferteS
/// < prec :
/// - lista elementelor ofertei sa fie alocate dinamic

Oferte* GetRepo(OferteS* service);
/// <summary>
/// In acesta functie returnam lista de oferte a variabilei service
/// </summary>
/// <param :
/// - service : variabila de tip OferteS din care luam lista de oferte
/// < prec : service sa fie o referinta spre o variabila de tip OferteS valida
/// retrun : lista de oferte a variabilei service

int TestareResdimensionareServ(OferteS* ofertes);
/// <summary>
/// In acesta functie testam daca trebuie sa facem redimensionare
/// </summary>
/// <param :
/// - service : variabila de tip OferteS pentru care testam daca trebuie sa facem redimensionare

void RedimensionareServ(OferteS* service);
/// <summary>
/// In acesta functie facem redimensionarea
/// </summary>
/// <param :
/// - service : variabila de tip OferteS pentru care facem redimensionarea

int AdaugareServ(OferteS* service, char* tip, int pret, char* data, char *dest);
/// <summary>
/// In acesta functie adaugam oferta formata din tip, pret, data si dest la lista de oferte
/// </summary>
/// < param :
/// - service : variabila de tip OferteS in care adaugam oferta
/// - tip = tipul pe care il va avea oferta adaugata
/// - pret = pretul pe care il va avea oferta adaugata
/// - data = data pe care o va avea oferta adaugata
/// - dest = destinatia pe care il va avea oferta adaugata
/// < prec :
/// - tip = int
/// - pret = int
/// - data = adresa de la un sir de caractere
/// - dest = adresa de la un sir de caractere
/// post : oferta formata din tip, pret, data si dest este in lista de oferte
/// return :
/// - 1 daca tipul nu este ,,munte", ,,mare" sau ,,city_break"
/// - 2 daca pretul este negativ
/// - 3 daca data nu este valida
/// - 4 daca oferta pe care dorim sa o adaugam exista deja
/// - 0 daca s-a adaugat cu succes

int StergereServ(OferteS* service, char* tip, int pret, char* data, char * dest);
/// <summary>
/// In acesta functie sterge oferta formata din tip, pret, data si dest din lista de oferte
/// </summary>
/// < param :
/// - service : variabila de tip OferteS din care stergem oferta
/// - tip = tipul pe care il va avea oferta pe care o vom sterge
/// - pret = pretul pe care il va avea oferta pe care o vom sterge
/// - data = data pe care o va avea oferta pe care o vom sterge
/// - dest = destinatia pe care il va avea oferta pe care o vom sterge
/// < prec :
/// - tip = int
/// - pret = int
/// - data = adresa de la un sir de caractere
/// - dest = adresa de la un sir de caractere
/// post : oferta formata din tip, pret, data si dest nu mai este in lista de oferte
/// return :
/// - 1 daca tipul nu este ,,munte", ,,mare" sau ,,city_break"
/// - 2 daca pretul este negativ
/// - 3 daca data nu este valida
/// - 4 daca oferta pe care dorim sa o stergem nu exista
/// - 0 daca s-a sters cu succes

int ActualizareServ(OferteS* service, char* tipv, int pretv, char* datav, char *destv, char* tipn, int pretn, char* datan, char * destn);
/// <summary>
/// In acesta functie modifiam oferta formata din tipv, pretv, datav si destv in oferta formata cu tipn, pretn, datan si destn
/// </summary>
/// < post : daca nu sunt erori, oferta formata din tipv, pretv, datav si destv va fi modificata in oferta formata cu tipn, pretn, datan si destn
/// < param :
/// - service : variabila de tip OferteS din care stergem oferta
/// - tipv = tipul vechi pe care il are oferta pe care o vom modifica
/// - pretv = pretul vechi pe care il are oferta pe care o vom modifica
/// - datav = data veche pe care o are oferta pe care o vom modifica
/// - destv = destinatia veche pe care o are oferta pe care o vom modifica
/// - tipn = tipul nou pe care il va avea oferta pe care o vom modifica
/// - pretn = pretul nou pe care il va avea oferta pe care o vom modifica
/// - datan = data nou pe care o va avea oferta pe care o vom modifica
/// - destn = destinatia nou pe care o va avea oferta pe care o vom modifica
/// < prec :
/// - tipv = int si este un tip valid
/// - pretv = int si este un tip valid
/// - datav = adresa de la un sir de caractere si este o data valida
/// - destv = adresa de la un sir de caractere
/// - tipn = int
/// - pretn = int
/// - datan = adresa de la un sir de caractere
/// - destn = adresa de la un sir de caractere
/// return :
/// - 1 daca tipv sau tipn nu este ,,munte", ,,mare" sau ,,city_break"
/// - 2 daca pretv sau pretn este negativ
/// - 3 daca datan sau datav nu este valida
/// - 4 daca oferta pe care dorim sa o modificam nu exista
/// - 5 daca oferta dupa modificare exista deja
/// - 0 daca s-a sters cu succes

void SortarePretDestinatieCrescator(OferteS* ofertes);
/// <summary>
/// In acesta functie sortam crescator elementele din ofertes dupa pret di destinatie
/// </summary>
/// prec / param :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// post : ofertele din lista de oferte ofertes sunt sortate crescator dupa pret si destinatie

void SortarePretDestinatieDescrescator(OferteS* ofertes);
/// <summary>
/// In acesta functie sortam descrescator elementele din ofertes dupa pret di destinatie
/// </summary>
/// prec / param :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// post : ofertele din lista de oferte ofertes sunt sortate descrescator dupa pret si destinatie

void FiltrareDest(OferteS* ofertes, char* dest, OferteS * offil);
/// <summary>
/// In acesta functie creeam (alocam) o variabila de tip OferteS si ii atribuim adresa la offil. In acesta variabila punem pointerii
/// de la ofertele din ofertes care au ca destinatie dest
/// </summary>
/// param :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// - offil = variabila de tip OferteS nou construita
/// - dest = destinatia dupa care filtram
/// prec :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// - offil = un pointer de tip OferteS
/// - dest = un pointer de tip char
/// post : in offil avem pointerii de la ofertele din ofertes care au ca destinatie dest

void FiltrarePret(OferteS* ofertes, int pret, OferteS* offil);
/// <summary>
/// In acesta functie creeam (alocam) o variabila de tip OferteS si ii atribuim adresa la offil. In acesta variabila punem pointerii
/// de la ofertele din ofertes care au ca pret parametru pret
/// </summary>
/// param :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// - offil = variabila de tip OferteS nou construita
/// - pret = pretul dupa care filtram
/// prec :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// - offil = un pointer de tip OferteS
/// - pret = un numar natural
/// post : in offil avem pointerii de la ofertele din ofertes care au ca pretul pret

void FiltrareTip(OferteS* ofertes, char* tip, OferteS* offil);
/// <summary>
/// In acesta functie creeam (alocam) o variabila de tip OferteS si ii atribuim adresa la offil. In acesta variabila punem pointerii
/// de la ofertele din ofertes care au ca tip parametrul tip
/// </summary>
/// param :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// - offil = variabila de tip OferteS nou construita
/// - tip = tipul dupa care filtram
/// prec :
/// - ofertes = un pointer spre o lista valida de tip OferteS cu oferte
/// - offil = un pointer de tip OferteS
/// - tip = un pointer de tip char
/// post : in offil avem pointerii de la ofertele din ofertes care au ca tip parametrul tip

void FiltrareDestTip(OferteS* ofertes, char* dest, OferteS* offil, char* tip);

int Undo(OferteS* ser);

void TesteUndo();

void TesteS();
///- in acesta functie avem testele de la service

