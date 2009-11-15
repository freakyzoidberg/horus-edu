#ifndef ADMADDCLASSWIDGET_H
#define ADMADDCLASSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"

class AdmAddClassWidget : public QWidget
{
public:
                    AdmAddClassWidget(TreeDataPlugin *treeplugin,
                                      UserDataPlugin *userplugin);

private:
    TreeDataPlugin  *_treeplugin;
    UserDataPlugin  *_userplugin;

    void            initUserReferent(void);

    QLabel          *_classNameLabel;
    QLineEdit       *_className;

    QLabel          *_userReferentLabel;
    QComboBox       *_userReferent;

    QPushButton     *_save;
    QPushButton     *_cancel;

    QVBoxLayout     *_mainLayout;
};

#endif // ADMADDCLASSWIDGET_H
