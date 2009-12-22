#ifndef				__STRUCTUREELEMENT_H__
# define			__STRUCTUREELEMENT_H__

# include			<QWidget>

# include			"../../../../Common/TreeDataPlugin.h"
# include			"StructureForm.h"

class				StructureElement : public QWidget
{
	Q_OBJECT

public:
	StructureElement(QWidget *parent, TreeDataPlugin *treeDataPlugin);
	void			setForm(StructureForm *form);
	virtual void	update() = 0;

protected:
	virtual	void	editElement() = 0;
	virtual	void	removeElement() = 0;
	virtual void	validateElement() = 0;
	StructureForm	*_form;
	TreeDataPlugin	*_treeDataPlugin;

private slots:
	void			disable();
	void			edit();
	void			remove();
	void			validateForm();

signals:
	void			disabled();
	void			enabled();
};

Q_DECLARE_INTERFACE(StructureElement, "net.horus.StructureElement/1.0");

#endif //			__STRUCTUREELEMENT_H__
