#pragma once
#include <string.h>
#include <assert.h>
#include <stdlib.h>


typedef struct
{
	int tip, pret;
	char data[20], dest[20];
}Oferta;

void CreareOferta(Oferta* of, int tip, int pret, char* data, char *dest);
/// <summary>
/// In acesta functie se creeaza o oferta la adresa parametrului *of care are tipul, pretul, data si destinatia din parametrii
/// </summary>
/// <param : 
/// - of = adresa la care se creeaza oferta
/// - tip = tipul pe care il va avea oferta creeata
/// - pret = pretul pe care il va avea oferta creeata
/// - data = data pe care o va avea oferta creeata
/// - dest = destinatia pe care il va avea oferta creeata
/// <prec :
/// - of = adresa de la o variabila de tip Oferta
/// - tip = int
/// - pret = int
/// - data = adresa de la un sir de caractere
/// - dest = adresa de la un sir de caractere
/// <post : oferta de la adresa parametrului *of care are tipul, pretul, data si destinatia din parametrii
/// 

int GetTip(Oferta of);
/// <summary>
/// Acesta functie returneaza tipul ofertei of
/// </summary>
/// <prec :
/// - of = adresa de la o variabila de tip Oferta
/// <param :
/// - of = oferta a carei tip il returnam (variabila de tip Oferta)
/// post : oferta este una valida
/// return : tipul ofertei

void GetNumeTip(Oferta of, char* tip);
/// <summary>
/// Acesta functie copiem tipul variabilei of la adresa tip
/// </summary>
/// <prec :
/// - of = adresa de la o variabila de tip Oferta
/// - tip = adresa unui sir de caractere
/// <param :
/// - of = oferta a carei tip il returnam (variabila de tip Oferta)
/// - tip = adresa la care punem numele tipului ofertei of
/// post : oferta este una valida, tip este adresa unui sir de caractere

int GetPret(Oferta of);
/// <summary>
/// Acesta functie returneaza pretul ofertei of
/// </summary>
/// < prec :
/// - of = adresa de la o variabila de tip Oferta
/// <param :
/// - of = oferta a carei pret il returnam (variabila de tip Oferta)
/// post : oferta este una valida
/// return : pretul ofertei

void GetData(Oferta of, char* data);
/// <summary>
/// Acesta functie copiem data variabilei of la adresa data
/// </summary>
/// <prec :
/// - of = adresa de la o variabila de tip Oferta
/// - data = adresa unui sir de caractere
/// <param :
/// - of = oferta a carei data o returnam (variabila de tip Oferta)
/// - data = adresa la care punem data ofertei of
/// post : oferta este una valida, data este adresa unui sir de caractere

void GetDest(Oferta of, char* dest);
/// <summary>
/// Acesta functie copiem destinatia variabilei of la adresa dest
/// </summary>
/// < prec :
/// - of = adresa de la o variabila de tip Oferta
/// - dest = adresa unui sir de caractere
/// <param :
/// - of = oferta a carei destinatie o returnam (variabila de tip Oferta)
/// - dest = adresa la care punem destinatia ofertei of
/// post : oferta este una valida, dest este adresa unui sir de caractere

void SetTip(Oferta* of, int tip);
/// <summary>
/// In acesta functie setam tipul ofertei of in tip
/// </summary>
/// <prec :
/// - tipul este unul valid (are valoarea 1, 2 sau 3)
/// <param :
/// - of = oferta la care ii setam tipul in tip
/// - tip = tipul pe care il atribuim ofertei

void SetPret(Oferta* of, int pret);
/// <summary>
/// In acesta functie setam pretul ofertei of in tip
/// </summary>
/// <prec :
/// - pretul este unul valid
/// <param :
/// - of = oferta la care ii setam pretul in pret
/// - pret = pretul pe care il atribuim ofertei

void SetData(Oferta* of, char* data);
/// <summary>
/// In acesta functie setam data ofertei of in *data
/// </summary>
/// <prec :
/// - data este una valida
/// <param :
/// - of = oferta la care ii setam data in *data
/// - data = data pe care o atribuim ofertei

void SetDest(Oferta* of, char* dest);
/// <summary>
/// In acesta functie setam destinatia ofertei of in *dest
/// </summary>
/// <prec :
/// - dest este una valida
/// <param :
/// - of = oferta la care ii setam destinatia in *dest
/// - dest = destinatia pe care o atribuim ofertei

int Egal(Oferta of1, Oferta of2);
/// <summary>
/// In acesta functie verificam daca of1 este egala cu of2 (au aceleasi date)
/// </summary>
/// <param :
/// - of1 = prima variabila de tip Oferta
/// - of2 = a doua variabila de tip Oferta
/// <return : 1 daca of1 = of2, 0 daca of1 != of2

int Validare(char* tip, int pret, char* data, char *dest);
/// <summary>
/// In acesta functie validam parametrii
/// </summary>
/// < prec / param :
/// - tip = adresa unui sir de caractere
/// - pret = int
/// - data = adresa unui sir de caractere
/// - dest = adresa unui sir de caractere
/// <return :
/// - 1 daca tipul nu este ,,munte", ,,mare" sau ,,city_break"
/// - 2 daca pretul este negativ
/// - 3 daca data nu este valida


int TransformareTip(char* tip);
/// <summary>
/// In acesta functie returnam un numar asociat tipului
/// </summary>
/// prec : tip = o adresa de la un tip valid
/// param :
/// - tip = tipul la care ii returnam numarul asociat
/// return :
/// - 1 daca tip = munte
/// - 2 daca tip = mare
/// - 3 daca tip = city_break

void TesteD();
/// In acesta functie aveam testele din domain

void TesteDeepCopyOferta();

Oferta* DeepCopyOferta(Oferta* ofsursa);
/// In acesta functie alocam dinamic si returnam o variabila de tip Oferta si copiem elemntele din ofsursa in ea
/// param :
/// - ofsursa = oferta pe care o copiem
/// prec :
/// - ofsursa = variabila valida de tip Oferta
/// post :
/// - ofdest contine o adresa spre o variabila de tip Oferta de pe heap care are aceleasi valori cu ofsursa
/// return : o variabila de tip Oferta (alocata dinamic) care contine copii ale elementelor din ofsursa


