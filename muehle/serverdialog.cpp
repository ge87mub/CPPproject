#include "serverdialog.h"
#include "ui_serverdialog.h"
#include <QIntValidator> //ensures the port value stays in 1024-65535 and no strings

ServerDialog::ServerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    ui->portLineEdit->setValidator(new QIntValidator(1024, 65535, this));
}

ServerDialog::~ServerDialog()
{
    delete ui;
}

quint16 ServerDialog::port() const
{
    return ui->portLineEdit->text().toUShort(); //type in the port you wanna have
}

quint8 ServerDialog::whostarts() const
{
    if (ui->whoStarts->currentIndex() == 0) {
        return 0x00;
    } else {
        return 0x01;
    }
}
