#ifndef TREE_H
#define TREE_H

#include <QHash>
#include <QString>
#include <QVariant>

class Tree : public QObject
{
  Q_OBJECT


public:
    static Tree* GetNodebyId(int id);
    static void updateUserTree();
    static void receiveUserTree(const QVariantHash& response);
private:
    static QHash<int, Tree*> maptree;


public slots:
    void receiveUpdate(const int _id, const int _parent, const int _user_ref, const QString _name, const QString _type, const QHash<int,Tree*> _sons);
signals:
    void nodeUpdated();


public:
    inline Tree    *GetParent() const { return parent; }
    inline bool    isFilled() const { return filled; }
    //! insert node
    /*!
      add son node attached on the current node (this)

      \param name name of node
      \param user_ref id of the user in charge of this node
      \param type type of the node
      \return the id of the inserted node
    */
    void     AddSon(int user_ref, QString name, QString type);
    //! delete node
    /*!
      delete current node node and attache sons to the  father's current node
    */
    void     Delnode();
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    void MoveNode(int idfather);
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    void MoveNode(Tree* father);

    //! Delete node and attach child to first father
    /*!
      \param idnode node to remove
    */
   // bool DeleteNode();

    //! map of nodes
    /*!
      \return Map of sons node
    */
    inline const QHash<int,Tree*>& GetSonsNode() const { return sons; }

    //! Get name of node
    /*!
      \return name of the node
    */
    inline QString GetName() const { return name; }

    //! Get id of node
    /*!
      \return id of the node
    */
    inline int Getid() const { return id; }
    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    void SetName(QString name);

    //! Get User in charge of the node
    /*!
      \return user id of the referree of the node
    */
    inline int GetUserRef() const { return user_ref; }

    //! Set User in charge of the node
    /*!
      \param userref new user in charge of the node
      \return Boolean state of the change userref
    */
    void SetUserRef(int user_ref);

    //! Get type the node
    /*!
      \return user value of type
    */
    inline QString GetType() const { return type; }

    //! Set typee of the node
    /*!
      \param type to be assigned to the node
    */
    void SetType(QString type);

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
    bool HasAdminRightOnNodeOrFathers(int userid);

private:
    inline Tree(int _id) { id=_id; user_ref=0; parent=0; maptree[id]=this; filled=false; }
    inline ~Tree() {}
    int id;
    int user_ref;
    Tree *parent;
    QString type;
    QString name;
    QHash<int,Tree*> sons;
    bool filled;
};

#endif // TREE_H
