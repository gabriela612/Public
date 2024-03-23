#include "IteratorColectie.h"
#include "Colectie.h"
#define mx 987654

//Theta(1)
//Theta(m)
//O(m)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	prim();
}

//Theta(1)
//Theta(m)
//O(m)
void IteratorColectie::prim() {
	/* de adaugat */
	curent = 0;
	while (col.elems[curent] == mx and curent < col.m)
		curent++;
}

//Theta(1)
//Theta(m)
//O(m)
void IteratorColectie::urmator() {
	/* de adaugat */
	curent++;
	while (col.elems[curent] == mx and curent < col.m)
		curent++;
}

//Theta(1)
bool IteratorColectie::valid() const {
	/* de adaugat */
	if (curent >= col.m or curent < 0 or col.elems[curent] == mx)
		return false;
	return true;
}

//Theta(1)
TElem IteratorColectie::element() const {
	/* de adaugat */
	if (valid())
		return col.elems[curent];
	return -1;
}
