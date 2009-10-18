#ifndef NOTEFRAME_H
#define NOTEFRAME_H

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
#include "ElevePanel.h"

class NoteFrame : public QWidget
{
    Q_OBJECT

    public:
        NoteFrame();
    private:
        QVBoxLayout         *leftSide;
        QGridLayout         *rightSide;
        QLineEdit           *userName;
        QComboBox           *classList;
        QListView           *matiereList;
        QListView           *examList;
        QLineEdit           *coef;
        QPushButton         *okButton;
        QList<ElevePanel *> courList;
        void                setupUi();
};

#endif // NOTEFRAME_H
