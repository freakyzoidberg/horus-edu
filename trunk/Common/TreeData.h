/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef TREEDATA_H
#define TREEDATA_H

#include <QHash>
#include <QString>

#include "Data.h"
#include "TreeDataPlugin.h"

class UserData;
class TreeData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

public:
    //! create child
    /*!
      add son node attached on the current node (this)

      \param name name of node
      \param type type of the node
      \param user the user in charge of this node
      \return the inserted node
    */
    virtual TreeData* createChild(const QString name, const QString type, UserData* user) = 0;


    //! Get name of node
    /*!
      \return name of the node
    */
    virtual const QString name() const = 0;
    //! Set name of node
    /*!
      \param name new name for the corresponding node
      \return Boolean state of the name change
    */
    virtual void    setName(const QString name) = 0;


    //! Get id of node
    /*!
      \return id of the node
    */
	virtual quint32  id() const = 0;


    //! Get User in charge of the node
    /*!
      \return user id of the referree of the node
    */
    virtual UserData* user() const = 0;
    //! Set User in charge of the node
    /*!
      \param userref new user in charge of the node
      \return Boolean state of the change userref
    */
    virtual void    setUser(UserData* user) = 0;


    //! Get type the node
    /*!
      \return user value of type
    */
    virtual const QString type() const = 0;
    //! Set typee of the node
    /*!
      \param type to be assigned to the node
    */
    virtual void    setType(const QString type) = 0;

	virtual TreeData*			parent() const = 0;
	virtual void				setParent(TreeData*) = 0;
	virtual const QList<TreeData*>&	children() const = 0;

    //! check if the node has a father
    /*!
      \param id of the father node
      \return Boolean result
    */
    virtual bool    isDescendantOf(TreeData* parent) = 0;

    
	inline void		registerData(Data* data) { _registeredData.append(data); connect(this, SIGNAL(removed()), data, SLOT(remove())); }
template <typename T>
	inline T		registeredData() const
	{
		foreach (Data* data, _registeredData)
			if (T ret = qobject_cast<T>( data ))
				return ret;
		return 0;
	}
private:
	QList<Data*>	_registeredData;

protected:
	inline			TreeData(TreeDataPlugin* plugin) : Data(plugin) { }
	virtual inline	~TreeData() {}
};

#ifdef HORUS_SERVER
typedef TreeData ServerTreeData;
Q_DECLARE_INTERFACE(ServerTreeData, "net.horus.ServerTreeData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef TreeData ClientTreeData;
Q_DECLARE_INTERFACE(ClientTreeData, "net.horus.ClientTreeData/1.0");
#endif

#endif // TREEDATA_H
