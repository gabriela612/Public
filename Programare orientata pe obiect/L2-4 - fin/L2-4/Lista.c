#include "Lista.h"

Li * CreareListaGen(int cap)
{
	Li* li;
	li = (Li*)malloc(sizeof(Li));
	li->cap = cap;
	li->lg = 0;
	li->elem = (void**)malloc(sizeof(void*) * cap);
	return li;
}

void DistrugeListaGen(Li* li)
{
	free(li->elem);
	free(li);
}

void AdaugaListaGen(Li* li, void* el)
{
	li->lg++;
	li->elem[li->lg] = el;
	if (TestareRedimListaGen(li))
		RedimListaGen(li);
}

int TestareRedimListaGen(Li* li)
{
	if (li->lg == li->cap - 1)
		return 1;
	return 0;
}

void RedimListaGen(Li* li)
{
	li->cap = li->cap * 2;
	void** celem;
	celem = (void**)malloc(sizeof(void*) * li->cap);
	for (int i = 1; i <= li->lg; i++)
		celem[i] = li->elem[i];
	free(li->elem);
	li->elem = celem;
}

void * GetStergeUltimulElemGen(Li* li)
{
	void * ultim = li->elem[li->lg];
	li->lg--;
	return ultim;
}

void TesteL()
{
	// Creeare
	Li* li = CreareListaGen(5);
	assert(li->cap == 5);
	assert(li->lg == 0);

	// Adaugare
	AdaugaListaGen(li, "a");
	assert(strcmp(li->elem[1], "a") == 0);
	assert(li->lg == 1);
	int b = 7;
	AdaugaListaGen(li, &b);
	assert(li->elem[2] == &b);
	assert(li->lg == 2);

	// Redimensionare
	AdaugaListaGen(li, "b");
	AdaugaListaGen(li, "c");
	AdaugaListaGen(li, "d");
	AdaugaListaGen(li, "e");
	AdaugaListaGen(li, "f");
	assert(strcmp(li->elem[1], "a") == 0);
	assert(li->elem[2] == &b);
	assert(strcmp(li->elem[3], "b") == 0);
	assert(strcmp(li->elem[4], "c") == 0);
	assert(strcmp(li->elem[5], "d") == 0);
	assert(strcmp(li->elem[6], "e") == 0);
	assert(strcmp(li->elem[7], "f") == 0);
	assert(li->lg == 7);
	assert(li->cap == 10);

	// GetStergeUltimulElemGen
	char* el;
	el = GetStergeUltimulElemGen(li);
	assert(li->lg == 6);
	assert(strcmp(el, "f") == 0);

	DistrugeListaGen(li);
}