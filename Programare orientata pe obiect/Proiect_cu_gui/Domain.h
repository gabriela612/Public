#pragma once
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;

class Activitate
{
private:
	string titlu, descriere, tip;
	int durata, id;

public:

	Activitate();
	void str(string* text);
	void creare_activitate(string* titlu, string* descriere, string* tip, int durata, int id);
	void get_titlu(string* copie);
	void get_descriere(string* copie);
	void get_tip(string* copie);
	int get_durata() const;
	int get_id() const;
	void set_titlu(string* titlu_nou);
	void set_descriere(string* descriere_noua);
	void set_tip(string* tip_nou);
	void set_durata(int durata_noua);
	void set_id(int id_nou);
	bool egal_id(Activitate& act1, Activitate& act2) const;
	bool egal_activitati(Activitate act1, Activitate act2) const;
	void teste_domain();
	Activitate& operator=(Activitate x);
	~Activitate();
	bool are_id(Activitate act, int id);
};

bool titlu_crescator(Activitate a, Activitate b);

bool tip_durata_crescator(Activitate a, Activitate b);

bool tip_egal(Activitate a, string* tip);

bool descriere_egala(Activitate a, string* descriere);

//void separare(string tot, string a)
