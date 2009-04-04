#ifndef IMODULE_H
#define IMODULE_H

#include <string>
#include <vector>

Class IModule
{

  private:

    std::string                 modName;
    std::string                 modVersion;
    std::vector<std::string>    modConflicts;
    std::vector<std::string>    modRequired;
    std::vector<std::string>    modRecommended;
};

#endif // IMODULE_H
