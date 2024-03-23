#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
    // Theta(cap)
	this->cap = 5;
	this->elemente = new TElem[this->cap];
	this->start = 0;
	this->final = 0;
	for (int i = 0; i < this->cap; i++)
		this->elemente[i] = 0;
}


void Colectie::adauga(TElem elem) {
    // Cel mai bun caz : Theta(1)
    // Cel mai rau caz : Theta(n)
    // Complexitate amortizata : O(n)
    // n = numarul de elemente din colectie

	if (elem < this->start)  /// daca am gasit un elemnet mai mic decat minimul de pana acum
	{
		int diferenta = this->start - elem; /// modulul diferentei dintre valoarea minima care a fost in container si elementul pe care vrem sa il adaugam
		while (this->cap <= this->final - elem) /// daca intre elem si final sunt mai multe elemente decat capacitatea curenta
		{
			redimensionare();
		}
		for (int i = this->final - this->start; i >= 0; i--)
		{
			this->elemente[i + diferenta] = this->elemente[i];
		}
		for (int i = 1; i < diferenta; i++)
			this->elemente[i] = 0;
		this->elemente[0] = 1;
		this->start = elem;
		return;
	}
	if (elem > this->final)
	{
		int diferenta = elem - this->final;
		while (this->cap <= elem - this->start)
		{
			redimensionare();
		}
		this->elemente[elem - this->start] = 1;
		this->final = elem;
		return;
	}
	this->elemente[elem - this->start]++;
}


bool Colectie::sterge(TElem elem) {
    // Cel mai bun caz : Theta(1) (frecventa initiala a elementului curent este mai mare decat 1 sau elementul anterior celui curent este nenul)
    // Cel mai rau caz : Theta(n) (stergem ultimul element din lista)
    // O(n)
    // n = lungimea listei
	if (elem > this->final or elem < this->start)
		return false;
	if (this->elemente[elem - this->start])
	{
		if (elem == this->final and this->elemente[elem - this->start] == 1)
		{
			this->final--;
			while (this->final > 0 and this->elemente[this->final - this->start] == 0)
				this->final--;
		}
		this->elemente[elem - this->start] --;
		return true;
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
    // Theta(1)
	if (elem > this->final or elem < this->start)
		return false;
	if (this->elemente[elem - this->start] != 0)
		return true;
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
    // Theta(1)
	if (elem > this->final or elem < this->start)
		return false;
	return this->elemente[elem - this->start];
}


int Colectie::dim() const {
    // Theta(n)
    // n = lungimea listei
	int nrelem = 0;
	for (int i = 0; i <= this->final - this->start; i++)
	{
		nrelem += this->elemente[i];
	}
	return nrelem;
}


bool Colectie::vida() const {
    // Theta(1)
	int nrelem = this->dim();
	if (nrelem)
		return false;
	return true;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
    // Theta(1)
	delete[] this->elemente;
}

void Colectie::goleste()
// Cel mai bun caz Theta(n)
// Cel mai rau caz : Theta(n*n)
// O(n*n)
{
	IteratorColectie it = iterator();
	TElem e;
	while (this->vida() == 0)
	{
		if (it.valid() == 0)
			it.prim();
		e = it.element();
		it.urmator();
		sterge(e);
	}
}

void Colectie::goleste2()
{
	// O(n)
	for (int i = 0; i <= this->final - this->start; i ++)
		this->elemente[i] = 0;
}

void Colectie::redimensionare()
{
    // O(n)
    // n = capacitatea initiala * 2
	TElem* elementenoi = new TElem[this->cap * 2];
	for (int i = 0; i < this->cap; i++)
	{
		elementenoi[i] = this->elemente[i];
	}
	for (int i = this->cap; i < this->cap * 2; i++)
		elementenoi[i] = 0;
	delete[] this->elemente;
	this->elemente = elementenoi;
	this->cap *= 2;
}






/*
subalgoritm goleste()
	it <- iterator()
	cat timp vida() = 0 executa
		daca it.valid() = 0
			it.prim()
		sf_daca
		e <- it.element
		it.urmator()
		sterge(e)
	sf_cat_timp




subalgoritm goleste2()
	pentru i <- 0, final - start executa
		elem[i] <- 0
	sfarsit pentru

*/





