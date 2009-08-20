#ifndef TREEWIDGETITEM_H
#define TREEWIDGETITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QTreeWidget>

class   TreeWidgetItem : public QTreeWidgetItem
{
    public:
        TreeWidgetItem(QTreeWidget *, QObject *);
        TreeWidgetItem(TreeWidgetItem *, QObject *);
        ~TreeWidgetItem();

        int     getPageBegin();
        int     getPageEnd();
        double  getPosYBegin();
        double  getPosYEnd();
        double  getPosXBegin();
        double  getPosXEnd();

        void    setPageBegin(int);
        void    setPageEnd(int);
        void    setPosYBegin(double);
        void    setPosYEnd(double);
        void    setPosXBegin(double);
        void    setPosXEnd(double);

    private:
        QObject     *parent;

        int     pageBegin, pageEnd;
        double  posYBegin, posYEnd;
        double  posXBegin, posXEnd;

};

#endif // TREEWIDGETITEM_H
