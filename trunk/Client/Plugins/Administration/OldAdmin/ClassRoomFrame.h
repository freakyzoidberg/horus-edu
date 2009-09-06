#ifndef ClassRoomFrame_H
#define ClassRoomFrame_H

#include "ui_ClassRoomFrame.h"
#include "../../../NetworkPlugin.h"

class ClassRoomFrame : public QFrame, private Ui::ClassRoomFrame {
    Q_OBJECT
    Q_DISABLE_COPY(ClassRoomFrame)
public:
     ClassRoomFrame();

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // ClassRoomFrame_H
