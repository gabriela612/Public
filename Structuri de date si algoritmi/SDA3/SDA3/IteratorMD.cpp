#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	/* de adaugat */
	it = this->md.prim;
}
// Theta(1)

TElem IteratorMD::element() const{
	/* de adaugat */
	//pair <TCheie, TValoare> el = this->md.elem[it];
	return this->md.elem[this->it];
}
// Theta(1)

bool IteratorMD::valid() const {
	/* de adaugat */
	if (this->md.vid() == true)
		return false;
	int inc = this->md.prim;
	int ok = 0;
	for (int i = 1; i <= this->md.nr_elem; i++)
	{
		if (inc == this->it)
			ok = 1;
		inc = this->md.urm[inc];
	}
	if (ok == 0)
		return false;
	
	vector<TValoare> val = this->md.cauta(this->element().first);
	for (int i = 0; i < val.size(); i ++)
		if (val[i] == this->element().second)
			return true;
	
	return true;
}
// O(n)
// Best = Theta(1), Worst = Theta(n)

void IteratorMD::urmator() {
	/* de adaugat */
	if (this->valid() == false)
	{
		this->it = 0;
	}
	this->it = this->md.urm[this->it];
}
// Theta(1)

void IteratorMD::prim() {
	/* de adaugat */
	it = this->md.prim;
}
// Theta(1)

