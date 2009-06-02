#ifndef PDFRENDERING_H
#define PDFRENDERING_H

#include <IPdfRendering.h>

#include <QString>
#include <QImage>
#include <QMatrix>
#include <qt4/poppler-qt4.h>

//! class used to generate a displayble "image" of the PDF
class   PdfRendering : public IPdfRendering
{
    public:
        //! Constructor. Open the pdf file.
        /*!
            \param fileName the name of the file
        */
        PdfRendering(const QString & fileName);

        //! Destructor. CLose the pdf file.
        ~PdfRendering();

        //! return the name of the pdf file
        /*!
          \return the variable fileName
        */
        const QString & getFileName() const;

        //! return the poppler document
        /*!
          \return the variable pdfDoc;
        */
        const Poppler::Document    *getPdfDoc() const;

        //! return the current page
        const Poppler::Page         *getPage() const;

        //! return the number of the current page
        int   getCurrentPageNumber() const;

        //! open the pdfFile
        bool        openFile();

        //! close the pdfFile
        void        closeFile();

        //! reload the file
        void        reloadFile();

        //! set one from the pdf document, check if the page is not out of range
        /*!
            \param pageNb the number of the page you wanna load
        */
        void        loadPage(int pageNb);

        //! return the scaleFactor
        float       getScaleFactor() const;
        void        setScaleFactor(const float scaleFactor);

        //! create the picture of the PDF, not finished
        QImage        render(QRectF *partToDisplay);

        //! modification of the scale factor, used when user zoom
        /*!
          \param scaleFactor the new scaleFactor
        */
        void    scaled(float scaleFactor);

    private:
        //! the name of the pdf file
        QString             fileName;

        //! THE pdf file according to the lib poppler
        Poppler::Document   *pdfDoc;

        //! the current from the pdf document
        Poppler::Page       *currentPage;

        //! the number of the current page
        int     currentPageNb;

        //! scale factor (like the 100%, 75%, etc view in most of the readers)
        float   scaleFactor;

        //! Matrix used to render
        QMatrix     *matrix;
};

#endif // PDFRENDERING_H
