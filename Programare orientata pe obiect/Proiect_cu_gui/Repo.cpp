#include "Repo.h"




Repo::Repo()
{

}

void Repo::adaugare_repo(Activitate& act)
{
	this->v.push_back(act);
}

void Repo::pune_activitate_pe_pozitia(Activitate* act, int poz)
{
	if (poz < 0 and poz >= (int)this->v.size())
		return;
	this->v[poz] = *act; /// posibila greseala
}

bool Repo::get_activitate_poz_repo(Activitate* act, int poz) const
{
	if (poz < 0 and poz >= (int)this->v.size())
		return 0;
	*act = this->v[poz];
	return 1;
}

int Repo::cautare_pozitie_id_repo(int id_cautat) const
{
	/*for (int i = 0; i < (int)this->v.size(); i++)
	{
		if (this->v[i].get_id() == id_cautat)
			return i;
	}
	return -1;*/

	auto poz = find_if(v.begin(), v.end(), [id_cautat](Activitate act) {return act.are_id(act, id_cautat); });
	if (poz == v.end())
		return -1;
	return distance(v.begin(), poz);

}

int Repo::cautare_pozitie_activitate_repo(Activitate& act_cautata) const
{
	if (this->v.size() == 0)
		return -1;
	/*string titlu_cautat = "", descriere_cautata = "", tip_cautat = "";
	string titlu_curent = "", descriere_curenta = "", tip_curent = "";
	for (int i = 0; i < (int)this->v.size(); i++)
	{
		Activitate act_curenta;
		this->get_activitate_poz_repo(&act_curenta, i);

		if (act_curenta.egal_activitati(act_curenta, act_cautata))
		{
			titlu_cautat.~basic_string();
			titlu_curent.~basic_string();
			descriere_cautata.~basic_string();
			descriere_curenta.~basic_string();
			tip_cautat.~basic_string();
			tip_curent.~basic_string();
			return i;
		}
	}
	titlu_cautat.~basic_string();
	titlu_curent.~basic_string();
	descriere_cautata.~basic_string();
	descriere_curenta.~basic_string();
	tip_cautat.~basic_string();
	tip_curent.~basic_string();
	return -1;*/


	auto poz = find_if(v.begin(), v.end(), [act_cautata](Activitate act) {return act.egal_activitati(Activitate(act_cautata), act); });
	if (poz == v.end())
		return -1;
	return distance(v.begin(), poz);
}

void Repo::modificare_activitate_pozitie(int poz, string* titlu, string* descriere, string* tip, int durata)
{
	this->v[poz].set_titlu(titlu);
	this->v[poz].set_descriere(descriere);
	this->v[poz].set_tip(tip);
	this->v[poz].set_durata(durata);
}

bool Repo::repo_vid()
{
	if (this->len() == 0)
		return 1;
	return 0;
}

int Repo::len()
{
	return int(this->v.size());
}

void Repo::get_all_repo(vector<Activitate>* v) const
{
	*v = this->v;
}

void Repo::distruge_repo()
{
	/*for (int i = 0; i < this->v.size(); i++)
	{
		this->v[i].~Activitate();
	}*/
	for (auto& i : v)
	{
		i.~Activitate();
	}
	this->v.~vector();
}

void Repo::distruge_activitate_pozitie(int poz)
{
	if (poz < 0 and poz >= (int)this->v.size())
		return;
	this->v[poz].~Activitate();
}

void Repo::arunca_ultima_activitate()
{
	if (this->repo_vid())
		return;
	auto act = v.erase(v.end() - 1);
}

void Repo::teste_repo()
{
	Repo repo;
	assert(repo.repo_vid() == 1);
	Activitate act;
	string a = "a", b = "b", c = "c";
	act.creare_activitate(&a, &b, &c, 1, 2);
	repo.adaugare_repo(act);
	assert(repo.repo_vid() == 0);
	Activitate act2;
	assert(repo.cautare_pozitie_activitate_repo(act) == 0);
	assert(repo.cautare_pozitie_id_repo(2) == 0);
	assert(repo.cautare_pozitie_id_repo(1) == -1);
	assert(repo.len() == 1);
	repo.distruge_repo();
	act.~Activitate();
	act2.~Activitate();
}

Activitate* Repo::get_pointer_activitate_poz(int poz)
{
	return &(this->v[poz]);
}

void Repo::s1()
{
	sort(this->v.begin(), this->v.end(), titlu_crescator);
}

void Repo::s2()
{
	sort(this->v.begin(), this->v.end(), tip_durata_crescator);
}


