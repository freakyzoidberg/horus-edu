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
    bool UpdateVector();
    void ShowSons();
    Tree *GetParent() const;
    static Tree* GetNodebyId(int id);
};

#endif // TREE_H
