#ifndef ADMADDCLASSWIDGET_H
#define ADMADDCLASSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QListWidget>

#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"
#include "classlist.h"

class AdmAddClassWidget : public QWidget
{
    Q_OBJECT

public:
                    AdmAddClassWidget(TreeDataPlugin *treeplugin,
                                      UserDataPlugin *userplugin);
    void            addClassInDatabase();
	void            displayClasses(int id = -1);

public slots:
    void            addClass();
    void            emptyField();
    void            modifUser();
  //  void            cellClicked(int, int);
	void            choosenClass(QListWidgetItem *);
	void			deleteClass();
	void			refreshList(Data *);

private:
    void            initUserReferent(void);
    void            editClassInDatabase();
    
    TreeDataPlugin  *_treeplugin;
    UserDataPlugin  *_userplugin;

	ClassList		*_classList;

    QLabel          *_classNameLabel;
    QLineEdit       *_className;

    QLabel          *_userReferentLabel;
    QComboBox       *_userReferent;

    QPushButton     *_save;
    QPushButton     *_cancel;

	//pompage
	QPushButton *addstudent;
	QPushButton *editstudent;
	QPushButton *back;
	QPushButton *edit;
	//QPushButton *save;
	QPushButton *del;
	QPushButton *ok;
	QPushButton *reset;
	QPushButton *refresh;

    QHBoxLayout     *_mainLayout;
   // QTableWidget    *_table;

	QLabel			*infoTitle;
	QLabel			*actions;
	int				currentrow;

	TreeData        *selectedData, *classSave;
    UserData        *save;
};

#endif // ADMADDCLASSWIDGET_H
