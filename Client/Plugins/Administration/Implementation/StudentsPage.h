#ifndef STUDENTSPAGE_H
#define STUDENTSPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QCalendarWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QWidget>
#include <QTreeView>

#include "../../../../Common/TreeData.h"
#include "StudentModel.h"

class StudentsPage : public QWidget
{
    Q_OBJECT

    public:
        StudentsPage(TreeDataPlugin* tree, UserDataPlugin *users);
    private:
        void    setupUi();
        QHBoxLayout *stuLayout;
        QTreeView *studentTree;
        QGroupBox *formW;
        QHBoxLayout *formLayout;
        QFormLayout *leftLayout;
        QLabel *label;
        QLineEdit *loginTxt;
        QLabel *label_12;
        QLineEdit *passTxt;
        QCalendarWidget *date;
        QLabel *label_2;
        QLineEdit *nomTxt;
        QLabel *label_3;
        QLineEdit *prenomTxt;
        QLabel *label_4;
        QLineEdit *phoneTxt;
        QLabel *label_6;
        QLineEdit *phonebisTxt;
        QLabel *label_7;
        QLineEdit *addrTxt;
        QLabel *label_10;
        QLineEdit *codeTxt;
        QLabel *label_9;
        QLineEdit *villeTxt;
        QLabel *label_8;
        QLineEdit *paysTxt;
        QLabel *label_11;
        QLineEdit *languageTxt;
        QCheckBox *activeBox;
        QFormLayout *rightLayout;
        QGraphicsView *graphicsView;
        QLineEdit *classTxt;
        QLabel *label_5;
        QLineEdit *lineEdit_7;
        QDialogButtonBox *buttonBox;
        QVBoxLayout *menuLayout;
        void    editUser();
        void    cancelUser();
        void    deleteUser();
        void    createUser();
        UserDataPlugin *_users;
        int     idUser;
   private slots:
    void buttonClicked(QAbstractButton * button);
    void userSelected(const QModelIndex &userIndex);
};

#endif // STUDENTSPAGE_H
