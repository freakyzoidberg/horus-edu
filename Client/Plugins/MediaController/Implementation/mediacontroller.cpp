#include <phonon/mediasource.h>

#include "mediacontroller.h"
#include "player.h"
#include "../../../../Common/PluginManager.h"

MediaController::MediaController()
{
}

MediaController::~MediaController()
{

}

const QString   MediaController::pluginName() const
{
    return "MediaController";
}

const QString   MediaController::pluginVersion() const
{
    return "0.2";
}

const QString   MediaController::getSupportedType() const
{
    return ("Media");
}

QWidget*        MediaController::createDocumentWidget(IItems *parent, ILessonDocument *document)
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

    //this->parent = parent;
    fileId = document->getParameters().value("name").toInt();
    data = pluginManager->findPlugin<FileDataPlugin*>()->getFile(fileId);
    Player *player = new Player(parent);
    this->parent = parent;
    parent->setMainWidget(player);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));

    //if (data->isDownloaded())
    dl();
    return player;
}

void    MediaController::dl()
{
    Player     *tmp;

    tmp = dynamic_cast<Player *>(parent->getMainWidget());

    Phonon::MediaSource source(data->file()->fileName());

    tmp->getVolumeSlider()->setAudioOutput(tmp->getVidPlayer()->audioOutput());
    tmp->getSeekSlider()->setMediaObject(tmp->getMedia());
    tmp->getVidPlayer()->play(source);
}

void    MediaController::reload()
{

}

void    MediaController::clean(IItems *widget)
{
    Player     *tmp;

    tmp = dynamic_cast<Player *>(widget->getMainWidget());
    tmp->getMedia()->stop();
    delete tmp;
}

void    MediaController::resizeWidget(IItems *widget)
{
    Player  *tmp;

    tmp = dynamic_cast<Player *>(widget);
}

QWidget    *MediaController::editDocument(QFile *metadata, QWidget *parent, ILessonDocument *)
{

}


