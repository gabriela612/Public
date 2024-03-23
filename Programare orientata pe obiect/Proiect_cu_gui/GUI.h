#pragma once
#include <qwidget.h>
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
#include <iterator>
#include <iostream>
#include <qformlayout.h>
#include <qtableview>
#include "Service.h"
#include <qdebug.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qbrush.h>
#include <qdialog.h>
#include <qcolor.h>
#include "Lista.h"
#include "Obs.h"
#include <qpainter.h>




class GUI :public QWidget, Observer, Observable
{
public:
	GUI(Service& serv) : service{ serv } { init_gui(), init_connect(), load_data(); }
	void load_data(); // afisare
	void load_data_vector_param(vector<Activitate>v);
	Lista_de_activitati* cos;
	//vector<Cos_GUI*>lista_cosuri;

	void update() override;

private:
	Service& service;
	QHBoxLayout* main_ly = new QHBoxLayout(); // layout-ul ce contine tot
	QVBoxLayout* stanga_ly = new QVBoxLayout(); // layout-ul pentru partea stanga
	QListWidget* act_qlist = new QListWidget; // lista de activitati
	QHBoxLayout* sortare_ly = new QHBoxLayout(); // layout-ul pentru sortare
	QPushButton* btn_sort1 = new QPushButton("&Sortarea dupa titlu"); // butonul pentru sortare 1
	QPushButton* btn_sort2 = new QPushButton("&Sortarea dupa tip si durata"); // butonul pentru sortare 2
	QLineEdit* in_filtrare = new QLineEdit(); // caseta de introducere a textului pentru filtrare
	QHBoxLayout* filtrare_ly = new QHBoxLayout(); // layout-ul pentru filtrare
	QPushButton* btn_filt1 = new QPushButton("&Filtrare dupa descriere"); // butonul pentru filtrare 1
	QPushButton* btn_filt2 = new QPushButton("&Filtrare dupa tip"); // butonul pentru filtrare 2
	QVBoxLayout* dreapta_ly = new QVBoxLayout(); // layout-ul pentru partea dreapta
	QLineEdit* in_id = new QLineEdit(); // caseta de input pentru id
	QLineEdit* in_titlu = new QLineEdit(); // caseta de input pentru titlu
	QLineEdit* in_descriere = new QLineEdit(); // caseta de input pentru descriere
	QLineEdit* in_tip = new QLineEdit(); // caseta de input pentru tip
	QLineEdit* in_durata = new QLineEdit(); // caseta de input pentru durata
	QFormLayout* input_ly = new QFormLayout; // layout-ul pentru introducerea datelor
	QPushButton* btn_adauga = new QPushButton("&Adauga"); // butonul pentru adaugare
	QHBoxLayout* modifica_sterge_ly = new QHBoxLayout(); // layout-ul pentru stergere si modificare
	QPushButton* btn_sterge = new QPushButton("&Sterge"); // butonul pentru stergere
	QPushButton* btn_modifica = new QPushButton("&Modifica"); // butonul pentru modificare
	QPushButton* btn_undo = new QPushButton("&Undo"); // butonul pentru undo
	string text_filtrare1;
	string text_filtrare2;
	QPushButton* btn_cos = new QPushButton("&Creeare cos");

	void init_gui();
	void init_connect();
	void connect_adauga();
	void connect_sterge();
	void connect_modifica();
	void connect_sortare_titlu();
	void connect_sortare_tip_durata();
	void connect_selectie();
	void connect_filtrare_descriere();
	void connect_filtrare_tip();
	void filtrare_descriere();
	void filtrare_tip();
	void connect_undo();
	void connect_cos();
};

class Cos_GUI :public QWidget, Observer, Observable
{
private:
	Lista_de_activitati* cos;
	QListWidget* copie_act = new QListWidget;
	QListWidget* cos_qlist = new QListWidget;
	Service* service_mare = nullptr;
	GUI* gui;

	QHBoxLayout* main_ly = new QHBoxLayout;
	QVBoxLayout* stanga_ly = new QVBoxLayout;
	QPushButton* btn_ad_cos = new QPushButton("&Adauga la lista");
	QFormLayout* st_cos_ly = new QFormLayout;
	//QLineEdit* in_ad_cos = new QLineEdit;
	QPushButton* btn_gen_cos = new QPushButton("&Genereaza activitati in lista : ");
	QLineEdit* in_gen_cos = new QLineEdit;

	QVBoxLayout* mijloc_ly = new QVBoxLayout;
	QVBoxLayout* mijloc_ly_text = new QVBoxLayout;
	QVBoxLayout* mijloc_ly_de_sters = new QVBoxLayout;
	QLabel* id_la = new QLabel("id: ");
	QLabel* titlu_la = new QLabel("titlu: ");
	QLabel* descriere_la = new QLabel("descriere:       ");
	QLabel* tip_la = new QLabel("tip: ");
	QLabel* durata_la = new QLabel("durata: ");

	QVBoxLayout* dreapta_ly = new QVBoxLayout;
	QPushButton* btn_gol_cos = new QPushButton("&Goleste lista");
	QFormLayout* dr_cos_ly = new QFormLayout;
	QPushButton* btn_exp_cos = new QPushButton("&Exporta : ");
	QLineEdit* in_exp_cos = new QLineEdit;

	QVBoxLayout* final_ly = new QVBoxLayout;
	QVBoxLayout* final_ly_text = new QVBoxLayout;
	QVBoxLayout* final_ly_de_sters = new QVBoxLayout;
	QLabel* id_la_fi = new QLabel("id: ");
	QLabel* titlu_la_fi = new QLabel("titlu: ");
	QLabel* descriere_la_fi = new QLabel("descriere:       ");
	QLabel* tip_la_fi = new QLabel("tip: ");
	QLabel* durata_la_fi = new QLabel("durata: ");

public:
	Cos_GUI(Service* service, Lista_de_activitati * _cos, GUI* _gui);
	void init_Cos_GUI(Service* service);
	void luare_lista(Service* service);
	void load_cos();
	void init_connect();
	void connect_adaugare();
	void connect_generare();
	void connect_golire();
	void connect_export();
	void connect_selecteaza();
	void connect_selecteaza2();
	void update()
	{
		//QMessageBox::information(nullptr, "ceva", "ceva");
		luare_lista(this->service_mare);
		load_cos();
	}
};


class PaintGUI : public QWidget, Observer, QPainter
{
private:
	Lista_de_activitati* cos;
	QHBoxLayout* ly = new QHBoxLayout;
	QListWidget* qlista_cos = new QListWidget;
public:
	PaintGUI(Lista_de_activitati* _cos);
	void paintEvent(QPaintEvent*) override;
	void update() override
	{
		repaint();
	}
};


