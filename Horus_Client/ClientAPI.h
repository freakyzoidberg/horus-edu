#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <string>
#include <vector>
#include <QEvent>

class IClientModule
{
  public:
    virtual void setModName(const &std::string) = 0;
    virtual void setModVersion(const &std::string) = 0;
    virtual void setModConflicts(const &std::string, const &std::string) = 0;
    virtual void setModRequired(const &std::string, const &std::string) = 0;
    virtual void setModRecommended(const &std::string, const &std::string) = 0;
    virtual void setExports(const void *) = 0;

  public:
    virtual const std::string                   getModName() = 0;
    virtual const std::string                   getModVersion() = 0;
    virtual const std::vector<std::string[2]>   getModConflicts() = 0;
    virtual const std::vector<std::string[2]>   getModRequired() = 0;
    virtual const std::vector<std::string[2]>   getModRecommended() = 0;
    virtual const void                          *getExports() = 0;

  private:
    virtual std::string                     modName = 0;
    virtual std::string                     modVersion = 0;
    virtual std::vector<std::string[2]>     modConflicts = 0;
    virtual std::vector<std::string[2]>     modRequired = 0;
    virtual std::vector<std::string[2]>     modRecommended = 0;

    virtual void    *exports = 0;

    virtual QEvent::QEvent  eventDispather = 0;
    virtual QEvent::QEvent  eventListener = 0;
};

#endif // CLIENTAPI_H
