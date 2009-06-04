#ifndef ITREE_H
#define ITREE_H

#include <QHash>
#include <QString>

class ITree : public QObject
{
  Q_OBJECT

signals:
    void nodeUpdated();

public:
    virtual ITree    *GetParent() const = 0;
    virtual bool    isFilled() const = 0;
    //! insert node
    /*!
      add son node attached on the current node (this)

      \param name name of node
      \param user_ref id of the user in charge of this node
      \param type type of the node
      \return the id of the inserted node
    */
    virtual void     AddSon(int user_ref, QString name, QString type) = 0;
    //! delete node
    /*!
      delete current node node and attache sons to the  father's current node
    */
    virtual void     Delnode() = 0;
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    virtual void MoveNode(int idfather) = 0;
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    virtual void MoveNode(ITree* father) = 0;

    //! Delete node and attach child to first father
    /*!
      \param idnode node to remove
    */
   // bool DeleteNode();

    //! map of nodes
    /*!
      \return Map of sons node
    */
    virtual const QHash<int,ITree*>& GetSonsNode() const = 0;

    //! Get name of node
    /*!
      \return name of the node
    */
    virtual QString GetName() const = 0;

    //! Get id of node
    /*!
      \return id of the node
    */
    virtual int Getid() const = 0;
    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    virtual void SetName(QString name) = 0;

    //! Get User in charge of the node
    /*!
      \return user id of the referree of the node
    */
    virtual int GetUserRef() const = 0;

    //! Set User in charge of the node
    /*!
      \param userref new user in charge of the node
      \return Boolean state of the change userref
    */
    virtual void SetUserRef(int user_ref) = 0;

    //! Get type the node
    /*!
      \return user value of type
    */
    virtual QString GetType() const = 0;

    //! Set typee of the node
    /*!
      \param type to be assigned to the node
    */
    virtual void SetType(QString type) = 0;

    //! check if the node has a father
    /*!
      \param id of the father node
      \return Boolean result
    */
    virtual bool HasFatherId(int fathernode) = 0;

    //! check if the user is admin on this or fathers node
    /*!
      \param id of user to test
      \return Boolean result
    */
    virtual bool HasAdminRightOnNodeOrFathers(int userid) = 0;

protected:
    virtual ~ITree() = 0;
};

#endif // ITREE_H
