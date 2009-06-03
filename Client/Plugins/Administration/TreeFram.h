#ifndef TREEFRAM_H
#define TREEFRAM_H

#include "ui_TreeFram.h"

class TreeFram : public QFrame, private Ui::TreeFram
{
    Q_OBJECT
    Q_DISABLE_COPY(TreeFram)
    public:
        explicit TreeFram(QWidget *parent = 0);

    protected:
        virtual void changeEvent(QEvent *e);

};

#endif // TREEFRAM_H
