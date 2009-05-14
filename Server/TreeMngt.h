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


    //! Get name of node by id
    /*!
      \param idnode node id from database
      \return name of the node
    */
    QString GetName(int idnode) const;

    //! Set name of node by id
    /*!
      \param idnode node id from database
      \param name new name for the corresponding node
    */
    bool SetName(int idnode, QString name);


    //! Get User in charge of the node
    /*!
      \param idnode node id from database
      \return user id of the referree of the node
    */
    int GetUserRef(int idnode) const;

    //! Set User in charge of the node
    /*!
      \param idnode node id from database
      \param userref new user in charge of the node
    */
    bool SetUserRef(int idnode, int userref);

    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    bool MoveNode(int idmove, int idfather);

    //! insert node
    /*!
      \param name name of father
      \param userref id of the user in charge of this node
      \param idfather if of the node to attach the new one
    */
    int InsertNode(QString name, int userref, int idfather);

    //! Delete node and attach child to first father
    /*!
      \param idnode node to remove
    */
    bool DeleteNode(int idnode);

   //! id of the father of the current node
    /*!
      \param idnode node to get infos
      \return user id of the father node
    */
    int GetFatherNode(int idnode) const;

    //! id of the sons of the current node
    /*!
      \param idnode node to get infos
      \return Map of ids of sons node
    */
    QMap<int, int> GetSonsNode(int idnode) const;

     //! Completely fill vector from db
    bool UpdateVector();

    void vecshow(QMap<int, node> vec);
};

#endif // TREEMNGT_H
