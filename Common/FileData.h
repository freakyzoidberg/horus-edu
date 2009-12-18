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
#ifndef FILEDATA_H
#define FILEDATA_H

#include "Data.h"
#include "FileDataPlugin.h"
#include <QFile>
class UserData;
class TreeData;
#define TRANSFERT_BUFFER_SIZE 32768

class FileData : public Data
{
  Q_OBJECT
#ifdef HORUS_SERVER
  Q_INTERFACES(ServerData)
#endif
#ifdef HORUS_CLIENT
  Q_INTERFACES(ClientData)
#endif

protected:
    inline FileData(FileDataPlugin* plugin) : Data(plugin) { }
	virtual inline ~FileData() {}

public:
    virtual quint32     id() const = 0;

    virtual QString     name() const = 0;
    virtual void        setName(const QString name) = 0;

    virtual UserData*   owner() const = 0;

    virtual TreeData*   node() const = 0;
    virtual void        moveTo(TreeData* node) = 0;

    virtual QString     mimeType() const = 0;
	virtual void        setMimeType(const QString name) = 0;

	virtual QString     keyWords() const = 0;
	virtual void        setKeyWords(const QString keyWords) = 0;

	virtual QByteArray  hash() const = 0;
	virtual quint64		size() const = 0;

	virtual QString		fileName() const = 0;

#ifdef HORUS_CLIENT
    //! return true if the file is downloaded in local
    virtual bool    isDownloaded() const = 0;
public slots:
	//! download the file from the server.
	virtual void  download() = 0;
	//! upload the file to the server.
    virtual void  upload() = 0;

signals:
    //! emitted when the localfile just finish downloading
    void downloaded();
    //! emitted when the localfile just finish uploading
    void uploaded();
#endif
};

#ifdef HORUS_SERVER
typedef FileData ServerFileData;
Q_DECLARE_INTERFACE(ServerFileData, "net.horus.ServerFileData/1.0");
#endif
#ifdef HORUS_CLIENT
typedef FileData ClientFileData;
Q_DECLARE_INTERFACE(ClientFileData, "net.horus.ClientFileData/1.0");
#endif

#endif // FILEDATA_H
