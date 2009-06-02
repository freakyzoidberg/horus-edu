#ifndef ADMINFRAM_H
#define ADMINFRAM_H

#include "ui_AdminFram.h"
#include "AdministrationPlugin.h"

class AdminFram : public QWidget, private Ui::AdminForm
{
    Q_OBJECT
    Q_DISABLE_COPY(AdminFram)
public:
    explicit AdminFram(QWidget *parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // ADMINFRAM_H
