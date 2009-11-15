#ifndef BASICINFOS_H
#define BASICINFOS_H
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
class BasicInfos : public QWidget
{
public:
    BasicInfos();

private:
    QLineEdit *name;
    QLineEdit *surname;
    QLineEdit *bday;
};

#endif // BASICINFOS_H
