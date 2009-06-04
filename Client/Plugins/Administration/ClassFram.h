#ifndef CLASSFRAM_H
#define CLASSFRAM_H

#include "ui_ClassFram.h"
#include "../../INetworkPlugin.h"

class ClassFram : public QFrame, private Ui::ClassFram {
    Q_OBJECT
    Q_DISABLE_COPY(ClassFram)
public:
    explicit ClassFram(INetwork *res);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // CLASSFRAM_H
