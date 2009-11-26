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
#ifndef IPDFFILE_H
#define IPDFFILE_H

#include <QObject>
#include <QImage>

class   IPdfRendering
{

    public:

    //! display a part of a pdf file
    /*
    \param fileName the absolute path  to the file
    \param page the page you want to display
    \param partToDisplay the part of the page you want to display
    \return a pointer to the diaplayable image
    */
      virtual QImage    *PdfDisplayerDoc(const QString & fileName, int page,
                                    QRectF *partToDisplay, int fileId = -1) = 0;

    //! display a part of a pdf file (overload)
    /*
    \param fileId the file identifier
    \param page the page you want to display
    \param partToDisplay the part of the page you want to display
    \return a pointer to the diaplayable image
    */
     virtual QImage    *PdfDisplayerDoc(quint32 fileId, int page, QRectF *partToDisplay) = 0;
     virtual QImage    *PdfDisplayerDoc(const QString & fileName, int page) = 0;

    /*!
      Close a pdf file and remove it from the map. When the name has been
      resolved from the id it calls the closePdfFile(const QString &)
      \param fileId the id of the file.
    */
     virtual void    closePdfFile(int fileId) = 0;
};

Q_DECLARE_INTERFACE(IPdfRendering, "net.horus.Client.PdfRenderingInterface/1.0");

#endif // IPDFFILE_H
