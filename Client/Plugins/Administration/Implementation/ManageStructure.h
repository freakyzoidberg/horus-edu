#ifndef					__MANAGESTRUCTURE_H__
# define				__MANAGESTRUCTURE_H__

# include				<QWidget>

# include				<QBoxLayout>
# include				<QPushButton>

# include				"../../../../Common/TreeDataPlugin.h"
# include				"../../../../Common/UserDataPlugin.h"
# include				"StructureElement.h"

class					ManageStructure : public QWidget
{
	Q_OBJECT

public:
	ManageStructure(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin);

private slots:
	void				schoolEnabled();
	void				schoolDisabled();
	void				classEnabled();
	void				classDisabled();
	void				subjectEnabled();
	void				subjectDisabled();

private:
	StructureElement	*school;
	StructureElement	*classes;
	StructureElement	*subjects;
	QBoxLayout			*leftLayout;
	QPushButton			*addSchoolButton;
	QPushButton			*editSchoolButton;
	QPushButton			*removeSchoolButton;
	QPushButton			*addClassButton;
	QPushButton			*editClassButton;
	QPushButton			*removeClassButton;
	QPushButton			*addSubjectButton;
	QPushButton			*editSubjectButton;
	QPushButton			*removeSubjectButton;
};

#endif //				__MANAGESTRUCTURE_H__
