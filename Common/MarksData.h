#ifndef MARKSDATA_H
#define MARKSDATA_H

#include "Data.h"
#include "MarksDataPlugin.h"

class MarksData : public Data
{
	Q_OBJECT
#ifdef HORUS_SERVER
	Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
	Q_INTERFACES(ClientData)
#endif

public:


protected:
        inline				MarksData(MarksDataPlugin* plugin) : Data(plugin) { }
        inline				~MarksData() {}
};

#ifdef HORUS_SERVER
typedef MarksData ServerMarksData;
Q_DECLARE_INTERFACE(ServerMarksData, "net.horus.ServerMarksData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef MarksData ClientMarksData;
Q_DECLARE_INTERFACE(ClientMarksData, "net.horus.ClientMarksData/1.0");
#endif

#endif // MARKSDATA_H
