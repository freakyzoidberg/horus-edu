#include <QtCore/qplugin.h>
#include <QDebug>
#include <QtXml/QXmlSimpleReader>
#include <QFile>
#include <QFrame>

#include "../../ClientEvents.h"
#include "../../IClient.h"
#include "../FileManagement/IFile.h"
#include "../FileManagement/IFilePlugin.h"
#include "../ILesson.h"
#include "../IController.h"
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

ILesson*      LessonManager::getLesson(quint32 fileId)
{
    Lesson *lesson = new Lesson();
    IFile *xmlfile = ((IFilePlugin*)(client->getPlugin("FileManagement")))->getFile(fileId);
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(xmlfile);
    XmlHandler *handler = new XmlHandler(lesson);
    xmlReader.setContentHandler(handler);
    xmlReader.setErrorHandler(handler);
    if (!xmlReader.parse(source))
        qDebug() << "Xml Parsing failed.";

    delete handler;
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

void          LessonManager::saveLesson(quint32 fileId, ILesson *lesson)
{
    IFile *xmlfile = ((IFilePlugin*)(client->getPlugin("FileManagement")))->getFile(fileId);
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

ILesson*      LessonManager::createNewLesson(quint32 fileId)
{
    Lesson *lesson = new Lesson();
    saveLesson(fileId, lesson);
    return lesson;
}

void        LessonManager::displayPage(ILesson::IPage *page, QWidget *widget)
{
    QList<quint32> files;
    const QList<ILesson::IPage::IObject *>& objects = page->getObjects();
    QList<ILesson::IPage::IObject *>::const_iterator it = objects.begin();
    this->page = page;
    this->widget = widget;
    file = 0;
    while (it != objects.end())
    {
        files = (*it)->getRequiredFiles();
        if (files.size() > 0)
        {
            file = ((IFilePlugin*)(client->getPlugin("FileManagement")))->getFile(files.at(0));
            file->open(QIODevice::ReadOnly);
            connect(file, SIGNAL(fileSynchronized()), this, SLOT(readyDisplayPage()));
            break;
        }
        it++;
    }
    this->readyDisplayPage();
}

void        LessonManager::readyDisplayPage()
{
    if (file)
        this->disconnect(file, SIGNAL(fileSynchronized()), this, SLOT(readyDisplayPage()));
    IController *controller;
    const QList<ILesson::IPage::IObject *>& objects = page->getObjects();
    QList<ILesson::IPage::IObject *>::const_iterator it = objects.begin();
    while (it != objects.end())
    {
        QPointF position = (*it)->getPosition();
        QSizeF size = (*it)->getSize();
        QWidget *frame = new QWidget(widget);
        frame->setGeometry((int)(position.x() * widget->geometry().width()) / 100, (int)(position.y() * widget->geometry().height()) / 100, (int)(size.width() * widget->geometry().width()) / 100, (int)(size.height() * widget->geometry().height()) / 100);
        (*it)->setWidget(frame);
        controller = qobject_cast<IController *>(this->client->getPlugin(QString((*it)->getType() + "Controller").toAscii()));
        qDebug() << "LessonManager: DisplayPage: Trying to display" << (*it)->getType() << "using controller"<< QString((*it)->getType() + "Controller").toAscii();
        if (!controller)
            qDebug() << "controle NULL";
        if (controller && controller->getSupportedType() == (*it)->getType())
        {
            controller->showObject(*it);
            (*it)->getWidget()->show();
        }
        else
            qDebug() << "LessonManager: DisplayPage: display failed";
        it++;
    }
    widget->update();
    displayedPages.insert(page, widget);
}

void        LessonManager::hidePage(ILesson::IPage *page)
{
    QMap<ILesson::IPage *, QWidget *>::iterator it = displayedPages.find(page);
    if (it != displayedPages.end())
    {
        const QList<ILesson::IPage::IObject *>& objects = page->getObjects();
        QList<ILesson::IPage::IObject *>::const_iterator oit = objects.begin();
        while (oit != objects.end())
        {
 //           delete *oit;
            (*oit)->getWidget()->hide();
            oit++;
        }
        it.value()->update();
        displayedPages.remove(page);
    }
}
