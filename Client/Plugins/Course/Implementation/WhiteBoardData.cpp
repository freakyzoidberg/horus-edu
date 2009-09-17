#include <QXmlStreamWriter>
#include "WhiteBoardData.h"

WhiteBoardData::WhiteBoardData(FileDataPlugin *plugin, int fileId) : validXml(false)
{
    fileData = plugin->getFile(fileId);
    qDebug() << "Whiteboard: " << fileData->file()->readAll();
    QObject::connect(fileData, SIGNAL(downloaded()), SLOT(update()));
    if (fileData->isDownloaded())
        update();
}

bool    WhiteBoardData::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName == "Whiteboard")
    {
        validXml = true;
        return true;
    }
    else if (qName == "Item" && validXml)
    {
        int idx, id, x, y, w, h;
        bool isDocked;
        if ((idx = atts.index("id")) != -1)
            id = atts.value(idx).toInt();
        else
            return false;
        if ((idx = atts.index("x")) != -1)
            x = atts.value(idx).toInt();
        else
            return false;
        if ((idx = atts.index("y")) != -1)
            y = atts.value(idx).toInt();
        else
            return false;
        if ((idx = atts.index("width")) != -1)
            w = atts.value(idx).toInt();
        else
            return false;
        if ((idx = atts.index("height")) != -1)
            h = atts.value(idx).toInt();
        else
            return false;
        if ((idx = atts.index("is-docked")) != -1)
            isDocked = (bool)atts.value(idx).toInt();
        else
            return false;
        list.append(WhiteBoardItem(id, x, y, w, h, isDocked));
        return true;
    }
    return false;
}

bool    WhiteBoardData::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (qName == "Whiteboard")
    {
        validXml = false;
    }
    else if (qName != "Item")
    {
        return false;
    }
    return true;
}

void    WhiteBoardData::localUpdate(const WhiteBoardItemList& list)
{
    this->list.clear();
    this->list.append(list);
    WhiteBoardItemList::const_iterator it;
    QXmlStreamWriter writer(fileData->file());
    writer.writeStartDocument();
    writer.writeStartElement("WhiteBoard");
    for (it = list.begin(); it != list.end(); it++)
    {
        writer.writeStartElement("Item");
        writer.writeAttribute("id", QString(it->getId()));
        writer.writeAttribute("x", QString(it->getX()));
        writer.writeAttribute("y", QString(it->getY()));
        writer.writeAttribute("width", QString(it->getWidth()));
        writer.writeAttribute("height", QString(it->getHeight()));
        writer.writeAttribute("is-docked", QString((int)it->docked()));
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
}

void    WhiteBoardData::update()
{
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(fileData->file());
    xmlReader.setContentHandler(this);
    xmlReader.setErrorHandler(this);
    validXml = false;
    xmlReader.parse(source);
    emit remoteUpdate(list);
}

