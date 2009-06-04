#ifndef IPDFFILE_H
#define IPDFFILE_H

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
      virtual QImage    *dispPDFDoc(const QString & fileName, int page,
                                    QRectF *partToDisplay, int fileId = -1) = 0;

    //! display a part of a pdf file (overload)
    /*
    \param fileId the file identifier
    \param page the page you want to display
    \param partToDisplay the part of the page you want to display
    \return a pointer to the diaplayable image
    */
     virtual QImage    *dispPDFDoc(quint32 fileId, int page, QRectF *partToDisplay) = 0;

    /*!
      Close a pdf file and remove it from the map. When the name has been
      resolved from the id it calls the closePdfFile(const QString &)
      \param fileId the id of the file.
    */
     virtual void    closePdfFile(int fileId) = 0;
};

#endif // IPDFFILE_H
