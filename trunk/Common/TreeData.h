#ifndef TREEDATA_H
#define TREEDATA_H

#include <QHash>
#include <QString>

#include "Data.h"
#include "TreeDataPlugin.h"

class TreeData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

public:
    //! insert node
    /*!
      add son node attached on the current node (this)

      \param name name of node
      \param user_ref id of the user in charge of this node
      \param type type of the node
      \return the id of the inserted node
    */
    virtual void    createChild(int userId, QString name, QString type) = 0;
    //! delete node
    /*!
      delete current node node and attache sons to the  father's current node
    */
    virtual void    remove() = 0;
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    virtual void    moveTo(int idfather) = 0;
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    virtual void    moveTo(TreeData* father) = 0;

    //! Get name of node
    /*!
      \return name of the node
    */
    virtual QString getName() const = 0;

    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    virtual void    setName(QString name) = 0;

    //! Get id of node
    /*!
      \return id of the node
    */
    inline int     getId() const { return nodeId; }

    //! Get User in charge of the node
    /*!
      \return user id of the referree of the node
    */
    virtual int     getUserId() const = 0;

    //! Set User in charge of the node
    /*!
      \param userref new user in charge of the node
      \return Boolean state of the change userref
    */
    virtual void    setUserId(int user) = 0;

    //! Get type the node
    /*!
      \return user value of type
    */
    virtual QString getType() const = 0;

    //! Set typee of the node
    /*!
      \param type to be assigned to the node
    */
    virtual void    setType(QString type) = 0;

    //! check if the node has a father
    /*!
      \param id of the father node
      \return Boolean result
    */
    virtual bool    isDescendantOf(int parent) = 0;
    virtual bool    isDescendantOf(TreeData* parent) = 0;

    //! check if the user is admin on this or fathers node
    /*!
      \param id of user to test
      \return Boolean result
    */
    virtual bool    canChange() = 0;

protected:
    inline TreeData(quint32 _nodeId, TreeDataPlugin* _plugin) : Data(_plugin) { nodeId = _nodeId; }

    quint32         nodeId;
};

Q_DECLARE_INTERFACE(TreeData, "net.horus.TreeData/1.0");

#endif // TREEDATA_H
