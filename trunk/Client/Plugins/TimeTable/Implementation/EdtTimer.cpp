#include "EdtTimer.h"

EdtTimer::EdtTimer(QWidget *parent)
{
    this->setParent(parent);
}

//void EdtTimer::stepBy(int steps)
//{
//    if(this->currentSection() == this->MinuteSection)
//    {
//        this->time().minute();//stepBy(steps * 5);
//    }
//    else
//        stepBy(steps);
//}
