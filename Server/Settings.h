#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>

//!  Settings Class
/*!
  settings management for the server
*/
class Settings
{
public:
    Settings();
    void FirstSetSettings();
    QString GetSettings(QString key, QString group);
    void CheckSettings();
private:
    QSettings Gsettings;
};

#endif // SETTINGS_H
