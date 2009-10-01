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

# include				"WhiteBoard.h"
# include				"Items.h"

class                   CourseWidget : public QSplitter
{
    Q_OBJECT

public:
						CourseWidget(QWidget *parent, WhiteBoardData *wbd, PluginManager *pluginManager);

private:
    void                buildCategoryTree();


private slots:
	void contextMenu(const QPoint& point);

private:
    ILessonManager      *lessonPlugin;
    TreeDataPlugin      *treePlugin;
	WhiteBoardDataPlugin *whiteboardPlugin;
    QAbstractItemModel  *categoryModel;
    QTreeView           *categoryView;
	WhiteBoard          *pageWidget;
    quint32             fileIndex;
    FileData            *lessonFile;
	static QIcon		*lessonIcon;
	static QIcon		*sectionIcon;
	static QIcon		*documentIcon;
};

#endif // __COURSEWIDGET_H__
