#include <QPainter>
#include <QMatrix>
#include <QRect>
#include <QPainter>

#include <pdfFile.h>

#include <QDebug>

PdfFile::PdfFile(const QString & fileName)
{
    this->fileName = fileName;

    pdfDoc = NULL;
    currentPage = NULL;
    currentPageNb = 1;
    scaleFactor = 1;
    matrix = NULL;
    toc = NULL;

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

const Poppler::Document    *PdfFile::getPdfDoc() const
{
    return  pdfDoc;
}

QDomDocument    *PdfFile::getToc()
{
    if (!toc)
        generateToc();
    return toc;
}

void    PdfFile::generateToc()
{
    if (toc)
        return ;

    QDomDocument    *popplerToc = this->pdfDoc->toc();
    toc = new QDomDocument();

    addSynopsisToChild(popplerToc, toc);
    toc->toString();
}

void    PdfFile::addSynopsisChild(QDomNode *parent, QDomNode *parentDest)
{
    // keep track of the current listViewItem
    QDomNode n = parent->firstChild();
    while( !n.isNull() )
    {
        // convert the node to an element (sure it is)
        QDomElement e = n.toElement();

        // The name is the same
        QDomElement item = toc->createElement(n.nodeName());
        parentDest->appendChild(item);

        //useless for now
        if (!e.attribute("ExternalFileName").isNull())
             item.setAttribute("ExternalFileName", e.attribute("ExternalFileName"));

        if (!e.attribute("DestinationName").isNull())
        {
           // item.setAttribute("DestinationName", e.attribute("DestinationName"));
            Poppler::LinkDestination destination = *(doc->linkDestination(e.attribute("DestinationName")));

            item.setAttribute("Page", destination.pageNumber() - 1);
            item.setAttribute("PosYBegin", destination.top());
            item.setAttribute("PosTEnd", destination.bottom());
        }
        if (!e.attribute("Destination").isNull())
        {
            Poppler::LinkDestination destination(e.attribute(("Destination")));
            item.setAttribute("Page", destination.pageNumber() - 1);
            item.setAttribute("PosYBegin", destination.top());
            item.setAttribute("PosTEnd", destination.bottom());
        }

        /* truc je sais pas a quoi ca sert open
        if (!e.attribute("Open").isNull())
            item.setAttribute("Open", e.attribute("Open"));
        if (!e.attribute("DestinationURI").isNull())
            item.setAttribute("URL", e.attribute("DestinationURI"));
        */

        //recursivity mother fucker
        if (e.hasChildNodes())
          addSynopsisChil(&n, &item);
        n = n.nextSibling();
    }
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
    qDebug() << "pdf " << fileName << " file successfully opened";
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
    qDebug() << "[dispPDF] loading page " << pageNb;

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

    qDebug() << "[dispPDF] Image successfully generated";

    partToDisplay->adjust(-2, -2, 2, 2);
    scaled(scaleFactor);
    this->currentPage->links();
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
