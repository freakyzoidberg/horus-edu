#ifndef DISPPDF_H
#define DISPPDF_H

#include <QStringList>
#include <QObject>
#include <qt4/poppler-qt4.h>

#include "../../IClientPlugin.h"
#include "../../IPluginNetwork.h"
#include "dispPDFClient.h"
#include "dispPDFNetwork.h"
#include "pdfRendering.h"

//! This plugin is used to render a PDF file
/*
  To have more informations about horus plugins, see the plugin tesPlugin
*/

class DispPDF : public IClientPlugin
{
 Q_OBJECT
 Q_INTERFACES(IClientPlugin)

public:
    DispPDF();

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

    DispPDFNetwork   *pNetwork;

private:
    PdfRendering        *renderPdf;
    PdfRendering        *openPDFDoc(const QString &);
};

#endif // DISPPDF_H
