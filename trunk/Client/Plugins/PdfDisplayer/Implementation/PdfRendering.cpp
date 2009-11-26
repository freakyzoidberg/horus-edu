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
#include "PdfRendering.h"

#include <QPainter>
#include <QMatrix>
#include <QRect>
#include <QPainter>
#include <QDebug>

PdfRendering::PdfRendering(const QString & fileName, int fileId)
{
    this->fileName = fileName;
    this->fileId = fileId;

    pdfDoc = NULL;
    currentPage = NULL;
    currentPageNb = 1;
    scaleFactor = 1;
    matrix = NULL;

    openFile();
    if (pdfDoc)
      loadPage(currentPageNb);
}

PdfRendering::~PdfRendering()
{
    closeFile();
    if (matrix)
        delete matrix;
}

const QString & PdfRendering::getFileName() const
{
    return fileName;
}

int     PdfRendering::getFileId() const
{
    return fileId;
}

const Poppler::Document    *PdfRendering::getPdfDoc() const
{
    return  pdfDoc;
}

const Poppler::Page         *PdfRendering::getPage() const
{
    return currentPage;
}

int   PdfRendering::getCurrentPageNumber() const
{
    return  currentPageNb;
}

bool        PdfRendering::openFile()
{
    if (pdfDoc != NULL)
    {
        qDebug() << "File already opened";
        return true;
    }

    pdfDoc = Poppler::Document::load(fileName);
    if (pdfDoc == NULL)
    {
        qDebug() << "An error occured: cannot open pdf file";
        return false;
    }
    qDebug() << "pdf file successfully opened";
    return true;
}

void        PdfRendering::closeFile()
{
    if (pdfDoc != NULL)
    {
       if (currentPage)
            delete currentPage;
        delete pdfDoc;
        pdfDoc = NULL;
        return ;
    }
    currentPage = NULL;
    currentPageNb = 1;
}

void        PdfRendering::reloadFile()
{
    closeFile();
    openFile();
}

void        PdfRendering::scaled(float scaleFactor)
{   
    //to avoid big picture
    if (scaleFactor > 2)
        this->scaleFactor = 2;

    if (!matrix)
        matrix = new QMatrix(scaleFactor, 0, 0, scaleFactor, 0, 0);
    else if (this->scaleFactor != scaleFactor)
    {
        this->scaleFactor = scaleFactor;
        matrix->setMatrix(scaleFactor, 0, 0, scaleFactor, 0, 0);
    }
}

bool        PdfRendering::loadPage(unsigned int pageNb)
{
    if (pdfDoc == NULL)
    {
        qDebug() << "the document is not opened, cannot access pages";
        return false;
    }

    if (pageNb > (unsigned int)(pdfDoc->numPages()))
    {
        qDebug() << "Page number out of range";
        return false;
    }

    if (!currentPage)
    {
        currentPage = pdfDoc->page(pageNb);
        currentPageNb = pageNb;
    }
    else if (pageNb != currentPageNb)
    {
        delete currentPage;
        currentPage = pdfDoc->page(pageNb);
        currentPageNb = pageNb;
    }
    return true;
}

QImage        *PdfRendering::render(int page, QRectF *partToDisplay)
{
    if (!pdfDoc)
        if (!openFile())
            return NULL;

    if (!loadPage(page))
        return NULL;

    return generateImg(partToDisplay);
}

QImage  *PdfRendering::generateImg(QRectF * partToDisplay)
{
     QImage      image = currentPage->renderToImage(scaleFactor * 72.0,
                                                    scaleFactor * 72.0);
    if (image.isNull())
    {
        qDebug() << "[PdfDisplayer] Unable to generate an image from the PDF.";
        return NULL;
    }

    partToDisplay->adjust(-2, -2, 2, 2);
    scaled(scaleFactor);

    QRect part = matrix->mapRect(*partToDisplay).toRect();
    QImage  *subImg = new QImage(image.copy(part));
    delete partToDisplay;
    return subImg;
}

float PdfRendering::getScaleFactor() const
{
    return scaleFactor;
}

void        PdfRendering::setScaleFactor(const float scaleFactor)
{
    this->scaleFactor = scaleFactor;
}
