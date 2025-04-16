#ifndef MUEHLE_H
#define MUEHLE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Muehle;
}
QT_END_NAMESPACE

class Muehle : public QMainWindow
{
    Q_OBJECT

public:
    Muehle(QWidget *parent = nullptr);
    ~Muehle();

private:
    Ui::Muehle *ui;
};
#endif // MUEHLE_H
