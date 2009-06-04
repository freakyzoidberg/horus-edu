#include "InterfaceDisplay.h"

InterfaceDisplay::InterfaceDisplay(ClientApplication *app)
{
    this->app = app;
}

void    InterfaceDisplay::setCentralWidget(QWidget *widget)
{
    return (app->mainWindow->setCentralWidget(widget));
}
