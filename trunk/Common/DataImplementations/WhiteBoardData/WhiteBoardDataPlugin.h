#ifndef WHITEBOARDDATAPLUGIN_H
#define WHITEBOARDDATAPLUGIN_H

#include <QHash>
#include "../../DataPlugin.h"

class Data;
class TreeData;
class WhiteBoardData;
class WhiteBoardDataPlugin : public DataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientDataPlugin)
#endif

public:
	inline const QString pluginName()    const { return "WhiteBoard Data Plugin"; }
	inline const QString pluginVersion() const { return "0.1"; }
	inline const QString getDataType()   const { return "WhiteBoardData"; }

	WhiteBoardData*      getWhiteBoard(TreeData* node);
	WhiteBoardData*      getWhiteBoard(quint32 nodeId);
#ifdef HORUS_CLIENT
    void                 dataHaveNewKey(Data*d, QDataStream& s);
#endif
#ifdef HORUS_SERVER
    void                 loadDataBase(QSqlQuery&);
    void                 userDisconnected(UserData* user);
    UserData*            authenticatePassword(QSqlQuery& query, const QString& login, const QByteArray& password);
    UserData*            authenticateSession (QSqlQuery& query, const QString& login, const QByteArray& sesion);
    void                 sendUpdates(QSqlQuery&, UserData* user, QDateTime date);
#endif

protected:
    //! Return the pointer to the Data with a his unique key read in the stream
    Data*                getDataWithKey(QDataStream& s);

private:
	QList<WhiteBoardData*> whiteBoards;
};

#endif // WHITEBOARDDATAPLUGIN_H
