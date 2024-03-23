#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Multime::Multime() {
	/* de adaugat */
	this->start = NULL;
}


bool Multime::adauga(TElem elem) {
	/* de adaugat */
	if (this->cauta(elem) == true)
		return false;
	Nod *n = new Nod;
	n->urm = NULL;
	n->e = elem;
	Nod* st = this->start;
	if (st == NULL)
	{
		this->start = n;
		return true;
	}
	while (st->urm != NULL)
		st = st->urm;
	st->urm = n;
	return true;
}
//O(n) (n = numarul de elemente)
// Best = Theta(1), Worst = Theta(n)


bool Multime::sterge(TElem elem) {
	/* de adaugat */
	if (this->start == NULL)
		return false;
	if (this->cauta(elem) == false)
		return false;
	Nod* inainte = this->start;
	if (this->start->e == elem)
	{
		this->start = this->start->urm;
		delete inainte;
		return true;
	}
	while (inainte->urm->e != elem)
		inainte = inainte->urm;
	Nod* de_sters = inainte->urm;
	inainte->urm = de_sters->urm;
	delete de_sters;
	return true;
}
//Theta(n) (n = numarul de elemente)


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	Nod* st = this->start;
	while (st != NULL)
	{
		if (st->e == elem)
			return true;
		st = st->urm;
	}
	return false;
}
//O(n) (n = numarul de elemente)
// Best = Theta(1), Worst = Theta(n)


int Multime::dim() const {
	/* de adaugat */
	Nod* st = this->start;
	int nr = 0;
	while (st != NULL)
	{
		st = st->urm;
		nr++;
	}
	return nr;
}
//Theta(n) (n = numarul de elemente)

bool Multime::vida() const {
	/* de adaugat */
	if (this->dim() == 0)
		return true;
	return false;
}
//Theta(1)


Multime::~Multime() {
	/* de adaugat */
	Nod* st = this->start;
	while (st != NULL)
	{
		Nod* n = st;
		st = st->urm;
		delete n;
	}
}
//Theta(n) (n = numarul de elemente)



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

void Multime::reuniune(const Multime& b)
{
	IteratorMultime it(b);
	while (it.valid())
	{
		bool nu_conteaza = this->adauga(it.element());
	}
}
//O(nx(n+m)) (n = numarul de elemente din b, m = numarul de elemnete din a)


/*
Subalgoritm reuniune(b)
	it <- IteratorMultime(b)
	cat timp it.valid()
		nu_conteaza <- adauga(it.element())
*/

