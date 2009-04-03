#ifndef TREE_H
#define TREE_H

#include "Tree_global.h"

namespace Horus
{
    namespace Server
    {
        class TREESHARED_EXPORT Tree : Module {
        public:
            Tree();
            const std::string         name = "srvModTree";

            const std::list<Module&>  initAfterModules(const std::list<Module>& mods);

            void                      onRecvClientData(Client& cli, void* data);

            Node&       createNode(uint parent, string name);
            Node&       getNode(uint id);
            list<Node&> searchNodes(string name);
        };
    }
}

#endif // TREE_H
