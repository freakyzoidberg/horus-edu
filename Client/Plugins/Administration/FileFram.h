#ifndef FILEFRAM_H
#define FILEFRAM_H

#include "ui_FileFram.h"
#include "../../INetworkPlugin.h"

class FileFram : public QFrame, private Ui::FileFram {
    Q_OBJECT
    Q_DISABLE_COPY(FileFram)
public:
    explicit FileFram(INetwork *res);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // FILEFRAM_H
