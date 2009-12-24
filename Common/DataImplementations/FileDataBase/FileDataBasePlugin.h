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
#ifndef FILEDATABASEPLUGIN_H
#define FILEDATABASEPLUGIN_H


#include <QHash>
#include "../../FileDataPlugin.h"

class Data;
class FileData;
class FileDataBase;
class FileServer;
class FileDataBasePlugin : public FileDataPlugin
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerFileDataPlugin)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientFileDataPlugin)
#endif

  friend class FileDataBase;

// Plugin Interface
public:
	inline const QString	pluginName() const { return "File Data Base"; }
	inline const QString	pluginVersion() const { return "0.1"; }
	void					load();
	void					unload();
	bool					canLoad() const;


// DataPlugin Interface
public:
#ifdef HORUS_CLIENT
	void					dataHaveNewKey(Data*d, QDataStream& s);
	QAbstractListModel*		listModel() const;
#endif
protected:
    //! Return the pointer to the Data with a his unique key read in the stream
	Data*					dataWithKey(QDataStream& s);


// FileDataPlugin Interface
public:
	FileData*				file(quint32 fileId);
	QList<FileData*>		filesInNode(quint32 nodeId) const;
	QList<FileData*>		filesInNode(const TreeData *node) const;
	QList<FileData*>		filesInNodeAndUser(quint32 nodeId, quint32 userId) const;
	QList<FileData*>		filesInNodeAndUser(const TreeData *node, const UserData* user) const;
	FileData*				createFile();

#ifdef HORUS_SERVER
private:
	FileServer*					_server;
#endif
public:
	FileDataBasePlugin();
};

#endif // FILEDATABASEPLUGIN_H
