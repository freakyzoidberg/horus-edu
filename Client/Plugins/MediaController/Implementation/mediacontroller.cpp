#include <phonon/mediasource.h>

#include "mediacontroller.h"

#include "../../../../Common/PluginManager.h"

MediaController::MediaController()
{
    qWarning() << "Media Controller loaded";

}

MediaController::~MediaController()
{

}

const QString    MediaController::pluginName() const
{
    return "MediaController";
}

const QString    MediaController::pluginVersion() const
{
    return "0.2";
}

const QString   MediaController::getSupportedType() const
{
    return ("Media");
}

QWidget*        MediaController::createDocumentWidget(QWidget *parent, ILessonDocument *document)
{
    int         fileId;

//this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));
    if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin MediaController] Type error:";
        qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller MediaController handle " << this->getSupportedType() << " type.";
        return NULL;
    }

    this->parent = parent;
    fileId = document->getParameters().value("name").toInt();
    data = pluginManager->findPlugin<FileDataPlugin*>()->getFile(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));
    this->vid = new Phonon::VideoWidget(parent);

    //if (data->isDownloaded())
    dl();
    return vid;
}

void    MediaController::dl()
{
    this->media = new Phonon::MediaObject(parent);
    Phonon::createPath(this->media, this->vid);

    Phonon::AudioOutput *audioOutput =
                new Phonon::AudioOutput(Phonon::VideoCategory, this);
    Phonon::createPath(media, audioOutput);
    Phonon::MediaSource source(data->file()->fileName());

    this->media->setCurrentSource(source);
    this->media->play();
}

void    MediaController::reload()
{

}

