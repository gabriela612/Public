#pragma once
#include "Service.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "Lista.h"

#include <windows.h>
#include <stdlib.h>


using namespace std;


class UI
{
private:
	Service& service;
public:
	UI(Service& ser) : service{ ser } {}
	void inceput();
	void adaugare_ui();
	void stergere_ui();
	void modificare_ui();
	void filtrare_ui();
	void sortare_ui();
	void cautare_ui();
	void golire_ui();
	void creare_lista();
	void afisare_meniu();
	int citire_cerinta();
	void apelare_cerinta(int cer);
	void afisare_activitati(vector<Activitate>* v);
	void undo_ui();
};
