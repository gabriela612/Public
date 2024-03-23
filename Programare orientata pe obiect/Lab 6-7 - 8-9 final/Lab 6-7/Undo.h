#pragma once
#include "Repo.h"
#include "Service.h"
#include <string.h>
#include "Domain.h"
#include <iostream>
#include "Service.h"

using namespace std;

class Undo
{
public:
	Repo* repo;
	virtual void doUndo()=0;
	virtual ~Undo() = default;
};

class UndoAd : public Undo
{
private:
	int id;
	Repo* repo;
public:
	UndoAd(int _id, Repo* _repo) : id{ _id }, repo{ _repo } {}
	void doUndo() override
	{
		//ser->stergere_service(this->id);
		int poz = this->repo->cautare_pozitie_id_repo(id);
		if (poz == this->repo->len() - 1)
		{
			this->repo->distruge_activitate_pozitie(poz);
			this->repo->arunca_ultima_activitate();
			return;
		}
		this->repo->distruge_activitate_pozitie(poz);
		Activitate act_ul;
		this->repo->get_activitate_poz_repo(&act_ul, this->repo->len() - 1);
		this->repo->distruge_activitate_pozitie(this->repo->len() - 1);
		this->repo->arunca_ultima_activitate();
		this->repo->pune_activitate_pe_pozitia(&act_ul, poz);
		act_ul.~Activitate();
	}
};

class UndoSt : public Undo
{
private:
	Activitate act;
	Repo* repo;
public:
	UndoSt(Activitate _act, Repo* _repo) : act{ _act }, repo{ _repo } {}
	void doUndo() override
	{
		this->repo->adaugare_repo(this->act);
	}
	~UndoSt()
	{
		act.~Activitate();
	}
};

class UndoMo : public Undo
{
private:
	int poz, durata;
	string titlu, descriere, tip;
	Repo* repo;
public:
	UndoMo(int _poz, string _titlu, string _descriere, string _tip, int _durata, Repo* _repo) : poz{_poz}, titlu{_titlu}, descriere{_descriere}, tip{_tip}, durata{_durata}, repo{_repo} {}
	void doUndo() override
	{
		this->repo->modificare_activitate_pozitie(this->poz, &this->titlu, &this->descriere, &this->tip, this->durata);
	}
	~UndoMo()
	{
		this->titlu.~basic_string();
		this->descriere.~basic_string();
		this->tip.~basic_string();
	}
};

