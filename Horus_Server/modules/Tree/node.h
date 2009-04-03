#ifndef NODE_H
#define NODE_H

namespace Horus
{
    namespace Server
    {
        class Node
        {
        private:
            string name;

        public:
            Node();
            const unit id;

            list<Node&> getChilds();
            Node&       getParent();
            list<Node&> getParents();
            string      getName();
            void        setName(string name);
        };
    }
}

#endif // NODE_H
