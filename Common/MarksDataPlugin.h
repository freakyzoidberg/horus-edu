#ifndef MARKSDATAPLUGIN_H
#define MARKSDATAPLUGIN_H

#include <QDateTime>
#include "DataPlugin.h"

class TreeData;
class MarksData;
class MarksDataPlugin : public DataPlugin
{
    Q_OBJECT
#ifdef HORUS_SERVER
    Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
    Q_INTERFACES(ClientDataPlugin)
#endif

public:

};

#ifdef HORUS_SERVER
typedef MarksDataPlugin ServerMarksDataPlugin;
Q_DECLARE_INTERFACE(ServerMarksDataPlugin, "net.horus.ServerMarksDataPlugin/1.0");
#endif
#ifdef HORUS_CLIENT
typedef MarksDataPlugin ClientMarksDataPlugin;
Q_DECLARE_INTERFACE(ClientMarksDataPlugin, "net.horus.ClientMarksDataPlugin/1.0");
#endif

#endif // MARKSDATAPLUGIN_H
