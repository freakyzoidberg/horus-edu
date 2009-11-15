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
    QString getName() { return name->text();};
    QString getSurName() { return surname->text();};
    QString getBday() { return bday->text();};
    QString getAddress() { return address->text();};
private:
    QLineEdit *name;
    QLineEdit *surname;
    QLineEdit *bday;
    QLineEdit *address;
};

#endif // BASICINFOS_H
