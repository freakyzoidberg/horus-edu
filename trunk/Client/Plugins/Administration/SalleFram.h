#ifndef SALLEFRAM_H
#define SALLEFRAM_H

#include "ui_SalleFram.h"

class SalleFram : public QFrame, private Ui::SalleFram {
    Q_OBJECT
    Q_DISABLE_COPY(SalleFram)
public:
    explicit SalleFram(QWidget *parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // SALLEFRAM_H
