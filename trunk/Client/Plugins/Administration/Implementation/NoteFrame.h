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
#include <QListWidget>
#include "ElevePanel.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/EventData.h"

class NoteFrame : public QWidget
{
    Q_OBJECT

    public:
        NoteFrame(TreeDataPlugin *tree, UserDataPlugin *user, EventDataPlugin *event);
    private:
        QVBoxLayout         *leftSide;
        QHBoxLayout         *noteLayout;
        QLineEdit           *userName;
        QComboBox           *classList;
        QListWidget           *matiereList;
        QListWidget           *examList;
        ElevePanel          *listEleve;
        TreeDataPlugin      *tree;
        QHash<quint32,  UserData*> users;
        void                setupUi();
        void                fillClass(TreeDataPlugin *tree);
        int                 id;
    private slots:
        void                classChanged( int index );
        void                matiereSelected(QListWidgetItem *item);
        void                examSelected(QListWidgetItem *item);
};

#endif // NOTEFRAME_H
