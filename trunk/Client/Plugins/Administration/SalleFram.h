#ifndef SALLEFRAM_H
#define SALLEFRAM_H

#include "ui_SalleFram.h"
#include "../../INetworkPlugin.h"

class SalleFram : public QFrame, private Ui::SalleFram {
    Q_OBJECT
    Q_DISABLE_COPY(SalleFram)
public:
    explicit SalleFram(INetwork *res);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // SALLEFRAM_H
