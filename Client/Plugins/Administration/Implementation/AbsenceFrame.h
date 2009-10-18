#ifndef ABSENCEFRAME_H
#define ABSENCEFRAME_H

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
#include <QComboBox>
#include <QtGui/QCalendarWidget>
#include <QListView>
#include "CourPanel.h"

class AbsenceFrame : public QWidget
{
    Q_OBJECT

    public:
        AbsenceFrame();
    private:
        QVBoxLayout         *leftSide;
        QGridLayout         *rightSide;
        QLineEdit           *userName;
        QComboBox           *classList;
        QListView           *userList;
        QCheckBox           *allCourse;
        QPushButton         *okButton;
        QList<CourPanel *>  courList;
        void                setupUi();

};

#endif // ABSENCEFRAME_H
