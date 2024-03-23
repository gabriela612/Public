#include <iostream>
#include <assert.h>
#include "Service.h"
//#include "UI.h"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

using namespace std;

void INC()
{
    Activitate act;
    act.teste_domain();
    act.~Activitate();
    Repo repo;
    repo.teste_repo();
    Service service(repo);
    service.teste_service();
    //UI ui(service);
    //ui.inceput();
    service.distruge_service();
    _CrtDumpMemoryLeaks();
}





















/*
char titlu[10] = "ceva", desc[10] = "ceva", tip[10] = "ceva";
Activitate act;
act.creare_activitate(titlu, desc, tip, 20, 1);
cout << act.get_durata();
Repo re;
assert(re.repo_vid() == 1);
re.adaugare_repo(act);
Activitate act2;
re.get_activitate_poz_repo(&act2, 0);
cout << "#" << act2.get_durata() << "#";
cout << re.cautare_pozitie_activitate_repo(act2);
cout << re.cautare_pozitie_id_repo(1);
cout << "Hello World!\n";
*/
