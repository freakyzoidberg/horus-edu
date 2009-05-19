//#define QT_NO_DEBUG_OUTPUT
#include <QtCore/QCoreApplication>
#include <QtNetwork>
#include <QtDebug>
#include <QThreadPool>
#include "Server.h"
#include "PluginManager.h"
#include "../Common/Defines.h"
#include <QString>
#include "Settings.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(SERVER_NAME);

    for (int i = 0; i < QCoreApplication::arguments().count(); i++)
        if (QCoreApplication::arguments().at(i) == "--gen-config")
            {
                Settings *tmpSetting = new Settings();
                tmpSetting->FirstSetSettings();
                delete tmpSetting;
                return (0);
           }

    Server theserver(&a);
    PluginManager::globalInstance();
    qDebug() << "main() Server Loaded";

    QThreadPool::globalInstance()->setMaxThreadCount(MAX_POOL_THREADS);

    return a.exec();
}
