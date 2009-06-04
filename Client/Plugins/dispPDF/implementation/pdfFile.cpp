#include <QPainter>
#include <QMatrix>
#include <QRect>
#include <QPainter>

#include <pdfFile.h>

#include <QDebug>

PdfFile::PdfFile(const QString & fileName, int fileId)
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

PdfFile::~PdfFile()
{
    closeFile();
    if (matrix)
        delete matrix;
}

const QString & PdfFile::getFileName() const
{
    return fileName;
}

int     PdfFile::getFileId() const
{
    return fileId;
}

const Poppler::Document    *PdfFile::getPdfDoc() const
{
    return  pdfDoc;
}

const Poppler::Page         *PdfFile::getPage() const
{
    return currentPage;
}

int   PdfFile::getCurrentPageNumber() const
{
    return  currentPageNb;
}

bool        PdfFile::openFile()
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

void        PdfFile::closeFile()
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

void        PdfFile::reloadFile()
{
    closeFile();
    openFile();
}

void        PdfFile::scaled(float scaleFactor)
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

bool        PdfFile::loadPage(unsigned int pageNb)
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

QImage        *PdfFile::render(int page, QRectF *partToDisplay)
{
    if (!pdfDoc)
        if (!openFile())
            return NULL;

    if (!loadPage(page))
        return NULL;

    return generateImg(partToDisplay);
}

QImage  *PdfFile::generateImg(QRectF * partToDisplay)
{
     QImage      image = currentPage->renderToImage(scaleFactor * 72.0,
                                                    scaleFactor * 72.0);
    if (image.isNull())
    {
        qDebug() << "[dispPDF] Unable to generate an image from the PDF.";
        return NULL;
    }

    partToDisplay->adjust(-2, -2, 2, 2);
    scaled(scaleFactor);

    QRect part = matrix->mapRect(*partToDisplay).toRect();
    QImage  *subImg = new QImage(image.copy(part));
    return subImg;
}

float PdfFile::getScaleFactor() const
{
    return scaleFactor;
}

void        PdfFile::setScaleFactor(const float scaleFactor)
{
    this->scaleFactor = scaleFactor;
}
