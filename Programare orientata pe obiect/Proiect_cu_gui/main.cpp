#include <QApplication>
#include <QLabel>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qlayoutitem.h>
#include <qboxlayout.h>
#include <qtextedit.h>
#include <qline.h>
#include <qtextformat.h>
#include <qlistwidget.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <qformlayout.h>
#include <qtableview>
#include "GUI.h"
#include <QSpinBox>


using namespace std;



int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Activitate act;
    act.teste_domain();
    act.~Activitate();
    Repo repo;
    repo.teste_repo();
    Service service(repo);
    service.teste_service();

    GUI *g = new GUI(service);
    g->show();
    a.exec();

    service.distruge_service();
}

