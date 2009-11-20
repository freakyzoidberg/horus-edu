#ifndef BASICINFOS_H
#define BASICINFOS_H
#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QDate>
#include <QLineEdit>
#include <QDateEdit>
#include "../../../../../Common/UserData.h"
#include <QSpinBox>
class BasicInfos : public QFrame
{
	Q_OBJECT

public:
    BasicInfos();
    BasicInfos(UserData* ud);
    QString getName() { return name->text();}
    QString getSurName() { return surname->text();}
    QString getBplace() { return bplace->text();}
    QDate   getBday() { return bday->date(); }
    QString getAddress() { return address->text();}
    QString getEmail() { return email->text();}
    int getbrocount() { return brosis->value();}
private:
    QLineEdit *name;
    QLineEdit *surname;
    QDateEdit *bday;
    QLineEdit *bplace;
    QLineEdit *address;
    QLineEdit *email;
    QSpinBox *brosis;
};


#endif // BASICINFOS_H

