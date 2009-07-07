#include "DisplayablePlugin.h"
#include "ClientApplication.h"

void    DisplayablePlugin::setCentralWidget(QWidget *widget)
{
    return (((ClientApplication*)(QCoreApplication::instance()))->mainWindow->setCentralWidget(widget));
}
