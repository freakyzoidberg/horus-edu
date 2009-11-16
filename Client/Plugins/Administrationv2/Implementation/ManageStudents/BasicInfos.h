#ifndef BASICINFOS_H
#define BASICINFOS_H
#include <QFormLayout>
#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QLineEdit>
#include <QDateEdit>
#include "../../../../../Common/UserData.h"
class BasicInfos : public QWidget
{
public:
    BasicInfos();
    BasicInfos(UserData* ud);
    QString getName() { return name->text();}
    QString getSurName() { return surname->text();}
    QDate   getBday() { return bday->date(); }
    QString getAddress() { return address->text();}
private:
    QLineEdit *name;
    QLineEdit *surname;
    QDateEdit *bday;
    QLineEdit *address;
};


#endif // BASICINFOS_H
