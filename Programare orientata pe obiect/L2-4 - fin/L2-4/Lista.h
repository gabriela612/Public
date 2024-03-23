#pragma once
#include <stdlib.h>

typedef struct
{
	int lg, cap;
	void** elem;
}Li;

Li * CreareListaGen(int cap);
/// <summary>
/// In acesta functie se creeaza o lista cu capacitatea cap
/// </summary>
/// param : cap = capacitatea pe care o va avea lista (numarul inital de elemente care se pot pune in ea)
/// prec : cap este un numar natural nenul
/// post : la adresa returnata vom avea o lista de capacitate cap
/// return : lista nou creata

void AdaugaListaGen(Li* li, void* el);
/// <summary>
/// In acesta functie se adauga in lista li un element care are adresa el
/// </summary>
/// <param :
/// - lista la care adaugam elementul
/// - el - elementul pe care il adaugam
/// prec :
/// - li = adresa unei liste
/// - el = un pointer
/// post : el va fi adaugat in li

int TestareRedimListaGen(Li* li);
/// <summary>
/// In acesata functie testam daca este nevoie sa redimensionam
/// </summary>
/// <param : li = lista pentru care testam nevoia de redimensionare
/// prec : li este o lista valida
/// return :
/// -> 1, daca este nevoie de redimensionare
/// -> 0, daca nu este nevoie de redimensionare

void RedimListaGen(Li* li);
/// <summary>
/// In aceasta functie redimensionam lista li
/// </summary>
/// <param : li = lista pe care o redimensionam
/// prec : lista li este valida
/// post : lista li va avea capacitate dubla

void DistrugeListaGen(Li* li);
/// <summary>
/// In acesta functie dealocam lista li
/// </summary>
/// <param li : lista pe care o dealocam

void* GetStergeUltimulElemGen(Li* li);
/// In acesta functie stergem ultimul element din lista li si il returnam
/// prec : lista li este valida
/// post : se sterge ultimul element din lista li
/// return : pointer spre elementul sters din lista li


void TesteL();


