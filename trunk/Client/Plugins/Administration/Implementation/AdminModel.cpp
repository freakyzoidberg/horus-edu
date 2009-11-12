#include "AdminModel.h"

AdminModel::AdminModel(const QHash<quint32, UserData*>&  _users, TreeData *root) : users(_users)
{
	rootItem = root;
}

int AdminModel::columnCount ( const QModelIndex & ) const
{
    return 1;
}

int AdminModel::rowCount ( const QModelIndex & parent ) const
{
	// if invalid, parent is the parent of the rootElement, so only the rootElement in child
	if ( ! parent.isValid())
		return 1;

	// if parent is not a TreeData*, it's a UserData, so there's no child
	TreeData* node = qobject_cast<TreeData*>((Data*)(parent.internalPointer()));
	if ( ! node)
		return 0;

	int nbUsers = 0;

	// count the number of children in this node
	foreach (UserData* user, users)
		if (user->level() > 1 && user->node() == node)
			nbUsers++;

	// return the number of the node's children + the number of users in this node
	return node->children().count() + nbUsers;
}

QVariant AdminModel::headerData (int section, Qt::Orientation orientation, int role) const
{
   if (role == Qt::DisplayRole)
        return QVariant("Administration Tree");
   return QVariant();
}

QVariant AdminModel::data ( const QModelIndex & index, int role ) const
{
    if ( ! index.isValid())
        return QVariant();

	if (role == Qt::BackgroundColorRole)
        return QVariant();

        return ((Data*)(index.internalPointer()))->data(index.column(), role);
}

QModelIndex AdminModel::index ( int row, int column, const QModelIndex & parent ) const
{
	// if invalid, parent is the parent of the rootElement, so only the rootElement in child
	if ( ! parent.isValid())
		return createIndex(row, column, rootItem);

	TreeData* node = qobject_cast<TreeData*>((Data*)(parent.internalPointer()));

	// should not happen
	if ( ! node)
		return QModelIndex();

	// if the row corespond to a TreeData
	if (row < node->children().count())
		return createIndex(row, column, node->children().at(row));

	int pos = 0;
	foreach (UserData* user, users)
            if (user->node() == node && user->level() > 1)
            {
			if (pos == row - node->children().count())
                            return createIndex(row, column, user);
			pos++;
            }

	//should not happen
	return QModelIndex();
}

QModelIndex AdminModel::parent ( const QModelIndex & index ) const
{
	//should not happen
	if ( ! index.isValid())
		return QModelIndex();

	TreeData* node = qobject_cast<TreeData*>((Data*)(index.internalPointer()));
	// if index is a node
	if (node)
	{
		//if index is the rootElement
		if (node == rootItem)
			return QModelIndex();

		// the node is the parent
		node = (TreeData*)(node->parent());
	}
	else
		node = ((UserData*)(index.internalPointer()))->node();

	// if the parent is the root item
	if (node == rootItem)
            return createIndex(0, 0, rootItem);

	return createIndex(node->parent()->children().indexOf(node), 0, node);
}
