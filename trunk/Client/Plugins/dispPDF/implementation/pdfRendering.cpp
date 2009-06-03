#include <QPainter>
#include <QMatrix>
#include <QRect>
#include <QPainter>

#include <pdfRendering.h>
#include <metadata.h>

#include <QDebug>

PdfRendering::PdfRendering(const QString & fileName)
{
    this->fileName = fileName;
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
        scaleFactor = 2;

    this->scaleFactor = scaleFactor;
    matrix->setMatrix(scaleFactor, 0, 0, scaleFactor, 0, 0);
}

bool        PdfRendering::loadPage(int pageNb)
{
    if (pdfDoc == NULL)
    {
        qDebug() << "the document is not opened, cannot access pages";
        return false;
    }

    if (pageNb < 0 || pageNb > pdfDoc->numPages())
    {
        qDebug() << "Page number out of range";
        return false;
    }

    //free the old page
    if (currentPage)
        delete currentPage;

    //load the new one
    currentPage = pdfDoc->page(pageNb);
    currentPageNb = pageNb;
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
     QImage      image = currentPage->renderToImage(this->scaleFactor * 72.0,
                                                   this->scaleFactor * 72.0);
    if (image.isNull())
    {
        qDebug() << "[dispPDF] Unable to generate an image from the PDF.";
        return NULL;
    }

    if (!matrix)
        matrix = new QMatrix(this->scaleFactor, 0, 0, this->scaleFactor, 0, 0);

    partToDisplay->adjust(-2, -2, 2, 2);

    QRect part = matrix->mapRect(*partToDisplay).toRect();
    QImage  *subImg = new QImage(image.copy(part));
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
