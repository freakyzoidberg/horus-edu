#ifndef FILEFRAM_H
#define FILEFRAM_H

#include "ui_FileFram.h"

class FileFram : public QFrame, private Ui::FileFram {
    Q_OBJECT
    Q_DISABLE_COPY(FileFram)
public:
    explicit FileFram(QWidget *parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // FILEFRAM_H
