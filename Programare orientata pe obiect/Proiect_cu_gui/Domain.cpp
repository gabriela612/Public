#include "Domain.h"



Activitate::Activitate()
{
	this->titlu = "";
	this->descriere = "";
	this->tip = "";
	this->durata = -1;
	this->id = -1;
}

void Activitate::str(string* text)
{
	*text = "";
	*text += to_string(this->id);

	if ((20 - titlu.size()) % 2)
		*text += ' ';
	unsigned int j = 1;
	while (j < (20 - titlu.size()) / 2)
	{
		*text += ' ';
		j++;
	}
	*text += titlu;
	j = 1;
	while (j <= (20 - titlu.size()) / 2)
	{
		*text += ' ';
		j++;
	}
	if ((20 - titlu.size()) % 2)
		*text += ' ';

	j = 1;
	while (j < (60 - descriere.size()) / 2)
	{
		*text += ' ';
		j++;
	}
	*text += descriere;
	j = 1;
	while (j <= (60 - descriere.size()) / 2)
	{
		*text += ' ';
		j++;
	}
	if ((60 - descriere.size()) % 2)
		*text += ' ';

	j = 1;
	while (j < (30 - tip.size()) / 2)
	{
		*text += ' ';
		j++;
	}
	*text += tip;
	j = 1;
	while (j <= (30 - tip.size()) / 2)
	{
		*text += ' ';
		j++;
	}
	if ((30 - tip.size()) % 2)
		*text += ' ';

	*text += to_string(this->durata);
}

void Activitate::creare_activitate(string* titlu, string* descriere, string* tip, int durata, int id)
{
	set_titlu(titlu);
	set_descriere(descriere);
	set_tip(tip);
	set_durata(durata);
	set_id(id);
}

void Activitate::get_titlu(string* copie)
{
	*copie = this->titlu;
}

void Activitate::get_descriere(string* copie)
{
	*copie = this->descriere;
}

void Activitate::get_tip(string* copie)
{
	*copie = this->tip;
}

int Activitate::get_durata() const
{
	return this->durata;
}

int Activitate::get_id() const
{
	return this->id;
}

void Activitate::set_titlu(string* titlu_nou)
{
	this->titlu = *titlu_nou;
}

void Activitate::set_descriere(string* descriere_noua)
{
	this->descriere = *descriere_noua;
}

void Activitate::set_tip(string* tip_nou)
{
	this->tip = *tip_nou;
}

void Activitate::set_durata(int durata_noua)
{
	this->durata = durata_noua;
}

void Activitate::set_id(int id_nou)
{
	this->id = id_nou;
}

bool Activitate::egal_id(Activitate& act1, Activitate& act2) const
{
	if (act1.get_id() == act2.get_id())
		return 1;
	return 0;
}

bool Activitate::egal_activitati(Activitate act1, Activitate act2) const
{
	string titlu1 = "", descriere1 = "", tip1 = "";
	string titlu2 = "", descriere2 = "", tip2 = "";
	act1.get_titlu(&titlu1);
	act1.get_descriere(&descriere1);
	act1.get_tip(&tip1);
	act2.get_titlu(&titlu2);
	act2.get_descriere(&descriere2);
	act2.get_tip(&tip2);
	if (titlu1 == titlu2 and descriere1 == descriere2 and tip1 == tip2 and act1.get_durata() == act2.get_durata())
		return 1;
	return 0;
}


void Activitate::teste_domain()
{
	// teste creare si get
	Activitate act;
	string a = "a", b = "b", c = "c";
	act.creare_activitate(&a, &b, &c, 1, 2);
	string titlu, descriere, tip;
	act.get_titlu(&titlu);
	act.get_descriere(&descriere);
	act.get_tip(&tip);
	assert(titlu == "a");
	assert(descriere == "b");
	assert(tip == "c");
	assert(act.get_durata() == 1);
	assert(act.get_id() == 2);
	Activitate acts1 = act;
	acts1.~Activitate();

	// teste set
	act.set_titlu(&b);
	act.set_descriere(&c);
	act.set_tip(&a);
	act.set_durata(2);
	act.set_id(3);
	act.get_titlu(&titlu);
	act.get_descriere(&descriere);
	act.get_tip(&tip);
	assert(titlu == "b");
	assert(descriere == "c");
	assert(tip == "a");
	assert(act.get_durata() == 2);
	assert(act.get_id() == 3);

	// teste egalitate
	Activitate act2;
	act2.creare_activitate(&b, &c, &a, 2, 3);
	assert(act.egal_activitati(act, act2) == 1);
	act2.creare_activitate(&b, &c, &a, 1, 2);
	assert(act.egal_activitati(act, act2) == 0);
	bool as = titlu_crescator(act, act2);
	bool bs = tip_durata_crescator(act, act2);
	bool cs = tip_egal(act2, &a);
	bool ds = descriere_egala(act2, &a);

	// stergere
	a.~basic_string();
	b.~basic_string();
	c.~basic_string();
	act.~Activitate();
	act2.~Activitate();
}

Activitate& Activitate::operator=(Activitate x)
{
	string titlu, desc, tip;
	x.get_titlu(&titlu);
	x.get_descriere(&desc);
	x.get_tip(&tip);
	this->set_titlu(&titlu);
	this->set_descriere(&desc);
	this->set_tip(&tip);
	this->set_durata(x.get_durata());
	this->set_id(x.get_id());
	titlu.~basic_string();
	desc.~basic_string();
	tip.~basic_string();
	return *this;
}

Activitate::~Activitate()
{
	this->titlu.~basic_string();
	this->descriere.~basic_string();;
	this->tip.~basic_string();
}

bool Activitate::are_id(Activitate act, int id)
{
	if (act.get_id() == id)
		return true;
	return false;
}

bool titlu_crescator(Activitate a, Activitate b)
{
	string titlua, titlub;
	bool rez;

	a.get_titlu(&titlua);
	b.get_titlu(&titlub);

	//cout << titlua << " " << titlub << endl;

	rez = (titlua < titlub);

	titlua.~basic_string();
	titlub.~basic_string();

	return (bool)(rez);
}

bool tip_durata_crescator(Activitate a, Activitate b)
{
	string tipa, tipb;
	bool rez;

	a.get_tip(&tipa);
	b.get_tip(&tipb);

	if (tipa < tipb)
		rez = true;
	else
	{
		if (tipa == tipb and a.get_durata() < b.get_durata())
			rez = true;
		else
			rez = false;

	}

	tipa.~basic_string();
	tipb.~basic_string();

	return rez;
}

bool tip_egal(Activitate a, string* tip)
{
	bool rez = true;
	string tipa;
	a.get_tip(&tipa);
	rez = bool(tipa == *tip);
	tipa.~basic_string();
	return rez;
}

bool descriere_egala(Activitate a, string* descriere)
{
	bool rez = true;
	string desca;
	a.get_descriere(&desca);
	if (desca == *descriere)
		rez = true;
	else
		rez = false;
	desca.~basic_string();
	return rez;
}

//void creare_range(int n, int* v)
//{
//
//}
