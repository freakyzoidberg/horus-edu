#ifndef NODEINFO_H
#define NODEINFO_H

#include <QWidget>
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

#include "../../../../Common/TreeData.h"

class NodeInfo : public QWidget
{
    Q_OBJECT
    public:
        NodeInfo(TreeData &_node, int type);
    private:
        void    setupUi();
        QGroupBox *infos;
        QVBoxLayout *mainLayout;
        QFormLayout *nodeLayout;
        QLabel *label;
        QLineEdit *idTxt;
        QLabel *label_1;
        QLineEdit *nameTxt;
        QCalendarWidget *date;
        QLabel *label_2;
        QLineEdit *nomTxt;
        QLabel *label_3;
        QLineEdit *typeTxt;
        QLabel *label_4;
        QLineEdit *userTxt;
        QDialogButtonBox *buttonBox;
        TreeData&   node;
        void fillFields();
    private slots:
        void buttonClicked(QAbstractButton * button);
};

#endif // NODEINFO_H
