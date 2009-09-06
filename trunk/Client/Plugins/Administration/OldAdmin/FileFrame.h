#ifndef FileFrame_H
#define FileFrame_H

#include "ui_FileFrame.h"
#include "../../../NetworkPlugin.h"

class FileFrame : public QFrame, private Ui::FileFrame {
    Q_OBJECT
    Q_DISABLE_COPY(FileFrame)
public:
     FileFrame();

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // FileFrame_H
