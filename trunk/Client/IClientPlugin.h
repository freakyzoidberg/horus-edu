#ifndef ICLIENTPLUGIN_H
#define ICLIENTPLUGIN_H

class IClientPlugin
{
  public:
    virtual QString     getName() const = 0;
    virtual QString     getVersion() const = 0;
    virtual QStringList getPluginsConflicts() const = 0;
    virtual QStringList getPluginsRequired() const = 0;
    virtual QStringList getPluginsRecommended() const = 0;
    virtual QStringList getExports() const = 0;
    virtual QStringList getImplementations() const = 0;
};

#endif // ICLIENTPLUGIN_H
