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
    QMap<int, Tree*> sons;
    static QMap<int, Tree*> maptree;

public:
    Tree();
    ~Tree();
    bool UpdateVector();
    static Tree* GetNodebyId(int id);
};

#endif // TREE_H
