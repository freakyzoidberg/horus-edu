#ifndef						__ELEMENTCLASS_H__
# define					__ELEMENTCLASS_H__

# include					"StructureElement.h"

# include					<QSortFilterProxyModel>
# include					<QListView>

class						ElementClass : public StructureElement
{
	Q_OBJECT

public:
	ElementClass(QWidget *parent, TreeDataPlugin *treeDataPlugin);
	void					update();
	QListView				*classListView;
	QSortFilterProxyModel	*classesFilter;

protected:
	void					addElement();
	void					editElement();
	void					removeElement();
	void					validateElement();

private:
	TreeData				*editing;

private slots:
	void					classSelected(const QItemSelection &selected, const QItemSelection &);
};

#endif //					__ELEMENTCLASS_H__
