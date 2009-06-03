#ifndef IPDFRENDERING_H
#define IPDFRENDERING_H

#include <qt4/poppler-qt4.h>
#include <QRectF>
#include <QImage>

//! Class of the API used to render PDF files
/*!
    This class contains methods allowing to render a PDF virtual
    All of them are pure virtual. Modules using PDF files must
    implement this class

    Maybe some methods can be delete, im not sure right now
*/
class   IPdfRendering
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
    virtual bool        loadPage(int pageNb) = 0;

    //! return the scaleFactor
    virtual float       getScaleFactor() const = 0;

    //! create the picture of the PDF, not finished. (need a solution to
    //! pass this image to the "core")
    virtual QImage    *render(int page, QRectF *partToDisplay) = 0;

    //! modification of the scale factor, used when user zoom
    /*!
      \param scaleFactor the new scaleFactor
    */
    virtual void    scaled(float scaleFactor) = 0;
};

#endif // IPDFRENDERING_H
