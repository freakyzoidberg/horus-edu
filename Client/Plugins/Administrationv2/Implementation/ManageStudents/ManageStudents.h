#ifndef MANAGESTUDENTS_H
#define MANAGESTUDENTS_H
#include <QWidget>
#include <QHBoxLayout>

#include <QPushButton>

#include "FormStudents.h"
#include "ListSelection.h"
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
    QFrame* sidebar;

    FormStudents *StudentForm;
    ListSelection *StudentList;
    UserDataPlugin* UD;
    TreeDataPlugin* TD;
private slots:
    void goadd();
    void goedit();
    void goback();
    void gosave();
    void seteditfalse();
    void setedittrue();

};

#endif // MANAGESTUDENTS_H
