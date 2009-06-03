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
        delete pdfDoc;
        pdfDoc = NULL;
        return ;
    }
    if (currentPage)
        delete currentPage;
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
    //QSize    scale = pdfImage.size();

    //to avoid big picture
    if (scaleFactor > 2)
        scaleFactor = 2;

    //scale.setHeight(scale.height() * scaleFactor);
    //scale.setWidth(scale.width() * scaleFactor);
    //pdfImage = pdfImage.scaled(scale, Qt::KeepAspectRatio);
    this->scaleFactor = scaleFactor;
    matrix->setMatrix(scaleFactor, 0, 0, scaleFactor, 0, 0);
}

void        PdfRendering::loadPage(int pageNb)
{
    if (pdfDoc == NULL)
    {
        qDebug() << "the document is not opened, cannot access pages";
        return ;
    }

    if (pageNb < 0 || pageNb > pdfDoc->numPages())
    {
        qDebug() << "Page number out of range";
        return ;
    }

    //free the old page
    if (currentPage)
        delete currentPage;

    currentPage = pdfDoc->page(pageNb);
    currentPageNb = pageNb;
}

QImage        *PdfRendering::render(QRectF *partToDisplay)
{
    if (currentPage == NULL)
    {
        qDebug() << "NULL page";
    }
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

//QRect highlightRect = matrix.mapRect(test2).toRect();
    //remplacer ce tas de mouise => lire les metadatas et render en consequence
    //virer les valeurs en durs, chercher dpiX et Y, possibilite de changer le scaleFactor
    /*
    QRgb    pixel;

    highlightRect.adjust(-2, -2, 2, 2);

    QImage highlight = image.copy(highlightRect);
    QPainter painter;

    pixel = image.pixel(0, 0);
    painter.begin(&highlight);
    painter.fillRect(highlight.rect(),
                     QColor(qRed(pixel), qGreen(pixel), qBlue(pixel)));
    painter.end();

    painter.begin(&image);
    painter.drawImage(highlightRect, highlight);
    painter.end();
*/  
   // pdfImage = QPixmap::fromImage(image);
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
