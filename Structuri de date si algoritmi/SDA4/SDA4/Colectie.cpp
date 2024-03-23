#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>
#include <limits.h>

#define mx 987654
#define tbs 555555

using namespace std;

// Theta(m)
Colectie::Colectie() {
	/* de adaugat */
	m = 200000;
	elems = new TElem[m];
	urm = new int[m];
	d = Dispersie;
	for (int i = 0; i < m; i++)
	{
		urm[i] = -1;
		elems[i] = mx;
	}
	prim_liber = 0;
}

// Theta(1)
// Theta(m)
// Theta(1) amortizat
void Colectie::adauga(TElem elem) {
	/* de adaugat */
	if (elems[d(elem)] == mx)
	{
		elems[d(elem)] = elem;
		//cout << elem << " " << d(elem) << " " << urm[d(elem)] << endl;
		if (prim_liber == d(elem))
			actualizeaza_prim_liber();
		return;
	}
	int poz = d(elem);
	while (urm[poz] != -1)
		poz = urm[poz];
	urm[poz] = prim_liber;
	elems[prim_liber] = elem;
	//cout << elem << " " << prim_liber << " " << urm[prim_liber] << endl;
	actualizeaza_prim_liber();
}

// Theta(1) amortizat
bool Colectie::sterge(TElem elem) {
	/* de adaugat */
	if (cauta(elem) == false)
		return false;
	int poz = d(elem);
	while (elems[poz] != elem)
		poz = urm[poz];
	// poz = pozitia pe care se afla elementul
	//if (urm[poz] == -1)
	//{
	//	elems[poz] = mx;
	//	urm[poz] = -1;
	//}
	//else
	//{
	//	//elems[poz] = mx;
	//	int in = urm[poz];
	//	int inainte = poz;
	//	int gasit = 0;
	//	while (in != -1)
	//	{
	//		if (poz == d(elems[in]))
	//		{
	//			inainte = poz;
	//			elems[poz] = elems[in];
	//			poz = in;
	//			gasit = 1;
	//		}
	//		if (urm[in] == -1)
	//		{
	//			elems[poz] = mx;
	//			urm[inainte] = urm[poz];
	//			urm[poz] = -1;
	//		}
	//		in = urm[in];
	//	}
	//}
	elems[poz] = mx;
	return true;
}

// Theta(1) amortizat
bool Colectie::cauta(TElem elem) const {
	/* de adaugat */
	int poz = d(elem);
	//cout << elem << " " << poz << endl;
	while (elems[poz] != elem and poz != -1) // elems[poz] != mx
		poz = urm[poz];
	if (poz == -1)
		return false;
	if (elems[poz] == elem)
		return true;
	return false;
}

// Theta(1) amortizat
int Colectie::nrAparitii(TElem elem) const {
	/* de adaugat */
	int poz = d(elem);
	int nr_ap = 0;
	while (poz != -1) // elems[poz] != mx and 
	{
		if (elems[poz] == elem)
			nr_ap++;
		poz = urm[poz];
	}
	return nr_ap;
}

// Theta(m)
int Colectie::dim() const {
	/* de adaugat */
	int len = 0;
	for (int i = 0; i < m; i++)
		if (elems[i] != mx)
		{
			len++;
		}
	return len;
}

// Theta(m)
bool Colectie::vida() const {
	/* de adaugat */
	if (dim() == 0)
		return true;
	return false;
}

//Theta(1)
//Theta(m)
//O(m)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

// Theta(1)
// Theta(m)
// O(m)
void Colectie::actualizeaza_prim_liber()
{
	while (prim_liber < m and elems[prim_liber] != mx)
		prim_liber++;
	if (elems[prim_liber] != mx)
	{
		prim_liber = 0;
		actualizeaza_prim_liber();
	}
}

void Colectie::afisare()
{
	for (int i = 0; i <= 1200; i++)
		cout << "i: " << i << ", elem: " << elems[i] << ", urm: " << urm[i] << endl;
}


Colectie::~Colectie() {
	/* de adaugat */
	free(elems);
	free(urm);
}

//Theta(m) amortizat
// n = numarul de elemente din colectie
int Colectie::elementeCuFrecventaData(int frecventa) const
{
	if (frecventa <= 0)
		throw exception();
	int rez = 0;
	IteratorColectie it(*this);
	while (it.valid() == true) // 1 (se executa de n ori)
	{
		if (nrAparitii(it.element()) == frecventa) // 1 amortizat (se executa de n ori)
			rez++;
		it.urmator();
	}
	return (rez / frecventa);
}

/*
Subalgoritm  elementeCuFrecventaData(frecventa)
* daca frecventa <= 0 atunci
*	arunca exceptie
* sf_daca
* rez <- 0
* it <- IteratorColectie([this])
* cat timp it.valid() executa
*	daca nrAparitii(it.element()) = frecventa atunci
*		rez <- rez + 1
*	sf_daca
*	it.urmator()
* sf_cat timp
* elementeCuFrecventaData() <- (rez / frecventa)
*/

// Theta(1)
unsigned int Dispersie(TElem x)
{
	return abs(x) % 10000;
}



