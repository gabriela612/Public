#include "GUI.h"

void GUI::init_gui()
{
    /*qDebug() << "ceva";
    QMessageBox::information(nullptr, "titlu", "text");*/

    this->cos = new Lista_de_activitati(*new Repo);

    // setare apasare butoane de filtrare
    text_filtrare1 = "";
    text_filtrare2 = "";

    setLayout(main_ly);

    // adaugarea partii din stanga la layout-ul mare
    main_ly->addLayout(stanga_ly);

    // adaugarea listei de activitati in partea stanga
    stanga_ly->addWidget(act_qlist);

    // adaugarea layout-ului pentru sortarea la partea din stanga
    stanga_ly->addLayout(sortare_ly);

    // adaugarea butoanelor la layout-ul de sortare
    sortare_ly->addWidget(btn_sort1);
    sortare_ly->addWidget(btn_sort2);

    // adaugarea casetei de filtrare la layout-ul din stanga
    stanga_ly->addWidget(in_filtrare);

    // adaugarea layout-ului pentru filtrare la partea din stanga
    stanga_ly->addLayout(filtrare_ly);

    // adaugarea butoanelor la layout-ul de filtrare
    filtrare_ly->addWidget(btn_filt1);
    filtrare_ly->addWidget(btn_filt2);



    // adaugarea partii din dreapta la layout-ul mare
    main_ly->addLayout(dreapta_ly);
    dreapta_ly->addStretch();

    // adaugarea textului si casetelor la layou-ul pentru introducerea datelor

    input_ly->addRow("id:", in_id);
    input_ly->addRow("titlu:", in_titlu);
    input_ly->addRow("descriere:", in_descriere);
    input_ly->addRow("tip:", in_tip);
    input_ly->addRow("durata:", in_durata);

    // adaugarea layout-ului pentru introducerea datelor la layout-ul din dreapta
    dreapta_ly->addLayout(input_ly);
    //dreapta_ly->addStretch();


    // adaugarea butonului de adaugarea la layout-ul din dreapta
    dreapta_ly->addWidget(btn_adauga);

    // adaugarea layout-ului pentru stergere si modificare la layout-ul din dreapta
    dreapta_ly->addLayout(modifica_sterge_ly);

    // adaugarea butoanelor de stergere si modificare la layout-ul pentru stergere si modificare
    modifica_sterge_ly->addWidget(btn_sterge);
    modifica_sterge_ly->addWidget(btn_modifica);

    // adaugarea butonului de undo la layout-ul din dreapta
    dreapta_ly->addWidget(btn_undo);

    // adaugarea butonului de creeare cos la layout-ul din dreapta
    dreapta_ly->addWidget(btn_cos);


    dreapta_ly->addStretch();

}

void GUI::load_data()
{


    /*QPainter p{ this };
    p.drawEllipse(QPointF(20, 20), 20, 20);*/


    act_qlist->clear();

    vector<Activitate>v;
    this->service.get_all_service(&v);

    //act_qlist->addItem(QString::fromStdString("ID    Titlu                            Descriere                                   Tip          Durata"));
    //act_qlist->setGridSize(QSize());
    act_qlist->setItemAlignment(Qt::AlignLeft);
    for (auto& i : v)
    {
        string titlu;
        i.get_titlu(&titlu);
        QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(titlu));
        it->setData(Qt::UserRole, QString::fromStdString(to_string(i.get_id())));
        act_qlist->addItem(it);
    }
    act_qlist->addItem("adauga_activitate");
    v.~vector();
}

void GUI::load_data_vector_param(vector<Activitate> v)
{
    act_qlist->clear();

    //act_qlist->addItem("ID   Titlu                            Descriere                                   Tip          Durata");
    for (auto& i : v)
    {
        string titlu;
        i.get_titlu(&titlu);
        QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(titlu));
        it->setData(Qt::UserRole, QString::fromStdString(to_string(i.get_id())));
        act_qlist->addItem(it);
    }
    act_qlist->addItem("adauga_activitate");
}

void GUI::update()
{
    /*{
        for (int i = 0; i < this->lista_cosuri.size(); i++)
        {
            this->lista_cosuri[i]->update();
        }
    }*/
    this->notifica();
}

void GUI::init_connect()
{
    connect_adauga();
    connect_sterge();
    connect_modifica();
    connect_sortare_titlu();
    connect_sortare_tip_durata();
    connect_selectie();
    connect_filtrare_descriere();
    connect_filtrare_tip();
    connect_undo();
    connect_cos();
}

void GUI::connect_adauga()
{
    QObject::connect(btn_adauga, &QPushButton::clicked, [&]() {

        string titlu, descriere, tip, durata;
        titlu = QString(in_titlu->text()).toStdString();
        descriere = QString(in_descriere->text()).toStdString();
        tip = QString(in_tip->text()).toStdString();
        durata = QString(in_durata->text()).toStdString();

        int dur, p;
        dur = 0;
        p = 1;
        for (auto& i : durata)
        {
            if (i < '0' or i > '9')
            {
                QMessageBox::warning(nullptr, "Input gresit!", "Durata trebuie sa fie un numar natural.");
                durata.~basic_string();
                titlu.~basic_string();
                descriere.~basic_string();
                tip.~basic_string();
                return;
            }
            else
            {
                dur = dur * 10 + (int)(i - '0');
                p *= 10;
            }
        }
        if (titlu == "" or descriere == "" or tip == "" or durata == "")
        {
            QMessageBox::warning(nullptr, "Input insuficient!", "Pentru adaugare trebuie sa introduceti titlul, descrierea, tipul si durata activitatii.");
            durata.~basic_string();
            titlu.~basic_string();
            descriere.~basic_string();
            tip.~basic_string();
            return;
        }
        try
        {
            this->service.adaugare_service(&titlu, &descriere, &tip, dur);
            QMessageBox::information(nullptr, "Vesti bune", "Adaugarea a fost efectuata cu succes!");
        }
        catch (ServiceEx er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er.mesaj));
        }
        durata.~basic_string();
        titlu.~basic_string();
        descriere.~basic_string();
        tip.~basic_string();
        if (text_filtrare1 != "")
        {
            filtrare_descriere();
        }
        if (text_filtrare2 != "")
        {
            filtrare_tip();
        }
        if (text_filtrare1 == "" and text_filtrare2 == "")
            load_data();

        });
}

void GUI::connect_sterge()
{
    QObject::connect(btn_sterge, &QPushButton::clicked, [&]() {

        string id = QString(in_id->text()).toStdString();
        if (id == "")
        {
            QMessageBox::warning(nullptr, "Input insuficient!", "Trebuie sa introduceti id-ul activitatii pe care doriti sa o stergeti.");
            id.~basic_string();
            return;
        }
        int iid = 0;
        int p = 1;
        for (auto& i : id)
        {
            if (i < '0' or i > '9')
            {
                QMessageBox::warning(nullptr, "Input gresit!", "Id-ul trebuie sa fie un numar natural.");
                id.~basic_string();
                return;
            }
            else
            {
                iid = iid * 10 + (int)(i - '0');
                p *= 10;
            }
        }
        try
        {
            this->service.stergere_service(iid);
            QMessageBox::information(nullptr, "Vesti bune", "Stergerea a fost efectuata cu succes!");
        }
        catch (ServiceEx er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er.mesaj));
        }
        id.~basic_string();
        
        if (text_filtrare1 != "")
        {
            filtrare_descriere();
        }
        if (text_filtrare2 != "")
        {
            filtrare_tip();
        }
        if (text_filtrare1 == "" and text_filtrare2 == "")
            load_data();
    });
}

void GUI::connect_modifica()
{

    QObject::connect(btn_modifica, &QPushButton::clicked, [&]() {

        string titlu, descriere, tip, durata;
        titlu = QString(in_titlu->text()).toStdString();
        descriere = QString(in_descriere->text()).toStdString();
        tip = QString(in_tip->text()).toStdString();
        durata = QString(in_durata->text()).toStdString();

        int dur, p;
        dur = 0;
        p = 1;
        for (auto& i : durata)
        {
            if (i < '0' or i > '9')
            {
                QMessageBox::warning(nullptr, "Input gresit!", "Durata trebuie sa fie un numar natural.");
                durata.~basic_string();
                titlu.~basic_string();
                descriere.~basic_string();
                tip.~basic_string();
                return;
            }
            else
            {
                dur = dur * 10 + (int)(i - '0');
                p *= 10;
            }
        }
        string id = QString(in_id->text()).toStdString();
        if (titlu == "" or descriere == "" or tip == "" or durata == "" or id == "")
            if (id == "")
            {
                QMessageBox::warning(nullptr, "Input insuficient!", "Pentru modificare trebuie sa introduceti id-ul, titlul, descrierea, tipul si durata activitatii pe care vreti sa le aiba activitatea cu id-ul dat.");
                durata.~basic_string();
                titlu.~basic_string();
                descriere.~basic_string();
                tip.~basic_string();
                id.~basic_string();
                return;
            }
        int iid = 0;
        p = 1;
        for (auto& i : id)
        {
            if (i < '0' or i > '9')
            {
                QMessageBox::warning(nullptr, "Input gresit!", "Id-ul trebuie sa fie un numar natural.");
                id.~basic_string();
                durata.~basic_string();
                titlu.~basic_string();
                descriere.~basic_string();
                tip.~basic_string();
                return;
            }
            else
            {
                iid = iid * 10 + (int)(i - '0');
                p *= 10;
            }
        }
        try
        {
            this->service.modificare_service(iid, &titlu, &descriere, &tip, dur);
            QMessageBox::information(nullptr, "Vesti bune", "Modificarea a fost efectuata cu succes!");
        }
        catch (ServiceEx er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er.mesaj));
        }
        id.~basic_string();
        durata.~basic_string();
        titlu.~basic_string();
        descriere.~basic_string();
        tip.~basic_string();

        if (text_filtrare1 != "")
        {
            filtrare_descriere();
        }
        if (text_filtrare2 != "")
        {
            filtrare_tip();
        }
        if (text_filtrare1 == "" and text_filtrare2 == "")
            load_data();
    });
}

void GUI::connect_sortare_titlu()
{

    QObject::connect(btn_sort1, &QPushButton::clicked, [&]() {

        vector<Activitate>v;
        try
        {
            this->service.sortare_titlu(&v);
        }
        catch (ServiceEx er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er.mesaj));
        }

        if (text_filtrare1 != "")
        {
            vector<Activitate>rez;
            copy_if(v.begin(), v.end(), back_inserter(rez), [this](Activitate a) {return descriere_egala(a, &text_filtrare1); });
            load_data_vector_param(rez);
            rez.~vector();
            v.~vector();
            return;
        }
        if (text_filtrare2 != "")
        {
            vector<Activitate>rez;
            copy_if(v.begin(), v.end(), back_inserter(rez), [this](Activitate a) {return tip_egal(a, &text_filtrare2); });
            load_data_vector_param(rez);
            rez.~vector();
            v.~vector();
            return;
        }
        load_data_vector_param(v);
        v.~vector();
    });
}

void GUI::connect_sortare_tip_durata()
{

    QObject::connect(btn_sort2, &QPushButton::clicked, [&]() {

        vector<Activitate>v;
        try
        {
            this->service.sortare_tip_durata(&v);
        }
        catch (ServiceEx er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er.mesaj));
        }

        if (text_filtrare1 != "")
        {
            vector<Activitate>rez;
            copy_if(v.begin(), v.end(), back_inserter(rez), [this](Activitate a) {return descriere_egala(a, &text_filtrare1); });
            load_data_vector_param(rez);
            rez.~vector();
            v.~vector();
            return;
        }
        if (text_filtrare2 != "")
        {
            vector<Activitate>rez;
            copy_if(v.begin(), v.end(), back_inserter(rez), [this](Activitate a) {return tip_egal(a, &text_filtrare2); });
            load_data_vector_param(rez);
            rez.~vector();
            v.~vector();
            return;
        }
        load_data_vector_param(v);
        v.~vector();
    });
}

void GUI::connect_selectie()
{
    QObject::connect(act_qlist, &QListWidget::itemSelectionChanged, [&]() {
        if (act_qlist->selectedItems().isEmpty())
        {
            in_id->setText("");
            in_titlu->setText("");
            in_descriere->setText("");
            in_tip->setText("");
            in_durata->setText("");
            return;
        }
    string text = act_qlist->selectedItems().at(0)->text().toStdString();
    if (text.find("id") != string::npos or text.find("adauga_activitate") != string::npos)
    {
        in_id->setText("");
        in_titlu->setText("");
        in_descriere->setText("");
        in_tip->setText("");
        in_durata->setText("");
        return;
    }

    QString data_asociata = act_qlist->selectedItems().at(0)->data(Qt::UserRole).toString();
    int id = data_asociata.toInt();

    int poz = service.cautare_id_service(id);

    vector<Activitate>v;
    service.get_all_service(&v);
    string titlu, descriere, tip;
    v[poz].get_titlu(&titlu);
    v[poz].get_descriere(&descriere);
    v[poz].get_tip(&tip);
    in_id->setText(QString::number(id));
    in_titlu->setText(QString::fromStdString(titlu));
    in_descriere->setText(QString::fromStdString(descriere));
    in_tip->setText(QString::fromStdString(tip));
    in_durata->setText(QString::number(v[poz].get_durata()));

    v.~vector();

        });
}

void GUI::connect_filtrare_descriere()
{
    QObject::connect(btn_filt1, &QPushButton::clicked, [&]() {

        if (text_filtrare1 == "" and QString(in_filtrare->text()).isEmpty() == false)
        {
            if (text_filtrare2 != "")
            {
                QMessageBox::warning(nullptr, "Eroare", "Exita deja un alt filtru activ. Pentru a adauga acest filtru, trebuie sa stergeti filtrul existent.");
                return;
            }
            text_filtrare1 = QString(in_filtrare->text()).toStdString();
            filtrare_descriere();
            btn_filt1->setText("&Sterge filtrarea dupa descriere");
            in_filtrare->setDisabled(true);
        }
        else
        {
            if (text_filtrare1 == "" and QString(in_filtrare->text()).isEmpty() == true)
            {
                return;
            }
            btn_filt1->setText("&Filtrare dupa descriere");
            text_filtrare1 = "";
            load_data();
            in_filtrare->setDisabled(false);
        }
    });
}

void GUI::connect_filtrare_tip()
{
    QObject::connect(btn_filt2, &QPushButton::clicked, [&]() {

        if (text_filtrare2 == "" and QString(in_filtrare->text()).isEmpty() == false)
        {
            if (text_filtrare1 != "")
            {
                QMessageBox::warning(nullptr, "Eroare", "Exita deja un alt filtru activ. Pentru a adauga acest filtrul, trebuie sa stergeti filtru existent.");
                return;
            }
            text_filtrare2 = QString(in_filtrare->text()).toStdString();
            filtrare_tip();
            btn_filt2->setText("&Sterge filtrarea dupa tip");
            in_filtrare->setDisabled(true);
        }
        else
        {
            if (text_filtrare2 == "" and QString(in_filtrare->text()).isEmpty() == true)
            {
                return;
            }
            btn_filt2->setText("&Filtrare dupa tip");
            text_filtrare2 = "";
            load_data();
            in_filtrare->setDisabled(false);
        }

        });
}

void GUI::filtrare_descriere()
{
    vector<Activitate>v;
    try
    {
        this->service.filtrare_descriere(&v, &text_filtrare1);
    }
    catch (ServiceEx er)
    {

    }
    load_data_vector_param(v);
    v.~vector();
}

void GUI::filtrare_tip()
{
    vector<Activitate>v;
    try
    {
        this->service.filtrare_tip(&v, &text_filtrare2);
    }
    catch (ServiceEx er)
    {

    }
    load_data_vector_param(v);
    v.~vector();
}

void GUI::connect_undo()
{

    QObject::connect(btn_undo, &QPushButton::clicked, [&]() {
        try
        {
            this->service.undo_service();
            QMessageBox::information(nullptr, "Vesti bune", "Operatia de undo s-a efectuat cu succes");
        }
        catch (ServiceEx er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er.mesaj));
            return;
        }
        if (text_filtrare1 != "")
        {
            filtrare_descriere();
        }
        if (text_filtrare2 != "")
        {
            filtrare_tip();
        }
        if (text_filtrare1 == "" and text_filtrare2 == "")
            load_data();
        });
}

void GUI::connect_cos()
{
    QObject::connect(btn_cos, &QPushButton::clicked, [&]() {

        Cos_GUI* c = new Cos_GUI(&service, this->cos, this);
        PaintGUI* p = new PaintGUI(this->cos);
        //this->lista_cosuri.push_back(c);
        this->add_follower((Observer*)c);
        this->add_follower((Observer*)p);
        c->show();
        p->show();
    });
}

void Cos_GUI::luare_lista(Service* service)
{
    this->copie_act->clear();
    this->service_mare = service;
    vector<Activitate>v;
    service_mare->get_all_service(&v);

    //copie_act->addItem("ID   Titlu                            Descriere                                   Tip          Durata");
    
    for (auto& i : v)
    {
        string titlu;
        i.get_titlu(&titlu);
        QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(titlu));
        it->setData(Qt::UserRole, QString::fromStdString(to_string(i.get_id())));
        copie_act->addItem(it);
    }
    v.~vector();
}

void Cos_GUI::load_cos()
{

    cos_qlist->clear();

    vector<Activitate>v;
    cos->get_repo()->get_all_repo(&v);

    //cos_qlist->addItem("ID   Titlu                            Descriere                                   Tip          Durata");
    
    for (auto& i : v)
    {
        string titlu;
        i.get_titlu(&titlu);
        QListWidgetItem* it = new QListWidgetItem(QString::fromStdString(titlu));
        it->setData(Qt::UserRole, QString::fromStdString(to_string(i.get_id())));
        cos_qlist->addItem(it);
    }
    v.~vector();
}

void Cos_GUI::init_connect()
{
    connect_adaugare();
    connect_generare();
    connect_golire();
    connect_export();
    connect_selecteaza();
    connect_selecteaza2();
}

void Cos_GUI::connect_adaugare()
{
    QObject::connect(btn_ad_cos, &QPushButton::clicked, [&]() {
        if (copie_act->selectedItems().isEmpty())
        {
            QMessageBox::warning(nullptr, "Input insuficient!", "Trebuie sa selectati o activitate.");
            return;
        }
        string id = copie_act->selectedItems().at(0)->data(Qt::UserRole).toString().toStdString();
        int iid = 0;
        /*int p = 1;
        for (auto& i : id)
        {
            if (i < '0' or i > '9')
            {
                QMessageBox::warning(nullptr, "Input gresit!", "Id-ul trebuie sa fie un numar natural.");
                id.~basic_string();
                return;
            }
            else
            {
                iid = iid * 10 + (int)(i - '0');
                p *= 10;
            }
        }*/
        iid = stoi(id);
        qDebug() << id << "ceva ceva ceva";
        try
        {
            cos->adauga_lista(iid, service_mare);
        }
        catch (string er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er));
        }
        load_cos();
        this->gui->update();
    });
}

void Cos_GUI::connect_generare()
{

    QObject::connect(btn_gen_cos, &QPushButton::clicked, [&]() {

        string id = QString(in_gen_cos->text()).toStdString();
        if (id == "")
        {
            QMessageBox::warning(nullptr, "Input insuficient!", "Trebuie sa introduceti numarul activitatii.");
            id.~basic_string();
            return;
        }
        int iid = 0;
        int p = 1;
        for (auto& i : id)
        {
            if (i < '0' or i > '9')
            {
                QMessageBox::warning(nullptr, "Input gresit!", "Trebuie sa introduceti un numar natural.");
                id.~basic_string();
                return;
            }
            else
            {
                iid = iid * 10 + (int)(i - '0');
                p *= 10;
            }
        }
        try
        {
            cos->genereaza_lista(iid, service_mare);
        }
        catch (string er)
        {
            QMessageBox::warning(nullptr, "Eroare", QString::fromStdString(er));
        }
        catch (MaiPutine a)
        {
            QMessageBox::warning(nullptr, "Eroare", "S-au putut genera doar " + QString::number(a.nr) + " activitati.");
        }
        load_cos();
        this->gui->update();
    });
}

void Cos_GUI::connect_golire()
{

    QObject::connect(btn_gol_cos, &QPushButton::clicked, [&]() {
        cos->goleste_lista();
        load_cos();
        this->gui->update();
    });
}

void Cos_GUI::connect_export()
{
    QObject::connect(btn_exp_cos, &QPushButton::clicked, [&]() {
        if (in_exp_cos->text().isEmpty())
        {
            QMessageBox::warning(nullptr, "Input insuficient!", "Trebuie sa introduceti numele unui fisier.");
            return;
        }
        try
        {
            cos->exporta_lista(in_exp_cos->text().toStdString());
            QMessageBox::information(nullptr, "Vesti bune!", "S-a exportat cu succes.");
        }
        catch (exception ex)
        {
            QMessageBox::warning(nullptr, "Eroare", "Eroare necunoscuta.");
        }
    });
}

void Cos_GUI::connect_selecteaza()
{
    /*QObject::connect(copie_act, &QListWidget::itemSelectionChanged, [&]() {
        if (copie_act->selectedItems().isEmpty())
        {
            in_ad_cos->setText("");
            return;
        }
        string text = copie_act->selectedItems().at(0)->text().toStdString();
        if (text.find("id") != string::npos or text.find("adauga_activitate") != string::npos)
        {
            in_ad_cos->setText("");
            return;
        }

        QString data_asociata = copie_act->selectedItems().at(0)->data(Qt::UserRole).toString();
        in_ad_cos->setText(data_asociata);
    });*/


    QObject::connect(copie_act, &QListWidget::itemSelectionChanged, [&]() {
        if (copie_act->selectedItems().isEmpty())
        {

            id_la->setText("id: ");
            titlu_la->setText("titlu: ");
            descriere_la->setText("descriere:      ");
            tip_la->setText("tip: ");
            durata_la->setText("durata: ");

            mijloc_ly_de_sters->~QVBoxLayout();
            mijloc_ly_de_sters = new QVBoxLayout();
            mijloc_ly_text->addLayout(mijloc_ly_de_sters);
            mijloc_ly_de_sters->addWidget(id_la);
            mijloc_ly_de_sters->addWidget(titlu_la);
            mijloc_ly_de_sters->addWidget(descriere_la);
            mijloc_ly_de_sters->addWidget(tip_la);
            mijloc_ly_de_sters->addWidget(durata_la);

            return;
        }
        string text = copie_act->selectedItems().at(0)->text().toStdString();
        if (text.find("id") != string::npos or text.find("adauga_activitate") != string::npos)
        {
            id_la->setText("id: ");
            titlu_la->setText("titlu: ");
            descriere_la->setText("descriere:      ");
            tip_la->setText("tip: ");
            durata_la->setText("durata: ");

            mijloc_ly_de_sters->~QVBoxLayout();
            mijloc_ly_de_sters = new QVBoxLayout();
            mijloc_ly_text->addLayout(mijloc_ly_de_sters);
            mijloc_ly_de_sters->addWidget(id_la);
            mijloc_ly_de_sters->addWidget(titlu_la);
            mijloc_ly_de_sters->addWidget(descriere_la);
            mijloc_ly_de_sters->addWidget(tip_la);
            mijloc_ly_de_sters->addWidget(durata_la);

            return;
        }

        QString data_asociata = copie_act->selectedItems().at(0)->data(Qt::UserRole).toString();
        int id = data_asociata.toInt();

        int poz = service_mare->cautare_id_service(id);

        vector<Activitate>v;
        service_mare->get_all_service(&v);
        string titlu, descriere, tip;
        v[poz].get_titlu(&titlu);
        v[poz].get_descriere(&descriere);
        v[poz].get_tip(&tip);

        id_la->setText("id: " + QString::number(id));
        titlu_la->setText("titlu: " + QString::fromStdString(titlu));
        descriere_la->setText("descriere: " + QString::fromStdString(descriere));
        tip_la->setText("tip: " + QString::fromStdString(tip));
        durata_la->setText("durata: " + QString::number(v[poz].get_durata()));

        v.~vector();

        mijloc_ly_de_sters->~QVBoxLayout();
        mijloc_ly_de_sters = new QVBoxLayout();
        mijloc_ly_text->addLayout(mijloc_ly_de_sters);
        mijloc_ly_de_sters->addWidget(id_la);
        mijloc_ly_de_sters->addWidget(titlu_la);
        mijloc_ly_de_sters->addWidget(descriere_la);
        mijloc_ly_de_sters->addWidget(tip_la);
        mijloc_ly_de_sters->addWidget(durata_la);

        });
}

void Cos_GUI::connect_selecteaza2()
{
    QObject::connect(cos_qlist, &QListWidget::itemSelectionChanged, [&]() {
        if (cos_qlist->selectedItems().isEmpty())
        {

            id_la_fi->setText("id: ");
            titlu_la_fi->setText("titlu: ");
            descriere_la_fi->setText("descriere:      ");
            tip_la_fi->setText("tip: ");
            durata_la_fi->setText("durata: ");

            final_ly_de_sters->~QVBoxLayout();
            final_ly_de_sters = new QVBoxLayout();
            final_ly_text->addLayout(final_ly_de_sters);
            final_ly_de_sters->addWidget(id_la_fi);
            final_ly_de_sters->addWidget(titlu_la_fi);
            final_ly_de_sters->addWidget(descriere_la_fi);
            final_ly_de_sters->addWidget(tip_la_fi);
            final_ly_de_sters->addWidget(durata_la_fi);

            return;
        }
    string text = cos_qlist->selectedItems().at(0)->text().toStdString();
    if (text.find("id") != string::npos or text.find("adauga_activitate") != string::npos)
    {
        id_la_fi->setText("id: ");
        titlu_la_fi->setText("titlu: ");
        descriere_la_fi->setText("descriere:      ");
        tip_la_fi->setText("tip: ");
        durata_la_fi->setText("durata: ");

        final_ly_de_sters->~QVBoxLayout();
        final_ly_de_sters = new QVBoxLayout();
        final_ly_text->addLayout(final_ly_de_sters);
        final_ly_de_sters->addWidget(id_la_fi);
        final_ly_de_sters->addWidget(titlu_la_fi);
        final_ly_de_sters->addWidget(descriere_la_fi);
        final_ly_de_sters->addWidget(tip_la_fi);
        final_ly_de_sters->addWidget(durata_la_fi);

        return;
    }

    QString data_asociata = cos_qlist->selectedItems().at(0)->data(Qt::UserRole).toString();
    int id = data_asociata.toInt();

    int poz = cos->get_repo()->cautare_pozitie_id_repo(id);

    vector<Activitate>v;
    cos->get_repo()->get_all_repo(&v);
    string titlu, descriere, tip;
    v[poz].get_titlu(&titlu);
    v[poz].get_descriere(&descriere);
    v[poz].get_tip(&tip);

    id_la_fi->setText("id: " + QString::number(id));
    titlu_la_fi->setText("titlu: " + QString::fromStdString(titlu));
    descriere_la_fi->setText("descriere: " + QString::fromStdString(descriere));
    tip_la_fi->setText("tip: " + QString::fromStdString(tip));
    durata_la_fi->setText("durata: " + QString::number(v[poz].get_durata()));

    v.~vector();

    final_ly_de_sters->~QVBoxLayout();
    final_ly_de_sters = new QVBoxLayout();
    final_ly_text->addLayout(final_ly_de_sters);
    final_ly_de_sters->addWidget(id_la_fi);
    final_ly_de_sters->addWidget(titlu_la_fi);
    final_ly_de_sters->addWidget(descriere_la_fi);
    final_ly_de_sters->addWidget(tip_la_fi);
    final_ly_de_sters->addWidget(durata_la_fi);

        });
}

void Cos_GUI::init_Cos_GUI(Service* service)
{
    
    luare_lista(service);
    //cos_qlist->addItem("ID   Titlu                            Descriere                                   Tip          Durata");

    setLayout(main_ly);
    
    main_ly->addLayout(stanga_ly);
    main_ly->addLayout(mijloc_ly);
    main_ly->addLayout(dreapta_ly);
    main_ly->addLayout(final_ly);

    stanga_ly->addWidget(copie_act);

    stanga_ly->addLayout(st_cos_ly);

    //st_cos_ly->addRow(btn_ad_cos, in_ad_cos);
    st_cos_ly->addRow(btn_gen_cos, in_gen_cos);

    mijloc_ly->addLayout(mijloc_ly_text);
    mijloc_ly->addWidget(btn_ad_cos);
    mijloc_ly_text->addLayout(mijloc_ly_de_sters);
    mijloc_ly_de_sters->addWidget(id_la);
    mijloc_ly_de_sters->addWidget(titlu_la);
    mijloc_ly_de_sters->addWidget(descriere_la);
    mijloc_ly_de_sters->addWidget(tip_la);
    mijloc_ly_de_sters->addWidget(durata_la);

    dreapta_ly->addWidget(cos_qlist);
    dreapta_ly->addLayout(dr_cos_ly);
    dr_cos_ly->addRow(btn_gol_cos);
    dr_cos_ly->addRow(btn_exp_cos, in_exp_cos);

    final_ly->addLayout(final_ly_text);
    //final_ly_text->addStretch();
    final_ly_text->addLayout(final_ly_de_sters);
    final_ly_de_sters->addWidget(id_la_fi);
    final_ly_de_sters->addWidget(titlu_la_fi);
    final_ly_de_sters->addWidget(descriere_la_fi);
    final_ly_de_sters->addWidget(tip_la_fi);
    final_ly_de_sters->addWidget(durata_la_fi);
    //final_ly_text->addStretch();
}

Cos_GUI::Cos_GUI(Service* service, Lista_de_activitati* _cos, GUI* _gui)
{
    this->cos = _cos;
    this->gui = _gui;
    init_Cos_GUI(service);
    init_connect();
    this->service_mare->add_follower(this);
    load_cos();
}

PaintGUI::PaintGUI(Lista_de_activitati* _cos)
{
    this->cos = _cos;
    this->setLayout(ly);
    //ly->addWidget(this->qlista_cos);
    //this->show();
    // load
    repaint();
}

void PaintGUI::paintEvent(QPaintEvent*)
{
    qlista_cos->clear();
    QPainter p{this};
    Repo* repo = this->cos->get_repo();
    for (int i = 0; i < repo->len(); i++)
    {
        int durata = repo->get_pointer_activitate_poz(i)->get_durata();
        string titlu;
        repo->get_pointer_activitate_poz(i)->get_titlu(&titlu);
        qlista_cos->addItem(QString::fromStdString(titlu));
        p.drawRect((i + 1) * 40 + 1, 0, 20, durata * 10);
        //p.drawRect((i + 1) * 40 + 1, 0, 0, durata * 10);
        //p.drawEllipse(5*i, 5*i, 5*i, 5*i);
        //QMessageBox::information(nullptr, "ceva", "ceva");
        /*QRectF rectangle(10.0, 20.0, 80.0, 60.0);

        QPainter painter(this);*/
        //p.drawRoundedRect(rectangle, 20.0, 15.0);
    }
    /*p.drawRect(40, 0, 20, 70);
    p.drawRect(0, 0, 20, 30);
    p.drawRect(0, 0, 200, 200);
    p.drawLine(10, 10, 100, 100);
    p.drawLine(50, 5, 50, 5);*/

    /*QRectF target(20, 40, 100, 94);
    QRectF source(0, 0, 732, 720);
    QImage image("red.jpg");*/

    /*p.drawEllipse(QPointF(20, 20), 20, 20);

    p.drawImage(target, image, source);*/

    //QMessageBox::warning(nullptr, "ceva", "ceva");
}
