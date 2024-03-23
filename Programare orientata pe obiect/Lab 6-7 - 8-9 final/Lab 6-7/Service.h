
#pragma once
#include "Repo.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include "Undo.h"

using namespace std;



class Service
{
private:
	vector<unique_ptr<Undo>> lista_undo;
	Repo& repo;
	int id;

public:
	Service(Repo& rep) : repo{ rep }, id{ 0 } {}
	int cautare_id_service(int id);
	void cautare_service(int id, Activitate* act);
	void adaugare_service(string* titlu, string* descriere, string* tip, int durata);
	void stergere_service(int id);
	void modificare_service(int id, string* titlu, string* descriere, string* tip, int durata);
	void filtrare_descriere(vector<Activitate>* v, string* descriere);
	void filtrare_tip(vector<Activitate>* v, string* tip);
	void sortare_titlu(vector<Activitate>* v);
	void sortare_tip_durata(vector<Activitate>* v);
	void golire_lista();
	void distruge_service();
	void get_all_service(vector<Activitate>* v);
	void teste_service();
	Repo* pointer_repo();
	void undo_service();
};

class ServiceEx
{
public:
	string mesaj;
	ServiceEx(string er);
};