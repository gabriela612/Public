
#include "Service.h"





int Service::cautare_id_service(int id)
{
	return this->repo.cautare_pozitie_id_repo(id);
}

void Service::cautare_service(int id, Activitate* act)
{
	int poz = this->repo.cautare_pozitie_id_repo(id);
	if (poz == -1)
	{
		throw ServiceEx("Activitatea cautata nu exista!");
	}
	this->repo.get_activitate_poz_repo(act, poz);
}

void Service::adaugare_service(string* titlu, string* descriere, string* tip, int durata)
{
	Activitate act;
	act.creare_activitate(titlu, descriere, tip, durata, this->id);

	if (this->repo.cautare_pozitie_activitate_repo(act) != -1)
	{
		act.~Activitate();
		throw ServiceEx("Activitatea exista deja!");
	}
	this->repo.adaugare_repo(act);
	this->id++;
	//UndoAd u(id - 1, &this->repo);
	//this->lista_undo.push_back(u);
	this->lista_undo.push_back(make_unique < UndoAd>(id - 1, &this->repo));
}

void Service::stergere_service(int id)
{
	int poz = this->repo.cautare_pozitie_id_repo(id);
	if (poz == -1)
	{
		throw ServiceEx("Nu exista nicio activitate cu id-ul dat!");
	}
	if (poz == this->repo.len() - 1)
	{
		//UndoSt u(this->repo.get_pointer_activitate_poz(poz), &this->repo);
		//this->lista_undo.push_back(u);
		this->lista_undo.push_back(make_unique < UndoSt>(*this->repo.get_pointer_activitate_poz(poz), &this->repo));
		this->repo.distruge_activitate_pozitie(poz);
		this->repo.arunca_ultima_activitate();
		return;
	}
	//UndoSt u(this->repo.get_pointer_activitate_poz(poz), &this->repo);
	//this->lista_undo.push_back(u);
	this->lista_undo.push_back(make_unique < UndoSt>(*this->repo.get_pointer_activitate_poz(poz), &this->repo));
	this->repo.distruge_activitate_pozitie(poz);
	Activitate act_ul;
	this->repo.get_activitate_poz_repo(&act_ul, this->repo.len() - 1);
	this->repo.distruge_activitate_pozitie(this->repo.len() - 1);
	this->repo.arunca_ultima_activitate();
	this->repo.pune_activitate_pe_pozitia(&act_ul, poz);
	act_ul.~Activitate();
}

void Service::modificare_service(int id, string* titlu, string* descriere, string* tip, int durata)
{
	Activitate act;
	act.creare_activitate(titlu, descriere, tip, durata, this->id);
	int poz = this->repo.cautare_pozitie_activitate_repo(act);
	act.~Activitate();
	if (poz != -1)
	{
		throw ServiceEx("Activitatea modificata exista deja in lista!");
	}
	poz = this->repo.cautare_pozitie_id_repo(id);


	Activitate* ac = NULL;
	ac = this->repo.get_pointer_activitate_poz(poz);
	string tu, d, tp;
	ac->get_titlu(&tu);
	ac->get_descriere(&d);
	ac->get_tip(&tp);
	//UndoMo u(poz, tu, d, tp, ac->get_durata(), &this->repo);
	//this->lista_undo.push_back(u);
	this->lista_undo.push_back(make_unique < UndoMo>(poz, tu, d, tp, ac->get_durata(), &this->repo));
	tu.~basic_string();
	d.~basic_string();
	tp.~basic_string();
	

	this->repo.modificare_activitate_pozitie(poz, titlu, descriere, tip, durata);
}

void Service::filtrare_descriere(vector<Activitate>* v, string* descriere)
{
	vector<Activitate> toate;
	string desc_cur;
	this->repo.get_all_repo(&toate);
	/*for (unsigned int i = 0; i < toate.size(); i++)
	{
		toate[i].get_descriere(&desc_cur);
		if (strstr(desc_cur.c_str(), (*descriere).c_str()))
		{
			v->push_back(toate[i]);
		}
	}*/
	/*for (auto& i : toate)
	{
		i.get_descriere(&desc_cur);
		if (strstr(desc_cur.c_str(), (*descriere).c_str()))
		{
			v->push_back(i);
		}
	}*/
	copy_if(toate.begin(), toate.end(), back_inserter(*v), [descriere](Activitate a) {return descriere_egala(a, descriere); });
	toate.~vector();
	desc_cur.~basic_string();
	if (v->size() == 0)
		throw ServiceEx("Nu s-au gasit activitati care sa contina descrierea data.");
}

void Service::filtrare_tip(vector<Activitate>* v, string* tip)
{
	vector<Activitate> toate;
	string tip_cur;
	this->repo.get_all_repo(&toate);
	/*for (unsigned int i = 0; i < toate.size(); i++)
	{
		toate[i].get_tip(&tip_cur);
		if (strstr(tip_cur.c_str(), (*tip).c_str()))
		{
			v->push_back(toate[i]);
		}
	}*/
	/*for (auto& i : toate)
	{
		i.get_tip(&tip_cur);
		if (strstr(tip_cur.c_str(), (*tip).c_str()))
		{
			v->push_back(i);
		}
	}*/
	copy_if(toate.begin(), toate.end(), back_inserter(*v), [tip](Activitate a) {return tip_egal(a, tip); });
	toate.~vector();
	tip_cur.~basic_string();
	if (v->size() == 0)
		throw ServiceEx("Nu s-au gasit activitati care sa contina tipul dat.");
}

void Service::sortare_titlu(vector<Activitate>* v)
{
	this->repo.get_all_repo(v);
	if (v->size() == 0)
		throw ServiceEx("Lista de activitati este vida.");
	sort(v->begin(), v->end(), titlu_crescator);
}

void Service::sortare_tip_durata(vector<Activitate>* v)
{
	this->repo.get_all_repo(v);
	if (v->size() == 0)
		throw ServiceEx("Lista de activitati este vida.");
	sort(v->begin(), v->end(), tip_durata_crescator);
}

void Service::golire_lista()
{
	this->repo.distruge_repo();
	Repo repo;
	this->repo = repo;
	this->id = 0;
}

void Service::distruge_service()
{
	this->repo.distruge_repo();
	for (auto& i : this->lista_undo)
	{
		i.get()->~Undo();
	}
	this->lista_undo.~vector();
}

void Service::get_all_service(vector<Activitate>* v)
{
	this->repo.get_all_repo(v);
}

void Service::teste_service()
{
	Repo repo;
	Service service(repo);
	service.distruge_service();
}

Repo* Service::pointer_repo()
{
	return &(this->repo);
}

void Service::undo_service()
{
	if (this->lista_undo.empty())
		throw ServiceEx("Lista de undo este goala.");

	//auto u = this->lista_undo[this->lista_undo.size() - 1];
	//auto st = this->lista_undo.erase(this->lista_undo.end() - 1);
	//u.get()->doUndo();
	unique_ptr<Undo> u = move(this->lista_undo.back());
	u->doUndo();
	this->lista_undo.pop_back();
}

ServiceEx::ServiceEx(string er)
{
	this->mesaj = "Service error : " + er + "\n";
}
