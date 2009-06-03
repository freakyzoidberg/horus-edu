#ifndef TREEFRAM_H
#define TREEFRAM_H

#include "ui_TreeFram.h"
#include <QHash>
#include <QVariant>
 #include <QTreeWidgetItem>

class TreeFram : public QFrame, private Ui::TreeFram
{ 
    Q_OBJECT
    Q_DISABLE_COPY(TreeFram)

    typedef void (TreeFram::*requestFunction)(QVariantHash& response);

    public:
        explicit    TreeFram(QWidget *parent = 0);
        void        readResponse(QVariantHash response);
    protected:
        virtual void changeEvent(QEvent *e);
    protected slots:
        void            itemClicked(QTreeWidgetItem*, int);
    private:
        //TreeManager tM;
        //TreeManager(Administration *parent);
        void            getTree();
        void            getTreeResponse(QVariantHash &response);
        void            getNodInfo();
        void            getNodInfoResponse(QVariantHash &response);
        void            deleteNode(QString idNode);
        void            moveNode(QString from, QString to);
        void            editNode(QString id, QString type, QString name, QString userId);
        void            editNodeResponse(QVariantHash &response);
        void            unknownResponse(QVariantHash &response);
        void            updateTree(QVariantHash tree);
        //Administration  *parent;
        //! functions for each request
        /*! called by AdminFram */
        QHash<QByteArray,requestFunction> requestFunctions;
};

#endif // TREEFRAM_H
