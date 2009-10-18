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
        QHBoxLayout     *courLayout;
        QLabel          *coursName;
        QCheckBox       *lateCheck;
        QCheckBox       *absenceCheck;
   private:
        void            setupUi(QString cName);
};

#endif // COURPANEL_H
