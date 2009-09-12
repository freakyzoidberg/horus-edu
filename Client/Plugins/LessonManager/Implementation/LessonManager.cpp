#include <QtCore/qplugin.h>
#include <QDebug>
#include <QtXml/QXmlSimpleReader>
#include <QFile>
#include <QFrame>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/FileDataPlugin.h"
#include "../../../../Common/FileData.h"

#include "../ILesson.h"
#include "../IController.h"
#include "LessonManager.h"
#include "Lesson.h"
#include "XmlHandler.h"

bool	LessonManager::canLoad() const
{
    if (pluginManager->findPlugin<TreeDataPlugin *>("Tree Data Base"))
        return (true);
    return (false);
}

void    LessonManager::load()
{
    lessonModel = new LessonModel(pluginManager);
}

void    LessonManager::unload()
{
    delete lessonModel;
}

const QString	LessonManager::pluginName() const
{
	return ("LessonManager");
}

const QString	LessonManager::pluginVersion() const
{
	return ("1.1");
}

LessonModel*     LessonManager::getLessonModel()
{
    return lessonModel;
}

ILesson*      LessonManager::getLesson(quint32 fileId)
{
    FileData *xmlfile;
    Lesson *lesson = new Lesson();
	// Waiting for FileData and FileDataPlugin to be implemented
    //xmlfile = this->pluginManager->findPlugin<FileDataPlugin *>("FileDataPlugin")->getFile(fileId);
    //QXmlSimpleReader xmlReader;
    //QXmlInputSource *source = new QXmlInputSource(xmlfile);
    //XmlHandler *handler = new XmlHandler(lesson);
    //xmlReader.setContentHandler(handler);
    //xmlReader.setErrorHandler(handler);
    //if (!xmlReader.parse(source))
    //    qDebug() << "Xml Parsing failed.";
    //delete handler;
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
    FileData *xmlfile;
	// Waiting for FileData and FileDataPlugin to be implemented
    //xmlfile = this->pluginManager->findPlugin<FileDataPlugin *>("FileDataPlugin")->getFile(fileId);
    //xmlfile->open(QIODevice::WriteOnly | QIODevice::Truncate);
    //QXmlStreamWriter xmlWriter(xmlfile);
    //xmlWriter.writeStartDocument("1.0");
    //xmlWriter.writeStartElement("lesson");
    //xmlWriter.writeAttribute("title", lesson->getTitle());
    //writeXmlSection(lesson->getElements(), xmlWriter);
    //xmlWriter.writeEndElement();
    //xmlWriter.writeEndDocument();
    //xmlfile->close();
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
			// Waiting for FileData and FileDataPlugin to be implemented
            //file = this->pluginManager->findPlugin<FileDataPlugin *>("FileDataPlugin")->getFile(files.at(0));
            //file->open(QIODevice::ReadOnly);
            //connect(file, SIGNAL(fileSynchronized()), this, SLOT(readyDisplayPage()));
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
        controller = this->pluginManager->findPlugin<IController *>(QString((*it)->getType() + "Controller").toAscii());
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
