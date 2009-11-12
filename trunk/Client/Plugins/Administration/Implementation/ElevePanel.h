#ifndef ELEVEPANEL_H
#define ELEVEPANEL_H

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
#include <QDateEdit>
#include "CourPanel.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h"
#include <qDebug>
#include <QMessageBox>

class ElevePanel : public QWidget
{
    Q_OBJECT

    public:
        ElevePanel(QHash<int, QString> eleves);
        QHash<int, QList<QVariant > > getMarks();
    private:
        QLabel      *coefLabel;
        QLineEdit   *coef;
        QDateEdit   *date;
        QScrollArea *scrollArea;
        QVBoxLayout *mainLayout;
        QHBoxLayout *bottomLayout;
        QPushButton *okButton;
        void        setupUi();
        void        fillStudents(QHash<int, QString> students);
        QHash<int, QList<QWidget* > > hNotes;
    private slots:
        void                validateClicked();
};

#endif // ELEVEPANEL_H
