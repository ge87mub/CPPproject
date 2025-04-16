#include "muehle.h"
#include "ui_muehle.h"

Muehle::Muehle(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Muehle)
{
    ui->setupUi(this);
}

Muehle::~Muehle()
{
    delete ui;
}
