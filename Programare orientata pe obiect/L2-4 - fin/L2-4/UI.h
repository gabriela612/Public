#pragma once
#include <stdio.h>
#include "Service.h"
#include "Lista.h"

void AfisareMeniu();
// in acesta functie afisam meniul

int CitireCerinta();
// in acesta functie citi si returnam cerinta (de tip int)

void ApelareCerinta(int cer, OferteS* ofertes);
// in acesta functie apelam cerinta de pe pozitia cer, avand ca parametru un obiect de tip OferteS

void Inceput(OferteS* ofertes);

void AdaugareUI(OferteS* ofertes);
// in acesta functie citim si adaugam o noua oferta la lista de oferte, avand ca parametru un obiect de tip OferteS

void StergereIU(OferteS* ofertes);
// in acesta functie citim si stergem o oferta din lista de oferte, avand ca parametru un obiect de tip OferteS

void ActualizareIU(OferteS* ofertes);
// in acesta functie citim si modificam o oferta din lista de oferte, avand ca parametru un obiect de tip OferteS

void AfisareOferte(OferteS* ofertes);
// in acesta functie afisam ofertele din lista de oferte, avand ca parametru un obiect de tip OferteS

void SortarePretDestinatieUI(OferteS* ser);
// in acesta functie sortam si afisam ofertele din lista de oferte, avand ca parametru un obiect de tip OferteS

void FiltrareUI(OferteS* ser);
// in acesta functie filtram si afisam ofertele din lista de oferte, avand ca parametru un obiect de tip OferteS

void UndoUI(OferteS* ser);


