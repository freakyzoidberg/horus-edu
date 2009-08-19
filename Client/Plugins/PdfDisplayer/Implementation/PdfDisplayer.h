#ifndef __PDFDISPLAYER_H__
# define __PDFDISPLAYER_H__

# include <QStringList>
# include <QObject>
# include <QMap>
# include <QRectF>
# include <qt4/poppler-qt4.h>

# include "../../../../Common/Plugin.h"
# include "../../../../Common/FileDataPlugin.h"

# include "../IPdfFile.h"
# include "../IPdfRendering.h"
# include "PdfFile.h"

//! This plugin is used to render a PDF file
/*
  To have more informations about horus plugins, see the plugin tesPlugin <-------- outdated information
*/

class PdfDisplayer : public Plugin, public IPdfRendering
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
    Q_INTERFACES(IPdfRendering)

public:
    //! set some values
    PdfDisplayer();

    //! free pNetwork
    ~PdfDisplayer();

    //! Return the name of the plugin.
    /*!
      \return the variable name
    */
    const QString        pluginName() const;

    //! Return the version of the plugin
    /*!
      \return the variable version
    */
    const QString        pluginVersion() const;

    //! Overload of the event() method
    /*!
      \param event the event received by the plugin
      \return true if the event was successfully handled, false eitherway
    */
    bool    event(QEvent *event);

    bool    PluginEventHandler(QEvent *event);

    //! return the map containing all the PDF files
    /*
      \return the variable renderPdf
    */
    const QMap<quint32, IPdfFile *>    *getAllPdfFiles() const;

    //! display a part of a pdf file
    /*
    \param fileName the absolute path  to the file
    \param page the page you want to display
    \param partToDisplay the part of the page you want to display
    \return a pointer to the diaplayable image
    */
    QImage    *PdfDisplayerDoc(const QString & fileName, int page, QRectF *partToDisplay, int fileId = -1);

    //! //! display a part of a pdf file (overload)
    /*
    \param fileId the file identifier
    \param page the page you want to display
    \param partToDisplay the part of the page you want to display
    \return a pointer to the diaplayable image
    */
     QImage    *PdfDisplayerDoc(quint32 fileId, int page, QRectF *partToDisplay);

    /*!
      Close a pdf file and remove it from the map. When the name has been
      resolved from the id it calls the closePdfFile(const QString &)
      \param fileId the id of the file.
    */
    void    closePdfFile(int fileId);

private:
    //! QMap containing all the open PDF files with their name
    QMap<quint32, IPdfFile *>   *pdfFiles;
};

#endif // __PDFDISPLAYER_H__
