#ifndef TreeFrame_H
#define TreeFrame_H

//#include "ui_TreeFrame.h"
#include <QHash>
#include <QVariant>
#include <QTreeWidgetItem>
#include "../../../../Common/NetworkPlugin.h"

class TreeFrame : public QTreeWidget
{ 
    Q_OBJECT
    Q_DISABLE_COPY(TreeFrame)

    typedef void (TreeFrame::*requestFunction)(QVariantHash& response);

    public:
            TreeFrame();
        void        readResponse(QVariantHash response);
    protected:
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
        /*! called by AdministrationFrame */
        QHash<QByteArray,requestFunction> requestFunctions;

};

#endif // TreeFrame_H
