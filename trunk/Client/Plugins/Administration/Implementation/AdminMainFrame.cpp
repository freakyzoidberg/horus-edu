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
    contentsWidget->setMaximumWidth(82);
    contentsWidget->setSpacing(2);
    contentsWidget->setUniformItemSizes(true);

    framesWidget = new QStackedWidget;
    framesWidget->addWidget(new StudentsPage(tree, users));
    framesWidget->addWidget(new TeacherPage(tree, users));
    framesWidget->addWidget(new RoomPage(tree));

    createIcons();
    contentsWidget->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(framesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Administration"));
}

void AdminMainFrame::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/User Group.png"));
    configButton->setText(tr("Students"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget);
    updateButton->setIcon(QIcon(":/images/Administrator.png"));
    updateButton->setText(tr("Teachers"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget);
    queryButton->setIcon(QIcon(":/images/Clipboard.png"));
    queryButton->setText(tr("Classroom"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

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
