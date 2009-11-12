#ifndef COURPANEL_H
#define COURPANEL_H

#include <QWidget>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

class CourPanel : public QWidget
{
    Q_OBJECT

    public:
        CourPanel(QString cName);
        QVBoxLayout     *checkBoxs;
        QVBoxLayout     *nameBoxs;
        QHBoxLayout     *courLayout;
        QLabel          *coursName;
        QCheckBox       *lateCheck;
        QCheckBox       *absenceCheck;
   private:
        void            setupUi(QString cName);
   private slots:
        void            retardChecked(int state);
        void            absChecked(int state);
};

#endif // COURPANEL_H
