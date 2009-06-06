#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H

#include                <QSplitter>
#include                <QModelIndex>
#include                <QAbstractItemModel>
#include                <QTreeView>

#include                "../../IFileManager.h"
#include                "../LessonManager/ILessonManager.h"
#include                "../TreeManagement/ITreePlugin.h"


class                   CourseWidget : public QSplitter
{
    Q_OBJECT

public:
                        CourseWidget(ILessonManager *lessonManager, ITreePlugin *treePlugin, IFileManager *fileManager);

private:
    void                buildCategoryTree();
    void                buildLessonTree();

private slots:
    void lessonSelected(const QModelIndex &item);
    void pageSelected(const QModelIndex &item, const QModelIndex &olditem);
    void ready();

private:
    ILessonManager      *lessonManager;
    ITreePlugin         *treePlugin;
    IFileManager        *fileManager;
    QAbstractItemModel  *categoryModel;
    QAbstractItemModel  *lessonModel;
    QTreeView           *categoryView;
    QTreeView           *lessonView;
    QWidget             *pageWidget;
    quint32             fileIndex;
    IFile               *lessonFile;

};
#endif // COURSEWIDGET_H
