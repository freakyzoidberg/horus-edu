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
    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    bool SetName(QString name);

    static Tree* GetNodebyId(int id);
};

#endif // TREE_H
