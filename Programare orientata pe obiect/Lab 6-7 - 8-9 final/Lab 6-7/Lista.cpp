#include "Lista.h"


void Lista_de_activitati::adauga_lista(int id, Service* service)
{
	vector<Activitate> ve;
	service->get_all_service(&ve);

	int ex = 0;
	Activitate act;
	for (auto& i : ve)
	{
		if (i.get_id() == id)
		{
			ex = 1;
			act = i;
		}
	}
	if (ex == 0)
	{
		act.~Activitate();
		ve.~vector();
		throw string("Id-ul dat nu exista.\n");
	}

	if (this->repo.cautare_pozitie_activitate_repo(act) != -1)
	{
		act.~Activitate();
		ve.~vector();
		throw string("Activitatea cu is-ul dat exista deja in lista.\n");
	}
	this->repo.adaugare_repo(act);
	ve.~vector();
}

void Lista_de_activitati::goleste_lista()
{
	this->repo.distruge_repo();
	Repo repo;
	this->repo = repo;
}

void Lista_de_activitati::genereaza_lista(int nr, Service* service)
{
	vector<Activitate> ve;
	service->get_all_service(&ve);
	if (nr > (int)ve.size() - this->repo.len())
	{
		int ret = (int)ve.size() - this->repo.len();
		for (auto& i : ve)
		{
			try
			{
				adauga_lista(i.get_id(), service);
			}
			catch (string a)
			{

			}
		}
		//throw string("S-au adaugat mai putine activitati.\n");
		throw MaiPutine(ret);
	}
	int contor = 0, erori = 0;
	while (contor != nr and erori < nr * 3)
	{
		mt19937 mt{ std::random_device{}() };
		uniform_int_distribution<> dist(0, ve.size() - 1);
		int poz = dist(mt);
		try
		{
			adauga_lista(ve[poz].get_id(), service);
			contor++;
		}
		catch (string a)
		{
			erori++;
		}
	}
	if (erori == nr * 3)
		//throw string("S-au adaugat mai putine activitati.\n");
		throw MaiPutine(contor);
}

Lista_de_activitati::~Lista_de_activitati()
{
	this->repo.distruge_repo();
}

void Lista_de_activitati::exporta_lista(string nume_fisier)
{
	vector<Activitate> v;
	this->repo.get_all_repo(&v);


	ofstream fout;
	fout.open(nume_fisier);
	fout << "<!DOCTYPE html><html>"; //starting html

	string titlu, descriere, tip;

	fout << "<head> <style> table, th, td{ border-style: solid; \n border-collapse: collapse; } </style> </head><body>";

	//add some html content
	//as an example: if you have array of objects featuring the properties name & value, you can print out a new line for each property pairs like this:
	fout << "<table style=\"width:100 % \">";
	fout << "<tr><th>" << "ID" << "</th><th>" << "Titlu" << "</th><th>" << "Descriere" << "</th><th>" << "Tip" << "</th><th>" << "Durata" << "</th></tr>";
	for (auto& i : v)
	{
		i.get_titlu(&titlu);
		i.get_descriere(&descriere);
		i.get_tip(&tip);
		fout << "<tr><td>" << i.get_id() << "</td><td>" << titlu << "</td><td>" << descriere << "</td><td>" << tip << "</td><td>" << i.get_durata() << "</td></tr>";
	}
	fout << "</table>";
	//ending html
	fout << "</body></html>";

	titlu.~basic_string();
	descriere.~basic_string();
	tip.~basic_string();
	v.~vector();

	fout.close();
}


ListaEx::ListaEx(string er)
{
	this->mesaj = "Lista error : " + er + "\n";
}


MaiPutine::MaiPutine(int nr)
{
	this->nr = nr;
}
