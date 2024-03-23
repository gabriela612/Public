#pragma once
#include "Domain.h"
#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
#include <algorithm>
using namespace std;

class Repo
{
private:
	vector<Activitate>v;

public:
	Repo();
	void adaugare_repo(Activitate& act);
	void pune_activitate_pe_pozitia(Activitate* act, int poz);
	bool get_activitate_poz_repo(Activitate* act, int poz) const;
	int cautare_pozitie_id_repo(int id_cautat) const;
	int cautare_pozitie_activitate_repo(Activitate& act_cautata) const;
	void modificare_activitate_pozitie(int poz, string* titlu, string* descriere, string* tip, int durata);
	bool repo_vid();
	int len();
	void get_all_repo(vector<Activitate>* v) const;
	void distruge_repo();
	void distruge_activitate_pozitie(int poz);
	void arunca_ultima_activitate();
	void teste_repo();
	Activitate* get_pointer_activitate_poz(int poz);
	void s1();
	void s2();
};

