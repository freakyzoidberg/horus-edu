#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <string>
#include <vector>
#include <QEvent>

class IClientModule
{
  private:
    virtual std::string                 modName = 0;
    virtual std::string                 modVersion = 0;
    virtual std::vector<std::string>    modConflicts = 0;
    virtual std::vector<std::string>    modRequired = 0;
    virtual std::vector<std::string>    modRecommended = 0;

    virtual void    *exports = 0;

    virtual QEvent::QEvent  eventDispather = 0;
    virtual QEvent::QEvent  eventListener = 0;
};

#endif // CLIENTAPI_H
