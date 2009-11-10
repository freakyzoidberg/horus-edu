#include	"AdminMainFrame.h"

#include	"AdminTree.h"
#include	"UserPage.h"
#include	"RoomPage.h"
#include	"AbsenceFrame.h"
#include	"NoteFrame.h"
#include	"BulletinFrame.h"

AdminMainFrame::AdminMainFrame(TreeDataPlugin *tree, UserDataPlugin *user) : QTabWidget()
{
	this->addTab(new AdminTree(tree, user), QIcon(":/images/Tree.png"), tr("Tree View"));
	this->addTab(new UserPage(tree, user), QIcon(":/images/User Group.png"), tr("Users"));
	this->addTab(new RoomPage(tree), QIcon(":/images/Clipboard.png"), tr("Manage Files"));
	this->addTab(new AbsenceFrame(), QIcon(":/images/pasla.png"), tr(" Absences "));
	this->addTab(new NoteFrame(), QIcon(":/images/notes.png"), tr(" Notes "));
	this->addTab(new BulletinFrame(), QIcon(":/images/bull.png"), tr(" Bulletins "));
}
