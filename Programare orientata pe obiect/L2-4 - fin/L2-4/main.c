#include <stdio.h>
#include "Service.c"
#include "UI.c"
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

int main()
{
	TesteD();
	TesteR();
	TesteS();
	TesteL();
	OferteS ofertes;
	CreareListaGoalaServ(&ofertes);
	AdaugareServ(&ofertes, "munte", 10, "12.01.2021", "trqw");
	AdaugareServ(&ofertes, "munte", 12, "12.01.2021", "qytdqs");
	AdaugareServ(&ofertes, "munte", 13, "12.01.2021", "af4iu3h");
	AdaugareServ(&ofertes, "city_break", 10, "12.01.2021", "mcorey");
	AdaugareServ(&ofertes, "munte", 12, "12.01.2021", "wdsxc");
	AdaugareServ(&ofertes, "munte", 13, "12.01.2021", "mvopf");
	AdaugareServ(&ofertes, "munte", 15, "12.01.2021", "sqts");

	Inceput(&ofertes);
	DistrugereListaServ(&ofertes);

	_CrtDumpMemoryLeaks();
	
	printf("\nGoodbye!\n");

}
