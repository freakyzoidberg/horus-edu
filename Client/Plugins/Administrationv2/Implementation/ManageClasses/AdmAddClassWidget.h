#ifndef ADMADDCLASSWIDGET_H
#define ADMADDCLASSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableWidget>

#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"

class AdmAddClassWidget : public QWidget
{
    Q_OBJECT

public:
                    AdmAddClassWidget(TreeDataPlugin *treeplugin,
                                      UserDataPlugin *userplugin);
    void            addClassInDatabase();
    void            displayClasses();

public slots:
    void            addClass();
    void            emptyField();
    void            modifUser();
	void			cellClicked(int, int);

private:
    void            initUserReferent(void);

    TreeDataPlugin  *_treeplugin;
    UserDataPlugin  *_userplugin;

    QLabel          *_classNameLabel;
    QLineEdit       *_className;

    QLabel          *_userReferentLabel;
    QComboBox       *_userReferent;

    QPushButton     *_save;
    QPushButton     *_cancel;

    QHBoxLayout     *_mainLayout;
    QTableWidget    *_table;

    UserData        *save;
};

#endif // ADMADDCLASSWIDGET_H
