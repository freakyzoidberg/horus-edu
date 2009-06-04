#ifndef IPDFFILE_H
#define IPDFFILE_H

class   IPdfRendering
{
    public:
      virtual QImage    *dispPDFDoc(const QString & fileName, int page,
                                    QRectF *partToDisplay, int fileId = -1) = 0;
      virtual QImage    *dispPDFDoc(quint32 fileId, int page, QRectF *partToDisplay) = 0;

};

#endif // IPDFFILE_H
