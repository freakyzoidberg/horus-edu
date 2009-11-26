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
#ifndef IPDFRENDERING_H
#define IPDFRENDERING_H

#include "poppler/include/poppler-qt4.h"
#include <QRectF>
#include <QImage>

//! Class of the API used to render PDF files
/*!
    This class contains methods allowing to render a PDF virtual
    All of them are pure virtual. Modules using PDF files must
    implement this class

    Maybe some methods can be delete, im not sure right now
*/
class   IPdfFile
{
 public:

    //! return the name of the PDF file
    virtual const QString & getFileName() const = 0;

    //! return the poppler document
    /*!
      \return the variable pdfDoc;
    */
    virtual const Poppler::Document    *getPdfDoc() const = 0;

    //! return the current page
    virtual const Poppler::Page         *getPage() const = 0;

    //! return the number of the current page
    virtual int   getCurrentPageNumber() const = 0;

    //! open the pdfFile
    virtual bool        openFile() = 0;

    //! close the pdfFile
    virtual void        closeFile() = 0;

    //! reload the file
    virtual void        reloadFile() = 0;

    //! set one from the pdf document, check if the page is not out of range
    /*!
      \param pageNb the number of the page you wanna load
    */
    virtual bool        loadPage(unsigned int pageNb) = 0;

    //! return the scaleFactor
    virtual float       getScaleFactor() const = 0;

    //! create the picture of the PDF, not finished. (need a solution to
    //! pass this image to the "core")
    virtual QImage    *render(int page, QRectF *partToDisplay) = 0;
    virtual QImage    *render(int page) = 0;

    //! modification of the scale factor, used when user zoom
    /*!
      \param scaleFactor the new scaleFactor
    */
    virtual void    scaled(float scaleFactor) = 0;
};

#endif // IPDFRENDERING_H
