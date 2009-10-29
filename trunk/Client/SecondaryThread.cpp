#include "SecondaryThread.h"

#include <QDebug>

QThread* SecondaryThread::instance()
{
	static QThread* _instance = 0;
	if ( ! _instance)
	{
		_instance = new QThread;
		_instance->start();
		qDebug() << "2nd thread:" << _instance;
	}
	return _instance;
}
