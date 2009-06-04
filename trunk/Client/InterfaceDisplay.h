#ifndef INTERFACEDISPLAY_H
#define INTERFACEDISPLAY_H

#include "IDisplayable.h"

#include "ClientApplication.h"

class InterfaceDisplay : public IDisplayable
{
public:
    InterfaceDisplay(ClientApplication *app);
    void setCentralWidget(QWidget *widget);

private:
    ClientApplication *app;
};

#endif // INTERFACEDISPLAY_H
