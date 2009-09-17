#include <QXmlStreamWriter>
#include "WhiteBoardData.h"

WhiteBoardData::WhiteBoardData(FileDataPlugin *plugin, int fileId) : validXml(false)
{
    fileData = plugin->getFile(fileId);
    QObject::connect(fileData, SIGNAL(downloaded()), SLOT(update()));
    if (fileData->isDownloaded())
        update();
}

bool    WhiteBoardData::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
	if (qName == "WhiteBoard")
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

void    WhiteBoardData::localUpdate(const WhiteBoardItemList& list)
{
    this->list.clear();
    this->list.append(list);
    WhiteBoardItemList::const_iterator it;
	QFile *file = fileData->file();
	file->open(QIODevice::WriteOnly | QIODevice::Truncate);
	QXmlStreamWriter writer(file);
    writer.writeStartDocument();
    writer.writeStartElement("WhiteBoard");
    for (it = list.begin(); it != list.end(); it++)
    {
        writer.writeStartElement("Item");
		writer.writeAttribute("id", QVariant(it->getId()).toString());
		writer.writeAttribute("x", QVariant(it->getX()).toString());
		writer.writeAttribute("y", QVariant(it->getY()).toString());
		writer.writeAttribute("width", QVariant(it->getWidth()).toString());
		writer.writeAttribute("height", QVariant(it->getHeight()).toString());
		writer.writeAttribute("is-docked", QVariant((int)it->docked()).toString());
        writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
	writer.device()->close();
	fileData->upload();
	delete file;
}

void    WhiteBoardData::update()
{
    QXmlSimpleReader xmlReader;
	QFile *file = fileData->file();
	QXmlInputSource *source = new QXmlInputSource(file);
    xmlReader.setContentHandler(this);
    xmlReader.setErrorHandler(this);
    validXml = false;
	list.clear();
	if (!xmlReader.parse(source))
		qWarning() << "Parse error";
	file->close();
	delete file;
    emit remoteUpdate(list);
}

