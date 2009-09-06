#ifndef TREEDATA_H
#define TREEDATA_H

#include <QHash>
#include <QString>

#include "Data.h"
#include "TreeDataPlugin.h"

class UserData;
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
    //! create child
    /*!
      add son node attached on the current node (this)

      \param name name of node
      \param type type of the node
      \param user the user in charge of this node
      \return the inserted node
    */
    virtual TreeData* createChild(const QString name, const QString type, UserData* user) = 0;
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
    virtual void    moveTo(TreeData* parent) = 0;


    //! Get name of node
    /*!
      \return name of the node
    */
    virtual const QString name() const = 0;
    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    virtual void    setName(const QString name) = 0;


    //! Get id of node
    /*!
      \return id of the node
    */
    inline int     id() const { return _id; }


    //! Get User in charge of the node
    /*!
      \return user id of the referree of the node
    */
    virtual UserData* user() const = 0;
    //! Set User in charge of the node
    /*!
      \param userref new user in charge of the node
      \return Boolean state of the change userref
    */
    virtual void    setUser(UserData* user) = 0;


    //! Get type the node
    /*!
      \return user value of type
    */
    virtual const QString type() const = 0;
    //! Set typee of the node
    /*!
      \param type to be assigned to the node
    */
    virtual void    setType(const QString type) = 0;


    //! check if the node has a father
    /*!
      \param id of the father node
      \return Boolean result
    */
    virtual bool    isDescendantOf(TreeData* parent) = 0;

    
protected:
    inline TreeData(quint32 id, TreeDataPlugin* plugin) : Data(plugin) { _id = id; }

    quint32         _id;
};

Q_DECLARE_INTERFACE(TreeData, "net.horus.TreeData/1.0");

#endif // TREEDATA_H
