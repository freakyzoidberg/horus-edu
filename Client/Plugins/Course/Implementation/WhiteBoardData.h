#ifndef WHITEBOARDDATA_H
#define WHITEBOARDDATA_H

#include <QXmlDefaultHandler>
#include <QObject>

#include "../../../../Common/FileDataPlugin.h"
#include "../../../../Common/FileData.h"
#include "WhiteBoardItem.h"

class WhiteBoardData : public QObject, public QXmlDefaultHandler
{
    Q_OBJECT

public:
    WhiteBoardData(FileDataPlugin *plugin, int fileId);

    bool    startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool    endElement(const QString &namespaceURI, const QString &localName, const QString &qName);

public slots:
    void    localUpdate(const WhiteBoardItemList&);

signals:
    void    remoteUpdate(const WhiteBoardItemList&);

protected slots:
    void    update();

private:
    FileData *fileData;
    bool validXml;
    WhiteBoardItemList list;
};

#endif // WHITEBOARDDATA_H
