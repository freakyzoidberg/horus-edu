#ifndef CALENDAR_H
#define CALENDAR_H

#include "Calendar_global.h"

namespace Horus
{
    namespace Server
    {
        class CALENDARSHARED_EXPORT Calendar : Module {
        public:
            Calendar();
            const std::string         name = "srvModCalendar";

            const std::list<Module&>  initAfterModules(const std::list<Module>& mods);

            void                      onRecvClientData(Client& cli, void* data);


        };
    }
}

#endif // CALENDAR_H
