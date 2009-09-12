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

class                   CourseWidget : public QSplitter
{
    Q_OBJECT

public:
                        CourseWidget(ILessonManager *lessonPlugin, TreeDataPlugin *treePlugin, FileDataPlugin *filePlugin);

private:
    void                buildCategoryTree();

private slots:
    void lessonSelected(const QModelIndex &item);
    void pageSelected(const QModelIndex &item);
    void ready();

private:
    ILessonManager      *lessonPlugin;
    TreeDataPlugin      *treePlugin;
    FileDataPlugin      *filePlugin;
    QAbstractItemModel  *categoryModel;
    QTreeView           *categoryView;
    QWidget             *pageWidget;
    quint32             fileIndex;
    FileData            *lessonFile;
    ILesson::IPage *oldpage;
};

#endif // __COURSEWIDGET_H__
