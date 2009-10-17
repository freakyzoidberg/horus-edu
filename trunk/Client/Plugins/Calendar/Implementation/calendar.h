#ifndef CALENDAR_H
#define CALENDAR_H

#include <QString>

# include "../../../../Common/Plugin.h"

class Calendar : public Plugin
{
Q_OBJECT
Q_INTERFACES(Plugin)

public:
    Calendar();
    const QString   pluginName()    const;
    //! Return the version of the plugin.
    /*!
     *  This function provide the version of the plugin.
     *  \return the version of the plugin
     */
    const QString   pluginVersion() const;
};

#endif // CALENDAR_H
