#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H

#include                <QSplitter>
#include                <QModelIndex>
#include                <QAbstractItemModel>
#include                <QTreeView>

#include                "../FileManagement/IFileManagement.h"
#include                "../LessonManager/ILessonManager.h"
#include                "../TreeManagement/ITreePlugin.h"


class                   CourseWidget : public QSplitter
{
    Q_OBJECT

public:
                        CourseWidget(ILessonManager *lessonManager, ITreePlugin *treePlugin, IFileManagement *fileManagement);

private:
    void                buildCategoryTree();
    void                buildLessonTree();

private slots:
    void lessonSelected(const QModelIndex &item);
    void pageSelected(const QModelIndex &item);
    void ready();

private:
    ILessonManager      *lessonManager;
    ITreePlugin         *treePlugin;
    IFileManagement     *fileManagement;
    QAbstractItemModel  *categoryModel;
    QAbstractItemModel  *lessonModel;
    QTreeView           *categoryView;
    QTreeView           *lessonView;
    QWidget             *pageWidget;
    quint32             fileIndex;
    IFile               *lessonFile;
    ILesson::IPage *oldpage;
};
#endif // COURSEWIDGET_H
