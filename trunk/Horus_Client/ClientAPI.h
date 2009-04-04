#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <string>
#include <vector>

Class IClientModule
{
  private:
    std::string                 modName;
    std::string                 modVersion;
    std::vector<std::string>    modConflicts;
    std::vector<std::string>    modRequired;
    std::vector<std::string>    modRecommended;

    void    *exports;
};

#endif // CLIENTAPI_H
