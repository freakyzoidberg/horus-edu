#ifndef TREE_H
#define TREE_H

#include <QVariant>
#include <QHash>
#include <QVector>
#include <QString>

#include "../ITree.h"

class Tree : public ITree
{
  Q_OBJECT

public:
    static Tree*      getNodeById(int id);
    static inline int countNodes() { return maptree.count(); }
    static void       updateUserTree();
    static void       receiveUserTree(const QVariantList& response);
//private:
    static QHash<int,Tree*> maptree;


public slots:
    void              receiveUpdate(const int _id, Tree* _parent, const int _user_ref, const QString _name, const QString _type, const QVector<ITree*> _sons);
signals:
    void              updated();


public:
    inline bool       isLoaded() const { return loaded; }
    //! insert node
    /*!
      add son node attached on the current node (this)

      \param name name of node
      \param user_ref id of the user in charge of this node
      \param type type of the node
      \return the id of the inserted node
    */
    void              createChild(int userId, QString name, QString type);
    //! delete node
    /*!
      delete current node node and attache sons to the  father's current node
    */
    void              remove();
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    void              moveTo(int parent);
    //! move node to new father
    /*!
      \param idmove node to move
      \param idfather node id of new father
    */
    void              moveTo(ITree* parent);

    //! Get name of node
    /*!
      \return name of the node
    */
    inline QString    getName() const { return name; }
    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    void              setName(QString name);

    //! Get type the node
    /*!
      \return user value of type
    */
    QString getType() const { return type; }

    //! Set typee of the node
    /*!
      \param type to be assigned to the node
    */
    void    setType(QString type);

    //! Get id of node
    /*!
      \return id of the node
    */
    inline int        getId() const { return id; }

    //! Get User in charge of the node
    /*!
      \return user id of the referree of the node
    */
    inline int        getUserId() const { return userId; }

    //! Set User in charge of the node
    /*!
      \param userref new user in charge of the node
      \return Boolean state of the change userref
    */
    void              setUserId(int user);

    //! check if the node has a father
    /*!
      \param id of the father node
      \return Boolean result
    */
    bool              isDescendantOf(int parent);
    bool              isDescendantOf(ITree* parent);

    //! check if the user is admin on this or fathers node
    /*!
      \param id of user to test
      \return Boolean result
    */
    bool              canChange();

private:
    inline            Tree(int _id) { id=_id; userId=0; setParent(this); name="Loading..."; loaded=false; }
    inline            ~Tree() {}
    int               id;
    int               userId;
    QString           type;
    QString           name;
    bool              loaded;
};

#endif // TREE_H
