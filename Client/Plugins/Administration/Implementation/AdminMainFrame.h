#ifndef ADMINMAINFRAME_H
#define ADMINMAINFRAME_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include "UserForm.h"
#include "RoomPage.h"
#include "AdminTree.h"

//class Administration;
class AdminMainFrame : public QWidget
{
    Q_OBJECT

public:
    AdminMainFrame(TreeDataPlugin *_treePlugin, UserDataPlugin *_userPlugin);
    ~AdminMainFrame();
public slots:
    void changeFrame(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();
    QListWidget *contentsWidget;
    QStackedWidget *framesWidget;
    TreeDataPlugin      *tree;
    UserDataPlugin      *users;
};

#endif // ADMINMAINFRAME_H
