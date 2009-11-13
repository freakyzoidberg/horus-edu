#include	"AdminMainFrame.h"

#include	"AdminTree.h"
#include	"UserPage.h"
#include	"RoomPage.h"
#include	"AbsenceFrame.h"
#include	"NoteFrame.h"
#include	"BulletinFrame.h"

AdminMainFrame::AdminMainFrame(TreeDataPlugin *tree, UserDataPlugin *user, EventDataPlugin *event) : QTabWidget()
{
	this->addTab(new UserPage(tree, user), QIcon(":/images/User Group.png"), tr("Users"));
	this->addTab(new RoomPage(tree), QIcon(":/images/Clipboard.png"), tr("Manage Files"));
	this->addTab(new AbsenceFrame(tree, user, event), QIcon(":/images/pasla.png"), tr(" Absences "));
	this->addTab(new NoteFrame(tree, user, event), QIcon(":/images/notes.png"), tr(" Notes "));
	this->addTab(new BulletinFrame(tree, user, event), QIcon(":/images/bull.png"), tr(" Bulletins "));
}
