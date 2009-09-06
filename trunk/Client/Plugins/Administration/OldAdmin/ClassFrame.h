#ifndef ClassFrame_H
#define ClassFrame_H

#include "ui_ClassFrame.h"
#include "../../../NetworkPlugin.h"

class ClassFrame : public QFrame, private Ui::ClassFrame {
    Q_OBJECT
    Q_DISABLE_COPY(ClassFrame)
public:
     ClassFrame();

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // ClassFrame_H
