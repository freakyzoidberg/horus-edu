#include <QtCore/qplugin.h>
#include <QDebug>
#include <QtXml/QXmlSimpleReader>
#include <QFile>
#include <QFrame>

#include "../../ClientEvents.h"
#include "../../IClient.h"
#include "../ILesson.h"
#include "LessonManager.h"
#include "Lesson.h"
#include "XmlHandler.h"

extern QEvent::Type ClientEvents::LoadPluginEvent;
extern QEvent::Type ClientEvents::UnloadPluginEvent;

Q_EXPORT_PLUGIN2(LessonManager, LessonManager)

LessonManager::LessonManager()
{
    this->modName = "LessonManager";
    this->modVersion = "1.0";
    qDebug() << "module LessonManager loaded.";
}

LessonManager::~LessonManager()
{
    qDebug() << "module LessonManager unloaded.";
}

bool    LessonManager::event(QEvent *event)
{
    if (event->type() == ClientEvents::LoadPluginEvent)
    {
        event->accept();
        return eventHandlerLoad(event);
    }
    else if (event->type() == ClientEvents::UnloadPluginEvent)
    {
        event->accept();
        return eventHandlerUnload(event);
    }
    event->ignore();
    return QObject::event(event);
}

bool    LessonManager::eventHandlerLoad(QEvent *event)
{
    qDebug()  << "Handling event loadModule"
            << "isAccepted:"    << event->isAccepted()
            << "spontaneous:"   << event->spontaneous();
    return true;
}

bool    LessonManager::eventHandlerUnload(QEvent *event)
{
    qDebug()  << "Handling event UnlodModule"
            << "isAccepted:" << event->isAccepted()
            << "spontaneous:" << event->spontaneous();
    return true;
}

void LessonManager::setModName(const QByteArray modName)
{
    this->modName = modName;
}

void    LessonManager::setModVersion(const QByteArray modVersion)
{
    this->modVersion = modVersion;
}

void    LessonManager::setModRequired(const QString name)
{
    modRequired << name;
}

void    LessonManager::setModConflicts(const QString name)
{
    modConflicts << name;
}

void    LessonManager::setExports(const QString name)
{
    exports << name;
}

void    LessonManager::setModRecommended(const QString name)
{
    modRecommended << name;
}

const QByteArray   LessonManager::getName() const
{
    return modName;
}

const QByteArray   LessonManager::getVersion() const
{
    return modVersion;
}

QStringList   LessonManager::getPluginsConflicts() const
{
    return modConflicts;
}

QStringList   LessonManager::getPluginsRequired() const
{
    return modRequired;
}

QStringList   LessonManager::getPluginsRecommended() const
{
    return modRecommended;
}

QStringList   LessonManager::getExports() const
{
    return exports;
}

ILesson*      LessonManager::getLesson(const QString& filename)
{
    Lesson *lesson = new Lesson();
    QFile *xmlfile = new QFile(filename);
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(xmlfile);
    XmlHandler *handler = new XmlHandler(lesson);
    xmlReader.setContentHandler(handler);
    xmlReader.setErrorHandler(handler);
    if (!xmlReader.parse(source))
        qDebug() << "Xml Parsing failed.";
    delete handler;
    delete xmlfile;
    return lesson;
}

void          LessonManager::writeXmlSection(const QList<ILesson::IElement *>& list, QXmlStreamWriter& xmlWriter)
{
    QList<ILesson::IElement *>::const_iterator it = list.begin();
    while (it != list.end())
    {
        ILesson::ISection* sec = dynamic_cast<ILesson::ISection *>(*it);
        ILesson::IPage* page = dynamic_cast<ILesson::IPage *>(*it);
        if (page != NULL)
        {
            xmlWriter.writeStartElement("page");
            xmlWriter.writeAttribute("title", (*it)->getTitle());
            const QList<ILesson::IPage::IObject *>& objs = page->getObjects();
            QList<ILesson::IPage::IObject *>::const_iterator oit = objs.begin();
            while (oit != objs.end())
            {
                xmlWriter.writeStartElement("object");
                xmlWriter.writeAttribute("type", (*oit)->getType());
                xmlWriter.writeAttribute("position", QString().setNum((*oit)->getPosition().x()) + "," + QString().setNum((*oit)->getPosition().y()));
                xmlWriter.writeAttribute("size", QString().setNum((*oit)->getSize().width()) + "," + QString().setNum((*oit)->getSize().height()));
                xmlWriter.writeEndElement();
                oit++;
            }
            xmlWriter.writeEndElement();
        }
        else if (sec != NULL)
        {
            xmlWriter.writeStartElement("section");
            xmlWriter.writeAttribute("title", (*it)->getTitle());
            writeXmlSection(sec->getElements(), xmlWriter);
            xmlWriter.writeEndElement();
        }
        it++;
    }
}

void          LessonManager::saveLesson(const QString& filename, ILesson *lesson)
{
    QFile *xmlfile = new QFile(filename);
    xmlfile->open(QIODevice::WriteOnly | QIODevice::Truncate);
    QXmlStreamWriter xmlWriter(xmlfile);
    xmlWriter.writeStartDocument("1.0");
    xmlWriter.writeStartElement("lesson");
    xmlWriter.writeAttribute("title", lesson->getTitle());
    writeXmlSection(lesson->getElements(), xmlWriter);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    xmlfile->close();
}

ILesson*      LessonManager::createNewLesson(const QString& filename)
{
    Lesson *lesson = new Lesson();
    saveLesson(filename, lesson);
    return lesson;
}

void        LessonManager::displayPage(ILesson::IPage *page, QWidget *widget)
{
    const QList<ILesson::IPage::IObject *>& objects = page->getObjects();
    QList<ILesson::IPage::IObject *>::const_iterator it = objects.begin();
    while (it != objects.end())
    {
        QPointF position = (*it)->getPosition();
        QSizeF size = (*it)->getSize();
        QWidget *frame = new QWidget(widget);
        frame->setGeometry((int)(position.x() * widget->geometry().width()) / 100, (int)(position.y() * widget->geometry().height()) / 100, (int)(size.width() * widget->geometry().width()) / 100, (int)(size.height() * widget->geometry().height()) / 100);
        (*it)->setWidget(frame);
        it++;
    }
    widget->update();
}

void        LessonManager::hideCurrentPage()
{

}
