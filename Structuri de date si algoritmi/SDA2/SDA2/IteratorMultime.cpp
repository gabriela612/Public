#include "IteratorMultime.h"
#include "Multime.h"
#include <iostream>


IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	/* de adaugat */
	this->it = this->multime.start;
}
// Theta(1)


void IteratorMultime::prim() {
	/* de adaugat */
	this->it = this->multime.start;
}
// Theta(1)


void IteratorMultime::urmator() {
	/* de adaugat */
	if (this->valid())
		this->it = this->it->urm;
}
//O(n) (n = numarul de elemente)
// Best = Theta(1), Worst = Theta(n)


TElem IteratorMultime::element() const {
	/* de adaugat */
	if (this->valid() == false)
		return NULL_TELEM;
	return this->it->e;
}
//O(n) (n = numarul de elemente)
// Best = Theta(1), Worst = Theta(n)

bool IteratorMultime::valid() const {
	/* de adaugat */
	if (this->it == NULL or this->multime.cauta(this->it->e) == false)
		return false;
	return true;
}
//O(n) (n = numarul de elemente)
// Best = Theta(1), Worst = Theta(n)
