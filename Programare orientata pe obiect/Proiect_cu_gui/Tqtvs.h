#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tqtvs.h"

class Tqtvs : public QMainWindow
{
    Q_OBJECT

public:
    Tqtvs(QWidget *parent = nullptr);
    ~Tqtvs();

private:
    Ui::TqtvsClass ui;
};
