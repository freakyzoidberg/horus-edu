#ifndef DISPPDF_H
#define DISPPDF_H

#include <QStringList>
#include <QObject>
#include <QMap>
#include <qt4/poppler-qt4.h>

#include "../../IClientPlugin.h"
#include "../../IPluginNetwork.h"
#include "dispPDFClient.h"
#include "dispPDFNetwork.h"
#include "pdfRendering.h"

#define PLUGIN_NAME "dispPDF"
#define PLUGIN_VERSION "1.0"

//! This plugin is used to render a PDF file
/*
  To have more informations about horus plugins, see the plugin tesPlugin
*/

class DispPDF : public IClientPlugin
{
 Q_OBJECT
 Q_INTERFACES(IClientPlugin)

public:
    //! allocate pNetwork and set some values
    DispPDF();

    //! free pNetwork
    ~DispPDF();

    //! Return the name of the plugin.
    /*!
      \return the variable name
    */
    const QByteArray        getName() const;

    //! Return the version of the plugin
    /*!
      \return the variable version
    */
    const QByteArray        getVersion() const;

    //! Return the conflicst between plugins
    /*!
      \return the variable pluginsConflicts
    */
    QStringList             getPluginsConflicts() const;

    //! Return the list of plugins requiered
    /*!
      \return the variable pluginsRequiered
    */
    QStringList             getPluginsRequired() const;

    //! Return the list of plugins recommended
    /*!
        \return the variable pluginsRecommended
    */
    QStringList             getPluginsRecommended() const;

    //QStringList           getExports();

    //! Overload of the event() method
    /*!
      \param event the event received by the plugin
      \return true if the event was successfully handled, false eitherway
    */
    bool                    event(QEvent *event);

    //! Handle the event loadEvent
    /*!
      \param event the event received by the plugin
      \return true if the event was successfully handled, false eitherway
    */
    bool                    eventHandlerLoad(QEvent *event);

    //! Handle the event unloadEvent
    /*!
      \param event the event received by the plugin
      \return true if the event was successfully handled, false eitherway
    */
    bool                    eventHandlerUnload(QEvent *event);

    //! return the map containing all the PDF files
    /*
      \return the variable renderPdf
    */
    const QMap<QString, PdfRendering *>    *getRenderPdf() const;

    //! Open a pdf file
    /*
    \param fileName the absolute path  to the file
    */
    void    dispPDFDoc(const QString & fileName);

private:
    //! the name of the plugin
    QByteArray  name;

    //!the version of the plugin
    QByteArray  version;

    //! The list of the name of the plugins conflicting with the dispPDF plugin
    QStringList pluginsConflicts;

    //! The list of the name of plugins requiered by the dispPDF plugin
    QStringList plugindRequired;

    //! The list of the name of plugins recommended by the dispPDF plugin
    QStringList pluginsRecommended;

    //! network access for the plugin dispPDF (im not sure it is necessary)
    DispPDFNetwork   *pNetwork;

    //! QMap containing all the open PDF files with their name
    QMap<QString, PdfRendering *>   *renderPdf;
};

#endif // DISPPDF_H
