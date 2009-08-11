#ifndef TREE_H
#define TREE_H

#include <QHash>
#include <QString>

class Tree
{

private:
    int id;
    int user_ref;
    int parent_id;
    Tree *parent;
    QString type;
    QString name;
    QHash<int, Tree*> sons;


public:
    static QHash<int, Tree*> maptree;
    Tree();
    ~Tree();
    static bool    UpdateVector();
    void    ShowSons();
    void    vecshow();
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
    //! delete node
    /*!
      delete current node node and attache sons to the  father's current node
      \return the id of the inserted node
    */
    bool     Delnode();
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
    QHash<int, Tree*> GetSonsNode() const;

    //! Get name of node
    /*!
      \return name of the node
    */
    QString GetName() const;

    //! Get id of node
    /*!
      \return id of the node
    */
    int Getid() const;
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

    //! Get type the node
    /*!
      \return user value of type
    */
    QString GetType() const;

    //! Set typee of the node
    /*!
      \param type to be assigned to the node
      \return Boolean state of the change type
    */
    bool SetType(QString type);

    //! check if the node has a father
    /*!
      \param id of the father node
      \return Boolean result
    */
    bool HasFatherId(int fathernode);

    //! check if the user is admin on this or fathers node
    /*!
      \param id of user to test
      \return Boolean result
    */
    bool HasAdminRightOnNodeAndFathers(int userid);

    static Tree* GetNodebyId(int id);
};

#endif // TREE_H