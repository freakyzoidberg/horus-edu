#ifndef TREEMNGT_H
#define TREEMNGT_H
#include <QString>
#include <QByteArray>
#include <Sql.h>
class TreeMngt
{
private:
    typedef struct {
        int id;
        QString name;
        int user_ref;
        int parent_id;
        int *fathernode;
        QMap<int, int> sons;
    } node;
    static QMutex mymute;
    static QMap<int, node> vectree;
public:


    TreeMngt();
    ~TreeMngt();


    //! Get name of node by id
    /*!
      \sa GetName(int idnode)
      \param idnode node id from database
    */
    QString GetName(int idnode) const;

    //! Set name of node by id
    /*!
      \sa SetName(int idnode, QString name)
      \param idnode node id from database
      \param name new name for the corresponding node
    */
    bool SetName(int idnode, QString name);


    //! Get User in charge of the node
    /*!
      \sa GetUserRef(int idnode)
      \param idnode node id from database
    */
    int GetUserRef(int idnode) const;

    //! Set User in charge of the node
    /*!
      \sa SetUserRef(int idnode, int userref)
      \param idnode node id from database
      \param userref new user in charge of the node
    */
    bool SetUserRef(int idnode, int userref);

    //! move node to new father
    /*!
      \sa MoveNode(int idnodetomove, int idnewfather)
      \param idmove node to move
      \param idfather node id of new father
    */
    bool MoveNode(int idmove, int idfather);

    //! insert node
    /*!
      \sa InsertNode(QString name, int userref, int idfather)
      \param name name of father
      \param userref id of the user in charge of this node
      \param idfather if of the node to attach the new one
    */
    int InsertNode(QString name, int userref, int idfather);

    //! Delete node and attach child to first father
    /*!
      \sa DeleteNode(int idnode)
      \param idnode node to remove
    */
    bool DeleteNode(int idnode);

   //! id of the father of the current node
    /*!
      \sa GetFatherNode(int idnode)
      \param idnode node to get infos
    */
    int GetFatherNode(int idnode) const;

    //! id of the sons of the current node
    /*!
      \sa GetSonsNode(int idnode)
      \param idnode node to get infos
    */
    QMap<int, int> GetSonsNode(int idnode) const;

     //! Completely fill vector from db
    /*!
      \sa UpdateVector()
    */
    bool UpdateVector();

    void vecshow(QMap<int, node> vec);
};

#endif // TREEMNGT_H
