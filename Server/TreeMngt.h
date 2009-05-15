#ifndef TREEMNGT_H
#define TREEMNGT_H
#include <QString>
#include <QByteArray>
#include <Sql.h>

//! Tree of linked node (groups, events, and so on)
/*!
  Allow the server to link any kind of node together
  some restriction may apply (as for users that can only be a leaf nor a node)
*/
class TreeMngt
{
private:
    //! Node of tree
    typedef struct {
        int id;
        QString name;
        int user_ref;
        int parent_id;
        int *fathernode;
        QMap<int, int> sons;
    } node;
    //! Mutex to prevent multiple modify access to the map
    static QMutex mymute;
    //! Map holding the tree
    static QMap<int, node> vectree;
public:


    TreeMngt();
    ~TreeMngt();


    void vecshow(QMap<int, node> vec);
};

#endif // TREEMNGT_H
