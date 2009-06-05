#ifndef ADMINFRAM_H
#define ADMINFRAM_H

#include "ui_AdminFram.h"
#include "TreeFram.h"
#include "UserFram.h"
#include "ClassFram.h"
#include "FileFram.h"
#include "SalleFram.h"
#include "TeacherFram.h"
#include <QVariant>
 #include <QQueue>

class AdminFram : public QWidget, public Ui::AdminForm
{
    Q_OBJECT

    public:
        explicit AdminFram(INetwork *reseau);
        void        packetManager(QVariantHash response);
    protected:
        virtual void changeEvent(QEvent *e);
    private:
        UserFram    *uF;
        ClassFram   *cF;
        TeacherFram *teachF;
        SalleFram   *sF;
        FileFram    *fF;
        INetwork    *res;
        void        fillTab();
        QQueue<QString> packetSender;
    protected slots:
        //! slot to send packet to a client
        void        sender(const QString&);
};

#endif // ADMINFRAM_H
