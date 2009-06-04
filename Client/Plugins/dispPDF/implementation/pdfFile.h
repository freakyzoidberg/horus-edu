#ifndef PdfFile_H
#define PdfFile_H

#include <IPdfFile.h>

#include <QString>
#include <QImage>
#include <QMatrix>
#include <qt4/poppler-qt4.h>

//! class used to generate a displayble "image" of the PDF
/*!
    Each lesson is composed of further parts of documents, listed in the
    metadata file.

    In those lessons parts of pdf files can be displayed. The class
    PdfFile inherites from the interface IPdfFile. It is
    designed to generate a QImage of a part of a page the pdf file.

    Each pdf file used in lessons must instanciate a PdfFile.

    The render(int page, QRectF *partToDisplay)  method is the "main"
    method of this class, because it generates the QImage.

    To display a pdf we use the poppler library, based on Qt4. It creates
    QImage of a page of a pdf. Once the image of an entire page is created,
    we extract the a rectangle (QRectF, the second parameter of the render()
    method) which represents the part of the page we want to display in the
    lesson.
 */
class   PdfFile : public IPdfFile
{
    public:
        //! Constructor. Open the pdf file.
        /*!
            \param fileName the name of the file
            \the page you want to display
        */
        PdfFile(const QString & fileName);

        //! Destructor. CLose the pdf file.
        ~PdfFile();

        //! return the name of the pdf file
        /*!
          \return the variable fileName
        */
        const QString & getFileName() const;
        int             getFileId() const;


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
        /*
        \return true if the file successfully opened, false either
        */
        bool        openFile();

        //! close the pdfFile
        void        closeFile();

        //! reload the file
        void        reloadFile();

        //! set one from the pdf document, check if the page is not out of range
        /*!
            \param pageNb the number of the page you wanna load
            \return true if the page 'page' is loaded, false either
        */
        bool        loadPage(unsigned int pageNb);

        //! return the scaleFactor
        float       getScaleFactor() const;

        //!set the scale factor
        /*!
          \param scaleFactor the scale factor
        */
        void        setScaleFactor(const float scaleFactor);

        //! create the picture of the PDF.
        /*!
          Firts it tries to open the file if it not already loaded.
          Second il tries to load the page specified by the parameter 'page'.
          Then it calls the method generateImg

          \param page the page number you want to display
          \param partToDisplay a QRectF containing the cooridinate of
          the part of the page 'page' youwant to display
          \return a pointer to the QImage extracted from the pdf or NULL if an error occurs.
        */
        QImage        *render(int page, QRectF *partToDisplay);

        //! create the picture of the PDF
        /*!
          Firts it render the entire page 'currentPage'.
          Then it extracts the rectangle 'partToDisplay' from the previous generated image.

          \param partToDisplay a QRectF containing the cooridinate of
          the part of the page 'page' youwant to display
          \return a pointer to the QImage extracted from the pdf or NULL if an error occurs.
        */
        QImage        *generateImg(QRectF *partToDisplay);

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
        unsigned int     currentPageNb;

        //! scale factor (like the 100%, 75%, etc view in most of the readers)
        float   scaleFactor;

        //! Matrix used to render
        QMatrix     *matrix;
};

#endif // PdfFile_H
