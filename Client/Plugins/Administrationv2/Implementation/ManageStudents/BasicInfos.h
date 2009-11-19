#ifndef BASICINFOS_H
#define BASICINFOS_H
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QDate>
#include <QLineEdit>
#include <QDateEdit>
#include "../../../../../Common/UserData.h"
class BasicInfos : public QFrame
{
public:
    BasicInfos();
    BasicInfos(UserData* ud);
    QString getName() { return name->text();}
    QString getSurName() { return surname->text();}
    QString getBplace() { return bplace->text();}
    QDate   getBday() { return bday->date(); }
    QString getAddress() { return address->text();}
private:
    QLineEdit *name;
    QLineEdit *surname;
    QDateEdit *bday;
    QLineEdit *bplace;
    QLineEdit *address;
};


#endif // BASICINFOS_H

