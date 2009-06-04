#ifndef TEACHERFRAM_H
#define TEACHERFRAM_H

#include "ui_TeacherFram.h"
#include "../../INetworkPlugin.h"

class TeacherFram : public QFrame, private Ui::TeacherFram {
    Q_OBJECT
    Q_DISABLE_COPY(TeacherFram)
public:
    explicit TeacherFram(INetwork *res);

protected:
    virtual void changeEvent(QEvent *e);
};

#endif // TEACHERFRAM_H
