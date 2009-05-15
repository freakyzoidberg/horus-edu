#ifndef TREE_H
#define TREE_H
#include <QMap>
#include <QString>
#include <Sql.h>
class Tree
{

private:
    int id;
    int user_ref;
    int parent_id;
    Tree *parent;
    QString type;
    QString name;
    QMap<int, Tree*> sons;
    static QMap<int, Tree*> maptree;

public:
    Tree();
    ~Tree();
    bool    UpdateVector();
    void    ShowSons();
    Tree    *GetParent() const;
    //! insert node
    /*!
      add son node attached on the current node (this)

      \param name name of node
      \param user_ref id of the user in charge of this node
      \param type type of the node
      \return the id of the inserted node
    */
    int     AddSon(int user_ref, QString name, QString type);
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    bool MoveNode(int idfather);
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    bool MoveNode(Tree* father);

    //! Delete node and attach child to first father
    /*!
      \param idnode node to remove
    */
   // bool DeleteNode();

    //! map of nodes
    /*!
      \return Map of sons node
    */
    QMap<int, Tree*> GetSonsNode() const;

    //! Get name of node
    /*!
      \return name of the node
    */
    QString GetName() const;

    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    bool SetName(QString name);

    //! Get User in charge of the node
    /*!
      \return user id of the referree of the node
    */
    int GetUserRef() const;

    //! Set User in charge of the node
    /*!
      \param userref new user in charge of the node
      \return Boolean state of the change userref
    */
    bool SetUserRef(int user_ref);


    static Tree* GetNodebyId(int id);
};

#endif // TREE_H
