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
#ifndef __PDFDISPLAYER_H__
# define __PDFDISPLAYER_H__

# include <QStringList>
# include <QObject>
# include <QMap>
# include <QRectF>
# include "poppler/include/poppler-qt4.h"

# include "../../../../Common/Plugin.h"
# include "../../../../Common/FileDataPlugin.h"

# include "../IPdfFile.h"
# include "../IPdfRendering.h"
# include "PdfFile.h"

//! This plugin is used to render a PDF file
/*
  To have more informations about horus plugins, see the plugin tesPlugin <-------- outdated information
*/

class PdfDisplayer : public Plugin, public IPdfRendering
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IPdfRendering)

public:
    //! set some values
    PdfDisplayer();

    //! free pNetwork
    ~PdfDisplayer();

    //! Return the name of the plugin.
    /*!
      \return the variable name
    */
    const QString        pluginName() const;

    //! Return the version of the plugin
    /*!
      \return the variable version
    */
    const QString        pluginVersion() const;

//    bool    PluginEventHandler(QEvent *event);

    //! return the map containing all the PDF files
    /*
      \return the variable renderPdf
    */
    const QMap<quint32, IPdfFile *>    *getAllPdfFiles() const;

    //! display a part of a pdf file
    /*
    \param fileName the absolute path  to the file
    \param page the page you want to display
    \param partToDisplay the part of the page you want to display
    \return a pointer to the diaplayable image
    */
    QImage    *PdfDisplayerDoc(const QString & fileName, int page, QRectF *partToDisplay, int fileId = -1);

    //! display a part of a pdf file (overload)
    /*
    \param fileId the file identifier
    \param page the page you want to display
    \param partToDisplay the part of the page you want to display
    \return a pointer to the diaplayable image
    */
     QImage    *PdfDisplayerDoc(quint32 fileId, int page, QRectF *partToDisplay);

     //!for convenience
     QImage    *PdfDisplayerDoc(const QString & fileName, int page);

    /*!
      Close a pdf file and remove it from the map. When the name has been
      resolved from the id it calls the closePdfFile(const QString &)
      \param fileId the id of the file.
    */
    void    closePdfFile(int fileId);

private:
    //! QMap containing all the open PDF files with their name
    QMap<quint32, IPdfFile *>   *pdfFiles;
};

#endif // __PDFDISPLAYER_H__
