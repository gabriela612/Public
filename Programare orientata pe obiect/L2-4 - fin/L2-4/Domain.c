#include "Domain.h"


void CreareOferta(Oferta* of, int tip, int pret, char* data, char * dest)
{
	SetTip(of, tip);
	SetPret(of, pret);
	SetData(of, data);
	SetDest(of, dest);
}

void GetDest(Oferta of, char* dest)
{
	strcpy_s(dest, 20, of.dest);
}

void SetDest(Oferta* of, char* dest)
{
	strcpy_s(of->dest, 20, dest);
}

int GetTip(Oferta of)
{
	return of.tip;
}

void GetNumeTip(Oferta of, char* tip)
{
	int t = GetTip(of);
	switch (t)
	{
	case 1:
		strcpy_s(tip, 10 * sizeof(char), "munte\0");
		break;
	case 2:
		strcpy_s(tip, 10 * sizeof(char), "mare\0");
		break;
	case 3:
		strcpy_s(tip, 15 * sizeof(char), "city_break\0");
		break;
	}
}

int GetPret(Oferta of)
{
	return of.pret;
}

void GetData(Oferta of, char* data)
{
	strcpy_s(data, 20, of.data);
}

void SetTip(Oferta* of, int tip)
{
	of->tip = tip;
}

void SetPret(Oferta* of, int pret)
{
	of->pret = pret;
}

void SetData(Oferta* of, char* data)
{
	strcpy_s(of->data, 20, data);
}

int Egal(Oferta of1, Oferta of2)
{
	char data1[20], data2[20], dest1[20], dest2[20];
	if (GetTip(of1) != GetTip(of2))
		return 0;
	if (GetPret(of1) != GetPret(of2))
		return 0;
	GetData(of1, data1);
	GetData(of2, data2);
	if (strcmp(data1, data2) != 0)
		return 0;
	GetDest(of1, dest1);
	GetDest(of2, dest2);
	if (strcmp(dest1, dest2) != 0)
		return 0;
	return 1;

}

int Validare(char* tip, int pret, char* data, char * dest)
{
	if (strcmp(tip, "munte") != 0 && strcmp(tip, "mare") != 0 && strcmp(tip, "city_break") != 0)
		return 1;
	if (pret < 0)
		return 2;
	if (data[0] < '3' && (data[3] == '0' || (data[3] == '1' && data[4] < '3')) && data[2] == '.' && data[5] == '.')
		return 0;
	else
		return 3;
}

int TransformareTip(char* tip)
{
	if (strcmp("munte", tip) == 0)
		return 1;
	if (strcmp("mare", tip) == 0)
		return 2;
	return 3;
}

Oferta* DeepCopyOferta(Oferta *ofsursa)
{
	Oferta* ofdest = (Oferta*)malloc(sizeof(Oferta));
	ofdest->tip = GetTip(*ofsursa);
	ofdest->pret = GetPret(*ofsursa);
	GetData(*ofsursa, ofdest->data);
	GetDest(*ofsursa, ofdest->dest);
	return ofdest;
}

void TesteDeepCopyOferta()
{
	Oferta of1;
	Oferta* of2;
	CreareOferta(&of1, 1, 100, "25.03.2023", "Romania");
	of2 = DeepCopyOferta(&of1);
	assert(GetTip(*of2) == 1);
	assert(GetPret(*of2) == 100);
	char data[20], dest[20];
	GetData(*of2, data);
	GetDest(*of2, dest);
	assert(strcmp(data, "25.03.2023") == 0);
	assert(strcmp(dest, "Romania") == 0);
	assert(Egal(of1, *of2) == 1);

	free(of2);
}

void TesteD()
{
	Oferta of;
	CreareOferta(&of, 1, 100, "12.01.2021\0", "Romania");
	assert(GetTip(of) == 1);
	assert(GetPret(of) == 100);
	char data[20];
	GetData(of, data);
	assert(strcmp(data, "12.01.2021\0") == 0);
	SetTip(&of, 2);
	assert(GetTip(of) == 2);
	SetPret(&of, 200);
	assert(GetPret(of) == 200);
	SetData(&of, "01.01.2001\0");
	GetData(of, data);
	assert(strcmp(data, "01.01.2001\0") == 0);
	Oferta of2;
	CreareOferta(&of2, 2, 200, "01.01.2001\0", "Romania");
	assert(Egal(of, of2) == 1);
	SetTip(&of, 1);
	assert(Egal(of, of2) == 0);
	char tip[15];
	GetNumeTip(of, tip);
	assert(strcmp(tip, "munte\0") == 0);
	SetTip(&of, 2);
	GetNumeTip(of, tip);
	assert(strcmp(tip, "mare\0") == 0);
	SetTip(&of, 3);
	GetNumeTip(of, tip);
	assert(strcmp(tip, "city_break\0") == 0);
	assert(Validare("mnte", 200, "12.01.2021", "Romania") == 1);
	assert(Validare("munte", -1, "12.01.2021", "Romania") == 2);
	assert(Validare("munte", 100, "12.13.2021", "Romania") == 3);
	assert(Validare("munte", 100, "30.02.2021", "Romania") == 3);
	assert(Validare("munte", 100, "2.11.2021", "Romania") == 3);
	char dest[20];
	GetDest(of, dest);
	assert(strcmp(dest, "Romania") == 0);
	Oferta ofert1, ofert2;
	CreareOferta(&ofert1, 1, 12, "12.01.2021", "Roma");
	CreareOferta(&ofert2, 1, 12, "12.01.2021", "Romania");
	assert(Egal(ofert1, ofert2) == 0);

	TesteDeepCopyOferta();
}




