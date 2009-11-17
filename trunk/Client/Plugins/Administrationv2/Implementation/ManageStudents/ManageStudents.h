#ifndef MANAGESTUDENTS_H
#define MANAGESTUDENTS_H
#include <QWidget>
#include <QHBoxLayout>

#include <QPushButton>

#include "FormStudents.h"
#include "ListSelection.h"
#include "Infopanel.h"
#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"

class ManageStudents : public QWidget
{
    Q_OBJECT

public:
    ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin);



private:
    QHBoxLayout *MainLayout;

    QPushButton *addstudent;
    QPushButton *editstudent;
    QPushButton *back;
    QPushButton *edit;
    QPushButton *save;
    QPushButton *del;
    QPushButton *ok;
    QPushButton *reset;
    QFrame* sidebar;
QFrame *informationsFrame;
QVBoxLayout *informationsLayout;
    QList<UserData*> getAllParents();
    FormStudents *StudentForm;
    ListSelection *StudentList;
    InfoPanel *info;
    UserDataPlugin* UD;
    TreeDataPlugin* TD;
private slots:
    void goadd();
    void goedit();
    void goback();
    void gook();
    void goreset();
    void gosave();
    void godel();
    void seteditfalse();
    void setedittrue();
    void checkCreated(Data *user);

};

#endif // MANAGESTUDENTS_H
