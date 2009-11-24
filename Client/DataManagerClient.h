#ifndef DATAMANAGERCLIENT_H
#define DATAMANAGERCLIENT_H

#include "../Common/DataManager.h"
#include <QHash>
class Data;
class DataPlugin;

class DataManagerClient : public DataManager
{
  Q_OBJECT
public:
	DataManagerClient(DataPlugin* parent);


// DataManager
public slots:
	void				dataStatusChange(Data* data, quint8 newStatus);
	void				sendData(Data* data);
	void				receiveData(const QByteArray& packet);


private:
	DataPlugin*			_plugin;
	QList<Data*>		_needSaveAgain;
	QHash<Data*,Data*>	_dependantDatas;
};

#endif // DATAMANAGERCLIENT_H
