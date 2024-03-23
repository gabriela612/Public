#include "Repo.h"

void CreareListaGoala(Oferte* oferte, int cap)
{
	oferte->cap = cap;
	oferte->elem = (Oferta**)malloc(oferte->cap * sizeof(Oferta*));
	oferte->lg = 0;
}

void DistrugereLista(Oferte* oferte)
{
	free(oferte->elem);
}

void Adaugare(Oferte* oferte, Oferta* of)
{
	oferte->lg++;
	oferte->elem[oferte->lg] = of;
}


void Stergere(Oferte* oferte, int poz)
{
	if (poz == oferte->lg)
	{
		free(oferte->elem[poz]);
		oferte->elem[poz] = NULL;
		oferte->lg--;
		return;
	}
	Oferta* ofdesters;
	Oferta* ultimaof;
	ofdesters = GetOfertaPoz2(oferte, poz);
	free(ofdesters);
	ultimaof = GetOfertaPoz2(oferte, oferte->lg);
	oferte->elem[poz] = ultimaof;
	oferte->elem[oferte->lg] = NULL;
	oferte->lg--;
}

void GetOfertaPoz(Oferte* oferte, Oferta* of, int poz)
{
	if (poz > oferte->lg)
	{
		of = NULL;
		return;
	}
	if (poz < 1)
	{
		of = NULL;
		return;
	}
	*of = *oferte->elem[poz];
}

int CautaOferta(Oferte oferte, Oferta of)
{
	for (int i = 1; i <= oferte.lg; i++)
	{
		if (Egal(*oferte.elem[i], of))
			return i;
	}
	return -1;
}

Oferta* GetOfertaPoz2(Oferte* oferte, int poz)
{
	if (poz > oferte->lg)
	{
		//of = NULL;
		return NULL;
	}
	if (poz < 1)
	{
		//of = NULL;
		return NULL;
	}
	return oferte->elem[poz];
}

void DistrugereOferte(Oferte* oferte)
{
	for (int i = 1; i <= oferte->lg; i++)
	{
		Oferta* of;
		of = GetOfertaPoz2(oferte, i);
		free(of);
	}
	free(oferte->elem);
	free(oferte);
}

void CopiereLista(Oferte* sursa, Oferte* dest)
{
	for (int i = 1; i <= sursa->lg; i++)
	{
		dest->elem[i] = sursa->elem[i];
	}
}

void Interschimba(int poz1, int poz2, Oferte* oferte)
{
	Oferta* aux;
	aux = oferte->elem[poz1];
	oferte->elem[poz1] = oferte->elem[poz2];
	oferte->elem[poz2] = aux;
}

Oferte * DeepCopyRepo(Oferte* reposursa)
{
	Oferte * repodest = (Oferte*)malloc(sizeof(Oferte));
	CreareListaGoala(repodest, reposursa->cap);
	Oferta* of=NULL;
	for (int i = 1; i <= reposursa->lg; i++)
	{
		of = DeepCopyOferta(reposursa->elem[i]);
		Adaugare(repodest, of);
	}
	return repodest;
}

void TesteR()
{
	Oferte oferte;
	Oferta* oferta;
	Oferta of;
	oferta = (Oferta*)malloc(sizeof(Oferta));
	CreareListaGoala(&oferte, 5);
	CreareOferta(oferta, 1, 100, "11.01.2001", "Romania");
	Adaugare(&oferte, oferta);

	assert(CautaOferta(oferte, *oferta) == 1);
	GetOfertaPoz(&oferte, &of, 1);
	assert(Egal(of, *oferta));
	GetOfertaPoz(&oferte, &of, 5);
	GetOfertaPoz(&oferte, &of, -10);
	SetPret(&of, 1);
	assert(CautaOferta(oferte, of) == -1);
	SetPret(&of, 100);
	Stergere(&oferte, 1);
	assert(CautaOferta(oferte, of) == -1);
	assert(GetOfertaPoz2(&oferte, -1) == NULL);
	assert(GetOfertaPoz2(&oferte, 100) == NULL);
	Oferta *ofert = NULL;
	GetOfertaPoz(&oferte, ofert, -1);
	assert(ofert == NULL);
	GetOfertaPoz(&oferte, ofert, 100);
	assert(ofert == NULL);

	free(oferte.elem);
}



