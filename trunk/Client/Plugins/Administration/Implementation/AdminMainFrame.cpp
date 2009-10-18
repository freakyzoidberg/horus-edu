#include "AdminMainFrame.h"
#include "Administration.h"
#include "../../../../Common/PluginManager.h"

AdminMainFrame::AdminMainFrame(TreeDataPlugin *_treePlugin, UserDataPlugin *_userPlugin)
    : QWidget()
{
    tree = _treePlugin;
    users = _userPlugin;
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(20, 20));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(80);
    contentsWidget->setSpacing(2);
    contentsWidget->setUniformItemSizes(true);

    framesWidget = new QStackedWidget;
    framesWidget->addWidget(new AdminTree(tree, users));
    framesWidget->addWidget(new UserPage(tree, users));
    framesWidget->addWidget(new RoomPage(tree));
    framesWidget->addWidget(new AbsenceFrame());
    framesWidget->addWidget(new NoteFrame());
    framesWidget->addWidget(new BulletinFrame());

    createIcons();
    contentsWidget->setCurrentRow(0);

    QGridLayout *horizontalLayout = new QGridLayout(this);
    horizontalLayout->addWidget(contentsWidget, 0, 0);
    horizontalLayout->addWidget(framesWidget, 0, 1);
//    setLayout(mainLayout);

    setWindowTitle(tr("Administration"));
}

void AdminMainFrame::createIcons()
{
    QListWidgetItem *treeButton = new QListWidgetItem(contentsWidget);
    treeButton->setIcon(QIcon(":/images/Tree.png"));
    treeButton->setText(tr("Tree View"));
    treeButton->setTextAlignment(Qt::AlignHCenter);

    QListWidgetItem *userButton = new QListWidgetItem(contentsWidget);
    userButton ->setIcon(QIcon(":/images/User Group.png"));
    userButton ->setText(tr("Users"));
    userButton ->setTextAlignment(Qt::AlignHCenter);
    userButton ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/Clipboard.png"));
    queryButton->setText(tr("Manage Files"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *absButton = new QListWidgetItem(contentsWidget);
    absButton->setIcon(QIcon(":/images/pasla.png"));
    absButton->setText(tr(" Absences "));
    absButton->setTextAlignment(Qt::AlignHCenter);
    absButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *noteButton = new QListWidgetItem(contentsWidget);
    noteButton->setIcon(QIcon(":/images/notes.png"));
    noteButton->setText(tr(" Notes "));
    noteButton->setTextAlignment(Qt::AlignHCenter);
    noteButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *bullButton = new QListWidgetItem(contentsWidget);
    bullButton ->setIcon(QIcon(":/images/bull.png"));
    bullButton ->setText(tr(" Bulletins "));
    bullButton ->setTextAlignment(Qt::AlignHCenter);
    bullButton ->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


    treeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changeFrame(QListWidgetItem *, QListWidgetItem*)));
}

void AdminMainFrame::changeFrame(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    framesWidget->setCurrentIndex(contentsWidget->row(current));
}

AdminMainFrame::~AdminMainFrame()
{

}
