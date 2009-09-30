#ifndef USERFORM_H
#define USERFORM_H

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
#include <QtGui/QCalendarWidget>
#include <QWidget>
#include <QTreeView>
#include <QComboBox>
#include "../../../../Common/TreeData.h"
#include "UserModel.h"

class UserForm : public QWidget
{
    Q_OBJECT

    public:
        UserForm(TreeData* treeNode, UserData *_user, UserDataPlugin &_users);
        UserForm(TreeData* treeNode, UserDataPlugin &_users);
    private:
        void    setupUi();
        QHBoxLayout *stuLayout;
        QGroupBox *formW;
        QHBoxLayout *formLayout;
        QFormLayout *leftLayout;
        QLabel *label;
        QLineEdit *loginTxt;
        QLabel *label_1;
        QLineEdit *passTxt;
        QCalendarWidget *date;
        QLabel *label_2;
        QLineEdit *nomTxt;
        QLabel *label_3;
        QLineEdit *prenomTxt;
        QLabel *label_4;
        QLineEdit *phoneTxt;
        QLabel *label_7;
        QLineEdit *addrTxt;
        QLabel *label_8;
        QLineEdit *paysTxt;
        QLabel *label_11;
        QLineEdit *languageTxt;
        QCheckBox *activeBox;
        QFormLayout *rightLayout;
        QLabel *imageLabel;
        QPushButton *imageButton;
        QLineEdit *classTxt;
        QLabel *label_5;
        QLineEdit *lineEdit_7;
        QLabel *label_6;
        QComboBox *typeBox;
        QDialogButtonBox *buttonBox;
        QVBoxLayout *menuLayout;
        void    editUser();
        void    cancelUser();
        void    deleteUser();
        void    createUser();
        UserData* user;
        UserDataPlugin& users;
        QImage image;
        void fillUserFields();
        void clearForm();
   private slots:
        void buttonClicked(QAbstractButton * button);
        void ImageButtonClick();
};

#endif // USERFORM_H
