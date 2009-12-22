#ifndef						__ELEMENTSUBJECT_H__
# define					__ELEMENTSUBJECT_H__

# include					"StructureElement.h"

# include					<QSortFilterProxyModel>
# include					<QListView>

class						ElementSubject : public StructureElement
{
	Q_OBJECT

public:
	ElementSubject(QWidget *parent, TreeDataPlugin *treeDataPlugin);
	void					update();
	void					setClass(TreeData *node);
	QSortFilterProxyModel	*classFilter;
	QSortFilterProxyModel	*subjectFilter;

protected:
	void					addElement();
	void					editElement();
	void					removeElement();
	void					validateElement();

private:
	QListView				*subjectListView;
	TreeData				*editing;
	TreeData				*_class;

private slots:
	void					subjectSelected(const QItemSelection &selected, const QItemSelection &);
};

#endif //					__ELEMENTSUBJECT_H__
