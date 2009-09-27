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
    contentsWidget->setMaximumWidth(75);
    contentsWidget->setSpacing(2);
    contentsWidget->setUniformItemSizes(true);

    framesWidget = new QStackedWidget;
    framesWidget->addWidget(new UserForm(tree, users));
    framesWidget->addWidget(new RoomPage(tree));
    framesWidget->addWidget(new AdminTree(tree, users));

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
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/User Group.png"));
    configButton->setText(tr("Students"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/Clipboard.png"));
    queryButton->setText(tr("Classes"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *treeButton = new QListWidgetItem(contentsWidget);
    treeButton->setIcon(QIcon(":/images/Tree.png"));
    treeButton->setText(tr("Tree View"));
    treeButton->setTextAlignment(Qt::AlignHCenter);

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
