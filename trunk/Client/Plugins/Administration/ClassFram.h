#ifndef CLASSFRAM_H
#define CLASSFRAM_H

#include "ui_ClassFram.h"

class ClassFram : public QFrame, private Ui::ClassFram {
    Q_OBJECT
    Q_DISABLE_COPY(ClassFram)
public:
    explicit ClassFram(QWidget *parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // CLASSFRAM_H
