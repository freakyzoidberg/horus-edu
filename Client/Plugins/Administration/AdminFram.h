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

class AdminFram : public QWidget, public Ui::AdminForm
{
    Q_OBJECT
    Q_DISABLE_COPY(AdminFram)
    public:
        explicit AdminFram(INetwork *reseau);
        void        packetManager(QVariantHash response);
    protected:
        virtual void changeEvent(QEvent *e);
    private:
        TreeFram    *tF;
        UserFram    *uF;
        ClassFram   *cF;
        TeacherFram *teachF;
        SalleFram   *sF;
        FileFram    *fF;
        INetwork    *res;
        void        fillTab();
};

#endif // ADMINFRAM_H
