#pragma once
#include "Repo.h"
#include "Service.h"
#include <random>
#include <fstream>

class Lista_de_activitati
{
private:
	Repo& repo;
public:
	Lista_de_activitati(Repo& rep) : repo{ rep } {}
	void adauga_lista(int id, Service* service);
	void goleste_lista();
	void genereaza_lista(int nr, Service* service);
	~Lista_de_activitati();
	void exporta_lista(string nume_fisier);
	Repo* get_repo();
};


class ListaEx
{
public:
	string mesaj;
	ListaEx(string er);
};


class MaiPutine
{
public:
	int nr;
	MaiPutine(int nr);
};
