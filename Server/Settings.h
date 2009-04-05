#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QtDebug>
#include <QStringList>

class Settings
{
public:
    Settings();
    void FirstSetSettings();
    QString GetSettings(QString key, QString group);
private:
    QSettings Gsettings;
};

#endif // SETTINGS_H
