#include "calendar.h"


Calendar::Calendar()
{
}

const QString   Calendar::pluginName()    const
{
    return "dudule";
}
    //! Return the version of the plugin.
    /*!
     *  This function provide the version of the plugin.
     *  \return the version of the plugin
     */
const QString   Calendar::pluginVersion() const
{
    return "0.001b.17/10/2009.18h19min";
}
