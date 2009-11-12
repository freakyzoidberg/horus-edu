#ifndef GRADEDATA_H
#define GRADEDATA_H

#include "Data.h"
#include "GradeDataPlugin.h"

class GradeData : public Data
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
        inline				GradeData(GradeDataPlugin* plugin) : Data(plugin) { }
        inline				~GradeData() {}
};

#ifdef HORUS_SERVER
typedef GradeData ServerGradeData;
Q_DECLARE_INTERFACE(ServerGradeData, "net.horus.ServerGradeData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef GradeData ClientGradeData;
Q_DECLARE_INTERFACE(ClientGradeData, "net.horus.ClientGradeData/1.0");
#endif

#endif // GRADEDATA_H
