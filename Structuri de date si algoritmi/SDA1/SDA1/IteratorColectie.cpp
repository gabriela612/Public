#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>
#include <iostream>

using namespace std;


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	prim();
}

void IteratorColectie::prim() {
    // Cel mai bun caz : Theta(1) (gasim un element pe prima pozitie)
    // Cel mai rau caz : Theta(n) (singurul element e pe ultima pozitie)
    // O(n)
    // n = dimensiunea colectiei
	if (this->col.dim() == 0)
	{
		this->curent = -1;
		return;
	}
	this->curent = 0;
	while (this->col.elemente[this->curent] == 0)
		this->curent++;
	this->nr = 1;
}


void IteratorColectie::urmator() {
    // Cel mai bun caz : Theta(1) (nr e egal cu elementul de pe pozitia curenta sau gasim un element nenul pe urmatoarea pozitie)
    // Cel mai rau caz : Theta(n) (parcurgem lista de la inceput la final)
    // O(n)
    // n = dimensiunea colectiei
	if (this->valid() == false)
		throw _exception();
	if (this->nr < this->col.elemente[this->curent])
	{
		this->nr++;
		return;
	}
	this->curent++;
	while (this->col.elemente[this->curent] == 0 and this->curent != this->col.final - this->col.start + 1)
		this->curent++;
	this->nr = 1;
}


bool IteratorColectie::valid() const {
    // Theta(1)
	if (this->col.elemente[this->curent] == 0 or this->curent > this->col.final - this->col.start or this->curent < 0 or this->nr < 1 or this->nr > this->col.elemente[this->curent])
		return false;
	return true;
}



TElem IteratorColectie::element() const {
    // Theta(1)
	if (this->valid() == false)
		throw _exception();
	return (this->curent + this->col.start);
}
