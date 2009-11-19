#ifndef MANAGESTUDENTS_H
#define MANAGESTUDENTS_H
#include <QWidget>
#include <QHBoxLayout>

#include <QPushButton>

#include "FormStudents.h"
#include "ListSelection.h"
#include "Infopanel.h"
#include "Scrollformstudent.h"
#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"
#include "../../../../../Common/DataPlugin.h"
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
    QPushButton *refresh;
    QFrame* sidebar;
    QScrollArea *scrollArea;
QFrame *informationsFrame;
QVBoxLayout *informationsLayout;
    QList<UserData*> getAllParents();
    FormStudents *StudentForm;
    ScrollFormStudent *scrollStudentForm;
    ListSelection *StudentList;
    InfoPanel *info;
    UserDataPlugin* UD;
    TreeDataPlugin* TD;
    UserData* newUSer;
    UserData* newPapa;
    UserData* newMomy;
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
    void userCreated();
    void refreshall();
};

#endif // MANAGESTUDENTS_H
