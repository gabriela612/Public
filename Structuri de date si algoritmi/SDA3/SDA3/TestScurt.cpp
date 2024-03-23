#include "TestScurt.h"
#include "MD.h"
#include "IteratorMD.h"
#include <assert.h>
#include <vector>
#include<iostream>

bool impar(TCheie c)
{
	return c % 2;
}

bool par(TCheie c)
{
	return (c + 1) % 2;
}

bool pozitiv(TCheie c)
{
	return c > 0;
}

void tests()
{
	assert(impar(1) == true);
	assert(impar(2) == false);
	assert(par(2) == true);
	assert(par(1) == false);
	assert(pozitiv(-1) == false);
	assert(pozitiv(1) == true);
	MD m;
	m.adauga(1, 1);
	m.adauga(1, 2);
	m.adauga(2, 1);
	m.filtreaza(impar);
	assert(m.dim() == 2);
	m.filtreaza(par);
	assert(m.dim() == 0);
	m.adauga(-2, 2);
	m.filtreaza(pozitiv);
	assert(m.dim() == 0);
	m.adauga(2, 2);
	m.filtreaza(pozitiv);
	assert(m.dim() == 1);
}

void testAll() {
	MD m;
	m.adauga(1, 100);
	m.adauga(2, 200);
	m.adauga(3, 300);
	m.adauga(1, 500);
	m.adauga(2, 600);
	m.adauga(4, 800);
	assert(m.dim() == 6);

	assert(m.sterge(5, 600) == false);
	assert(m.sterge(1, 500) == true);

	assert(m.dim() == 5);

    vector<TValoare> v;
	v=m.cauta(6);
	assert(v.size()==0);

	v=m.cauta(1);
	assert(v.size()==1);

	assert(m.vid() == false);
	IteratorMD im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.element();
		im.urmator();
	}
	assert(im.valid() == false);
	im.prim();
	assert(im.valid() == true);
}
