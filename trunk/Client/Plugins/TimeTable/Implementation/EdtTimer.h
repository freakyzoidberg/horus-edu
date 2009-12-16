#ifndef EDTTIMER_H
#define EDTTIMER_H

#include <QTimeEdit>

class EdtTimer : public QTimeEdit
{
    public:
        EdtTimer(QWidget *parent);
    private:
        //void stepBy(int steps);
};

#endif // EDTTIMER_H
