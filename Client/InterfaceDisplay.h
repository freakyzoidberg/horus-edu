#ifndef INTERFACEDISPLAY_H
#define INTERFACEDISPLAY_H

#include "IDisplayable.h"

class InterfaceDisplay : public IDisplayable
{
public:
    InterfaceDisplay();
    bool setCentralWidget(QWidget *widget);
};

#endif // INTERFACEDISPLAY_H
