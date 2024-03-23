#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


void MD::Redimensionare()
{
	TElem* elem_nou = new TElem[this->cap * 2];
	int* urm_nou = new int[this->cap * 2];
	for (int i = 0; i < cap; i++)
	{
		urm_nou[i] = this->urm[i];
		elem_nou[i] = this->elem[i];
	}
	for (int i = this->cap; i <= 2 * cap - 2; i++)
	{
		urm_nou[i] = i + 1;
	}
	urm_nou[this->cap * 2 - 1] = 0;
	this->prim_liber = this->cap;
	this->cap *= 2;
	delete[] this->elem;
	delete[] this->urm;
	this->elem = elem_nou;
	this->urm = urm_nou;
}
// Theta(n) (n = 2 * capacitatea initiala)

MD::MD() {
	/* de adaugat */
	this->cap = 10;
	this->nr_elem = 0;
	this->elem = new TElem[this->cap];
	this->urm = new int[this->cap];
	this->prim = 0;
	this->prim_liber = 1;
	for (int i = 0; i <= this->cap - 2; i++)
		this->urm[i] = i + 1;
	this->urm[this->cap - 1] = 0;
}
// Theta(n) (n = capacitatea initiala)


void MD::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	int urm_liber_initial = this->urm[this->prim_liber];
	this->urm[this->prim_liber] = this->prim;
	this->prim = this->prim_liber;
	this->elem[this->prim].first = c;
	this->elem[this->prim].second = v;
	this->prim_liber = urm_liber_initial;
	this->nr_elem++;
	if (this->nr_elem == cap - 1)
		this->Redimensionare();
}
// O(n) amortizat


bool MD::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	if (this->vid())
		return false;
	int i = this->prim;
	if (this->elem[i].first == c and this->elem[i].second == v)
	{
		int ur = this->urm[i];
		this->urm[i] = this->prim_liber;
		this->prim_liber = i;
		this->prim = ur;
		this->nr_elem--;
		return true;
	}
	for (int k = 1; k < this->nr_elem; k ++)
	{
		if (this->elem[this->urm[i]].first == c and this->elem[this->urm[i]].second == v)
		{

			int ind_inainte = i;
			int urm_inainte = this->urm[i]; // a
			int ind_sters = urm_inainte; // a
			int urm_sters = this->urm[ind_sters]; // b
			int ind_dupa = urm_sters; // b
			int urm_dupa = this->urm[ind_dupa]; // nu ne trebuie
			int liber_initial = this->prim_liber;
			int prim_initial = this->prim;


			this->prim_liber = ind_sters;
			this->urm[this->prim_liber] = liber_initial;

			this->urm[ind_inainte] = ind_dupa;


			this->nr_elem--;
			return true;
			
		}
		i = this->urm[i];
	}
	return false;
}
// O(n)
// Best = Theta(1), Worst = Theta(n)


vector<TValoare> MD::cauta(TCheie c) const {
	/* de adaugat */
	vector<TValoare> val;
	int i = this->prim;
	for (int k = 1; k <= this->nr_elem; k++)
	{
		if (this->elem[i].first == c)
			val.push_back(this->elem[i].second);
		i = this->urm[i];
	}
	return val;
}
// O(n)
// Best = Theta(1), Worst = Theta(n)


int MD::dim() const {
	/* de adaugat */
	return this->nr_elem;
}
// Theta(1)


bool MD::vid() const {
	/* de adaugat */
	if (this->dim() == 0)
		return true;
	return false;
}
// Theta(1)

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	/* de adaugat */
	delete[] this->elem;
	delete[] this->urm;
}

void MD::filtreaza(Conditie cond)
{
	IteratorMD it(*this);
	while (it.valid())
	{
		IteratorMD vechi = it;
		it.urmator();
		if (!cond(vechi.element().first))
			this->sterge(vechi.element().first, vechi.element().second);
	}
}
// O(n*n)


/*
	it <- IteratorMD(*this)
	cat timp it.valid(), executa
		vechi <- it
		it.urmator()
		daca cond(vechi.element().first) == false atunci
			sterge(vechi.element().first, vechi.element().second)
		sf_daca
	sf_cat timp



*/
