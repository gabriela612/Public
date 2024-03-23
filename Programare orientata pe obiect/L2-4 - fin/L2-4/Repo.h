#pragma once
#include "Domain.h"
#include <stdlib.h>
#include <assert.h>


typedef struct
{
	int lg, cap;
	Oferta** elem;
}Oferte;

void CreareListaGoala(Oferte* oferte, int cap);
/// <summary>
/// In acesta functie creeam o lista goala la adresa oferte care are capacitatea cap
/// </summary>
/// <param :
/// - oferte = adresa la care creeam lista goala
/// - cap = capacitatea initiala pe care o va avea lista de oferte
/// < prec :
/// - oferte = adresa unei variabile de tip Oferte
/// - cap = un numar pozitiv

void DistrugereLista(Oferte* oferte);
/// <summary>
/// In acesta functie dam free la elementele ofertei alocate dinamic
/// </summary>
/// <param :
/// - oferte = adresa unei variabile de tip oferte 
/// < prec :
/// - lista elementelor ofertei sa fie alocate dinamic

void Adaugare(Oferte* oferte, Oferta* of);
/// <summary>
/// In acesta functie adaugam oferta of la lista de oferte
/// </summary>
/// prec :
/// - oferte = o variabila de tip Oferte creeata si valida, in care mai incap elemente
/// - of = o oferta valida
/// <param :
/// - *oferte = lista de oferte la care adaugam oferta of
/// - *of = oferta pe care o adaugam

void Stergere(Oferte* oferte, int poz);
/// <summary>
/// In acesta functie se sterge elementul de pe pozitia poz din lista de oferte
/// </summary>
/// <prec :
/// - oferte este o lista de oferte valida
/// - poz este un numar natural mai mic sau egal cu lungimea listei
/// <param :
/// - oferta = adresa listei de oferte din care stergem oferta de pe pozitia poz
/// - poz = pozitia elementului pe care il stergem din lista

void GetOfertaPoz(Oferte* oferte, Oferta* of, int poz);
/// <summary>
/// In acesta functie punem in of adresa de pe pozitia poz din lista de oferte
/// </summary>
/// <param :
/// - oferte = lista de oferte
/// - of = variabila in care memoram adresa de la pozitia poz din lista de oferte
/// - poz = pozitia elementului in lista
/// < prec :
/// - oferte = lista de oferte valida
/// - of = adresa unei variabile de tip adrese
/// - poz = un numar intreg
/// - daca poz nu este natural sau este mai mare decat lungimea, of va fi NULL

int CautaOferta(Oferte oferte, Oferta of);
/// <summary>
/// In acesta functie cautam oferta of in lista de oferte
/// </summary>
/// prec :
/// - of este o oferta valida
/// - oferte este o lista de oferte
/// param :
/// - oferte = lista de oferte in care cautam of
/// - of = oferta pe care o cautam
/// return : pozitia pe care am gasit oferta of in lista de oferte (int) sau -1 daca nu se gaseste

Oferta* GetOfertaPoz2(Oferte* oferte, int poz);
/// <summary>
/// In acesta functie returnam adresa de pe pozitia poz din lista de oferte
/// </summary>
/// <param :
/// - oferte = lista de oferte
/// - poz = pozitia elementului in lista
/// < prec :
/// - oferte = lista de oferte valida
/// - poz = un numar intreg
/// return :
/// - daca poz nu este natural sau este mai mare decat lungimea, se va returna NULL
/// - un pointer spre oferta gasita

void DistrugereOferte(Oferte* oferte);
/// <summary>
/// In acesta functie se elibereaza toate variabilele de tip oferta din lista de oferte si lista de oferte, alocate dinamic
/// </summary>
/// <param :
/// - oferte = lista de oferte care urmeaza sa fie distrusa
/// <prec :
/// - ofertele din lista si lista sa fie alocate dinamic

void CopiereLista(Oferte* sursa, Oferte* dest);
/// <summary>
/// In acesta functie copiem adresele de la ofertele din lista de oferte sursa in lista de oferte destinatie
/// </summary>
/// param:
/// - sursa = adresa de la lista de oferte de la care copiem
/// - dest = adresa de la lista de oferte in care copiem
/// prec :
/// - sursa si dest sunt pointeri spre variabile de tip Oferte valide si alocate

void Interschimba(int poz1, int poz2, Oferte * oferte);
/// <summary>
/// In acesta functie interschimbam pointerii din lista de oferte de pe pozitiile poz1 si poz2
/// </summary>
/// param :
/// - poz1 = prima pozitie (int)
/// - poz2 = a doua pozitie (int)
/// - oferte = adresa unei liste de oferte
/// prec :
/// - oferte = pointer spre o lista de adrese valide
/// - poz1 = un numar natural mai mic decat lungimea listei de oferte
/// - poz2 = un numar natural mai mic decat lungimea listei de oferte


Oferte * DeepCopyRepo(Oferte* repodest);
/// In acesta functie alocam dinamic repodest si copiem copiile elementelor din reposursa la adresa din repodest
///param :
/// - reposursa = lista de oferte pe care o copiem
/// - repodest = adresa copiei listei de oferte reposursa
/// prec :
/// - reposursa = pointer spre o variabila valida de tip Oferte
/// - repodest = un pointer
/// post :
/// - repodest contine o adresa spre o variabila de tip Oferte de pe heap care are elementele copiate din reposursa
/// 


void TesteR();
///- in acesta functie avem testele de la repo



