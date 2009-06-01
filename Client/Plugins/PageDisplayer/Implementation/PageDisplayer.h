#ifndef PAGEDISPLAYER_H
#define PAGEDISPLAYER_H

#include <QObject>
#include <QEvent>
#include <QStringList>
#include <QtXml/QXmlStreamWriter>
#include <QList>
#include "../../IClientPlugin.h"

class PageDisplayer : public IClientPlugin
{
public:
    PageDisplayer();
    ~PageDisplayer();
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    QStringList         getPluginsConflicts() const;
    QStringList         getPluginsRequired() const;
    QStringList         getPluginsRecommended() const;
    bool                event(QEvent *event);
    bool                eventHandlerLoad(QEvent *event);
    bool                eventHandlerUnload(QEvent *event);

private:
    QByteArray          modName;
    QByteArray          modVersion;
    QStringList         modConflicts;
    QStringList         modRequired;
    QStringList         modRecommended;
    QStringList         exports;
};

#endif // PAGEDISPLAYER_H
