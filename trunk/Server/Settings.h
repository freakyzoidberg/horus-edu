#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>

//!  Manage settings for the server
/*!
  settings management for the server
*/
class Settings
{
public:
    Settings();
    //! initial set of settigns
    void FirstSetSettings();
    //! get the value of a given setting
    /*!
      \param key key value of the setting
      \param group group of which the settings depend
      \return the value of the actual settin
    */
    QString GetSettings(QString key, QString group);
    //! check the integrity of the settings on the system
    void CheckSettings();
private:
    QSettings Gsettings;
#endif // SETTINGS_H
