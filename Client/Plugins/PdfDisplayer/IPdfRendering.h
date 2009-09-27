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
