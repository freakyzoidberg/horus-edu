#ifndef __COURSEWIDGET_H__
# define __COURSEWIDGET_H__

# include               <QSplitter>
# include               <QModelIndex>
# include               <QAbstractItemModel>
# include               <QTreeView>

# include               "../../LessonManager/ILessonManager.h"
# include				"../../../../Common/TreeDataPlugin.h"
# include				"../../../../Common/FileDataPlugin.h"
# include				"../../../../Common/FileData.h"
#include  "WhiteBoard.h"
#include  "Items.h"

class                   CourseWidget : public QSplitter
{
    Q_OBJECT

public:
                        CourseWidget(ILessonManager *lessonPlugin, TreeDataPlugin *treePlugin, FileDataPlugin *filePlugin);

private:
    void                buildCategoryTree();


private slots:
    void lessonSelected(const QModelIndex &item);

private:
    ILessonManager      *lessonPlugin;
    TreeDataPlugin      *treePlugin;
    FileDataPlugin      *filePlugin;
    QAbstractItemModel  *categoryModel;
    QTreeView           *categoryView;
    WhiteBoard             *pageWidget;
    quint32             fileIndex;
    FileData            *lessonFile;
};

#endif // __COURSEWIDGET_H__
