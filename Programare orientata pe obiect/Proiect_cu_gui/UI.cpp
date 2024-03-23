/*
#include "UI.h"

void UI::inceput()
{
	int cer;
	while (true)
	{
		afisare_meniu();
		//vector<Activitate>v;
		//this->service.get_all_service(&v);
		//afisare_activitati(v);
		//v.~vector();
		cer = citire_cerinta();
		if (cer == 0)
			break;
		cout << endl;
		if (cer <= 9)
			apelare_cerinta(cer);
		else
			break;
		cout << endl;
	}
}

void UI::adaugare_ui()
{
	string titlu, descriere, tip;
	string durata;
	cout << "Introduceti titlul : ";
	cin >> titlu;
	cout << "Introduceti descrierea : ";
	cin >> descriere;
	cout << "Introduceti tipul : ";
	cin >> tip;
	cout << "Introduceti durata : ";
	cin >> durata;

	int ok = 0;
	int dur, p;
	while (ok == 0)
	{
		ok = 1;
		dur = 0;
		p = 1;
		for (unsigned int i = 0; i < durata.size() and ok == 1; i++)
		{
			if (durata[i] < '0' or durata[i] > '9')
			{
				cout << "Durata trebuie sa fie un numar natural.\nIntroduceti durata : ";
				cin >> durata;
				ok = 0;
			}
			else
			{
				dur = dur * 10 + (int)(durata[i] - '0');
				p *= 10;
			}
		}
	}
	try
	{
		this->service.adaugare_service(&titlu, &descriere, &tip, dur);
		cout << "Adaugarea a fost efectuata cu succes.\n";
	}
	catch (ServiceEx er)
	{
		cout << er.mesaj;
	}
	durata.~basic_string();
	titlu.~basic_string();
	descriere.~basic_string();
	tip.~basic_string();
}

void UI::stergere_ui()
{
	string id;
	cout << "Introduceti id-ul : ";
	cin >> id;
	int ok = 0;
	int iid, p;
	while (ok == 0)
	{
		ok = 1;
		iid = 0;
		p = 1;
		//for (unsigned int i = 0; i < id.size() and ok == 1; i++)
		//{
			//if (id[i] < '0' or id[i] > '9')
			//{
				//cout << "Id-ul trebuie sa fie un numar natural.\nIntroduceti id-ul : ";
				//cin >> id;
				//ok = 0;
			//}
			//else
			//{
				//iid = iid * 10 + (int)(id[i] - '0');
				//p *= 10;
			//}
		//}
		for (auto& i : id)
		{
			if (i < '0' or i > '9')
			{
				cout << "Id-ul trebuie sa fie un numar natural.\nIntroduceti id-ul : ";
				cin >> id;
				ok = 0;
			}
			else
			{
				iid = iid * 10 + (int)(i - '0');
				p *= 10;
			}
			if (ok == 0)
				break;
		}
	}
	try
	{
		this->service.stergere_service(iid);
		cout << "Stergerea a fost efectuata cu succes.\n";
	}
	catch (ServiceEx er)
	{
		cout << er.mesaj;
	}
	id.~basic_string();
}

void UI::modificare_ui()
{
	string id;
	cout << "Introduceti id-ul : ";
	cin >> id;
	int ok = 0;
	int iid, p;
	while (ok == 0)
	{
		ok = 1;
		iid = 0;
		p = 1;
		//for (unsigned int i = 0; i < id.size() and ok == 1; i++)
		//{
			//if (id[i] < '0' or id[i] > '9')
			//{
				//cout << "Id-ul trebuie sa fie un numar natural.\nIntroduceti id-ul : ";
				//cin >> id;
				//ok = 0;
			//}
			//else
			//{
				//iid = iid * 10 + (int)(id[i] - '0');
				//p *= 10;
			//}
		//}
		for (auto& i : id)
		{
			if (i < '0' or i > '9')
			{
				cout << "Id-ul trebuie sa fie un numar natural.\nIntroduceti id-ul : ";
				cin >> id;
				ok = 0;
			}
			else
			{
				iid = iid * 10 + (int)(i - '0');
				p *= 10;
			}
			if (ok == 0)
				break;
		}
	}
	id.~basic_string();
	int poz = this->service.cautare_id_service(iid);
	if (poz == -1)
	{
		cout << "Nu exista nicio activitate cu id-ul dat!\n";
		return;
	}
	string titlu, descriere, tip;
	try
	{
		string durata;
		cout << "Introduceti titlul : ";
		cin >> titlu;
		cout << "Introduceti descrierea : ";
		cin >> descriere;
		cout << "Introduceti tipul : ";
		cin >> tip;
		cout << "Introduceti durata : ";
		cin >> durata;

		int ok = 0;
		int dur, p;
		while (ok == 0)
		{
			ok = 1;
			dur = 0;
			p = 1;
			//for (unsigned int i = 0; i < durata.size() and ok == 1; i++)
			//{
				//if (durata[i] < '0' or durata[i] > '9')
				//{
					//cout << "Durata trebuie sa fie un numar natural.\nIntroduceti durata : ";
					//cin >> durata;
					//ok = 0;
				//}
				//else
				//{
					//dur = dur * 10 + (int)(durata[i] - '0');
					//p *= 10;
				//}
			//}
			for (auto& i : durata)
			{
				if (i < '0' or i > '9')
				{
					cout << "Durata trebuie sa fie un numar natural.\nIntroduceti durata : ";
					cin >> durata;
					ok = 0;
				}
				else
				{
					dur = dur * 10 + (int)(i - '0');
					p *= 10;
				}
				if (ok == 0)
					break;
			}
		}
		durata.~basic_string();
		this->service.modificare_service(iid, &titlu, &descriere, &tip, dur);
	}
	catch (ServiceEx er)
	{
		cout << er.mesaj;
	}
	titlu.~basic_string();
	descriere.~basic_string();
	tip.~basic_string();
}

void UI::filtrare_ui()
{
	cout << "1. Filtrare dupa descriere.\n";
	cout << "2. Filtrare dupa tip.\n";
	cout << "Introduceti optiunea : ";
	char opt;
	cin >> opt;
	while (opt != '1' and opt != '2')
	{
		cout << "Optiunea introdusa trebuie sa fie 1 sau 2.\n";
		cout << "Introduceti optiunea : ";
		cin >> opt;
	}
	string ceva;
	if (opt == '1')
	{
		cout << "Introduceti un sir de caractere care vreti sa apara in descriere : ";
	}
	else
	{
		cout << "Introduceti un sir de caractere care vrei sa apara in tip : ";
	}
	cin >> ceva;
	try
	{
		if (opt == '1')
		{
			vector<Activitate>v;
			this->service.filtrare_descriere(&v, &ceva);
			afisare_activitati(&v);
			v.~vector();
		}
		else
		{
			vector<Activitate>v;
			this->service.filtrare_tip(&v, &ceva);
			afisare_activitati(&v);
			v.~vector();
		}
	}
	catch (ServiceEx er)
	{
		cout << er.mesaj;
	}

	ceva.~basic_string();
}

void UI::sortare_ui()
{
	cout << "1. Sortare dupa titlu.\n";
	cout << "2. Sortare dupa tip si durata.\n";
	cout << "Introduceti optiunea : ";
	char opt;
	cin >> opt;
	while (opt != '1' and opt != '2')
	{
		cout << "Optiunea introdusa trebuie sa fie 1 sau 2.\n";
		cout << "Introduceti optiunea : ";
		cin >> opt;
	}
	try
	{
		if (opt == '1')
		{
			vector<Activitate>v;
			this->service.sortare_titlu(&v);
			afisare_activitati(&v);
			v.~vector();
		}
		else
		{
			vector<Activitate>v;
			this->service.sortare_tip_durata(&v);
			afisare_activitati(&v);
			v.~vector();
		}
	}
	catch (ServiceEx(er))
	{
		cout << er.mesaj;
	}
}

void UI::cautare_ui()
{
	string id;
	cout << "Introduceti id-ul : ";
	cin >> id;
	int ok = 0;
	int iid, p;
	while (ok == 0)
	{
		ok = 1;
		iid = 0;
		p = 1;
		//for (unsigned int i = 0; i < id.size() and ok == 1; i++)
		//{
			//if (id[i] < '0' or id[i] > '9')
			//{
				//cout << "Id-ul trebuie sa fie un numar natural.\nIntroduceti id-ul : ";
				//cin >> id;
				//ok = 0;
			//}
			//else
			//{
				//iid = iid * 10 + (int)(id[i] - '0');
				//p *= 10;
			//}
		//}
		for (auto& i : id)
		{
			if (i < '0' or i > '9')
			{
				cout << "Id-ul trebuie sa fie un numar natural.\nIntroduceti id-ul : ";
				cin >> id;
				ok = 0;
			}
			else
			{
				iid = iid * 10 + (int)(i - '0');
				p *= 10;
			}
			if (ok == 0)
				break;
		}
	}
	id.~basic_string();
	Activitate act;
	try
	{
		this->service.cautare_service(iid, &act);

		string titlu, descriere, tip;
		printf("%2s %10s %40s %40s %17s", "ID", "Titlu", "Descriere", "Tip", "Durata\n");

		act.get_titlu(&titlu);
		act.get_descriere(&descriere);
		act.get_tip(&tip);

		cout << endl;
		cout << act.get_id();

		if ((20 - titlu.size()) % 2)
			cout << " ";
		unsigned int j = 1;
		while (j < (20 - titlu.size()) / 2)
		{
			cout << " ";
			j++;
		}
		cout << titlu;
		j = 1;
		while (j <= (20 - titlu.size()) / 2)
		{
			cout << " ";
			j++;
		}
		if ((20 - titlu.size()) % 2)
			cout << " ";

		j = 1;
		while (j < (60 - descriere.size()) / 2)
		{
			cout << " ";
			j++;
		}
		cout << descriere;
		j = 1;
		while (j <= (60 - descriere.size()) / 2)
		{
			cout << " ";
			j++;
		}
		if ((60 - descriere.size()) % 2)
			cout << " ";

		j = 1;
		while (j < (30 - tip.size()) / 2)
		{
			cout << " ";
			j++;
		}
		cout << tip;
		j = 1;
		while (j <= (30 - tip.size()) / 2)
		{
			cout << " ";
			j++;
		}
		if ((30 - tip.size()) % 2)
			cout << " ";
		cout << act.get_durata() << endl;

		titlu.~basic_string();
		descriere.~basic_string();
		tip.~basic_string();
	}
	catch (ServiceEx er)
	{
		cout << er.mesaj;
	}
	act.~Activitate();
}

void UI::golire_ui()
{
	this->service.golire_lista();
	cout << "Golirea listei a fost efectuata cu succes!\n";
}

void UI::creare_lista()
{
	Repo repo;
	Lista_de_activitati li(repo);
	while (true)
	{
		cout << "0. Exit.\n";
		cout << "1. Adauga in lista.\n";
		cout << "2. Goleste lista.\n";
		cout << "3. Genereaza lista.\n";
		cout << "4. Exporta lista.\n";
		char opt;
		cout << "Introduceti optiunea : ";
		cin >> opt;
		while (opt != '1' and opt != '2' and opt != '3' and opt != '4' and opt != '0')
		{
			cout << "Optiunea introdusa trebuie sa fie 0, 1, 2, 3 sau 4.\n";
			cout << "Introduceti optiunea : ";
			cin >> opt;
		}
		if (opt == '1')
		{
			string id;
			cout << "Introduceti id-ul : ";
			cin >> id;
			int ok = 0;
			int iid, p;
			while (ok == 0)
			{
				ok = 1;
				iid = 0;
				p = 1;
				for (auto& i : id)
				{
					if (i < '0' or i > '9')
					{
						cout << "Id-ul trebuie sa fie un numar natural.\nIntroduceti id-ul : ";
						cin >> id;
						ok = 0;
					}
					else
					{
						iid = iid * 10 + (int)(i - '0');
						p *= 10;
					}
					if (ok == 0)
						break;
				}
			}
			id.~basic_string();
			try
			{
				li.adauga_lista(iid, &(this->service));
			}
			catch (string er)
			{
				cout << er;
			}
		}

		if (opt == '2')
		{
			li.goleste_lista();
		}

		if (opt == '3')
		{
			string snr;
			cout << "Introduceti numarul : ";
			cin >> snr;
			int ok = 0;
			int nr, p;
			while (ok == 0)
			{
				ok = 1;
				nr = 0;
				p = 1;
				for (auto& i : snr)
				{
					if (i < '0' or i > '9')
					{
						cout << "Trebuie sa introduceti un numar natural.\nIntroduceti numarul : ";
						cin >> snr;
						ok = 0;
					}
					else
					{
						nr = nr * 10 + (int)(i - '0');
						p *= 10;
					}
					if (ok == 0)
						break;
				}
			}
			snr.~basic_string();
			try
			{
				li.genereaza_lista(nr, &(this->service));
			}
			catch (string a)
			{
				cout << a;
			}
			catch (MaiPutine a)
			{
				cout << "S-au putut genera doar " << a.nr << " activitati.\n";
			}
		}

		if (opt == '0')
		{
			li.~Lista_de_activitati();
			return;
		}

		if (opt == '4')
		{
			cout << "Introduceti numele fisierului : ";
			string nume_fisier;
			cin >> nume_fisier;
			li.exporta_lista(nume_fisier);
			nume_fisier.~basic_string();
		}

		vector<Activitate> ve;
		repo.get_all_repo(&ve);
		afisare_activitati(&ve);
	}
}

void UI::afisare_meniu()
{
	cout << "0. Iesire.\n";
	cout << "1. Adaugare.\n";
	cout << "2. Stergere.\n";
	cout << "3. Modificare.\n";
	cout << "4. Cautare activitate.\n";
	cout << "5. Afisarea tuturor activitatilor.\n";
	cout << "6. Filtrare.\n";
	cout << "7. Sortare.\n";
	cout << "8. Crearea unei liste de activitati.\n";
	cout << "9. Undo.\n";
}

int UI::citire_cerinta()
{
	cout << "Introduceti cerinta : ";
	char cer;
	cin >> cer;
	if (cer < '0' or cer > '9')
	{
		cout << "\nCerinta incorecta.\n";
		return citire_cerinta();
	}
	return (int)(cer - '0');
}

void UI::apelare_cerinta(int cer)
{
	switch (cer)
	{
	case 1:
		adaugare_ui();
		break;
	case 2:
		stergere_ui();
		break;
	case 3:
		modificare_ui();
		break;
	case 4:
		cautare_ui();
		break;
	case 5:
	{
		vector<Activitate>v;
		this->service.get_all_service(&v);
		afisare_activitati(&v);
		v.~vector();
		break;
	}
	case 6:
		filtrare_ui();
		break;
	case 7:
		sortare_ui();
		break;
	case 8:
		creare_lista();
		break;
	case 9:
		undo_ui();
		break;
	}
}

void UI::afisare_activitati(vector<Activitate>* v)
{
	cout << endl;
	if ((*v).size() == 0)
		return;
	string titlu, descriere, tip;
	printf("%2s %10s %40s %40s %17s", "ID", "Titlu", "Descriere", "Tip", "    Durata\n");
	//for (unsigned int i = 0; i < (*v).size(); i++)
	for (auto& i : (*v))
	{
		i.get_titlu(&titlu);
		i.get_descriere(&descriere);
		i.get_tip(&tip);

		cout << i.get_id();

		if ((20 - titlu.size()) % 2)
			cout << " ";
		unsigned int j = 1;
		while (j < (20 - titlu.size()) / 2)
		{
			cout << " ";
			j++;
		}
		cout << titlu;
		j = 1;
		while (j <= (20 - titlu.size()) / 2)
		{
			cout << " ";
			j++;
		}
		if ((20 - titlu.size()) % 2)
			cout << " ";

		j = 1;
		while (j < (60 - descriere.size()) / 2)
		{
			cout << " ";
			j++;
		}
		cout << descriere;
		j = 1;
		while (j <= (60 - descriere.size()) / 2)
		{
			cout << " ";
			j++;
		}
		if ((60 - descriere.size()) % 2)
			cout << " ";

		j = 1;
		while (j < (30 - tip.size()) / 2)
		{
			cout << " ";
			j++;
		}
		cout << tip;
		j = 1;
		while (j <= (30 - tip.size()) / 2)
		{
			cout << " ";
			j++;
		}
		if ((30 - tip.size()) % 2)
			cout << " ";

		cout << i.get_durata() << endl;
	}
	cout << endl;
	titlu.~basic_string();
	descriere.~basic_string();
	tip.~basic_string();
}

void UI::undo_ui()
{
	try
	{
		this->service.undo_service();
		cout << "Operatia de undo s-a efectuat cu succes.\n";
	}
	catch (ServiceEx er)
	{
		cout << er.mesaj;
	}
}*/


