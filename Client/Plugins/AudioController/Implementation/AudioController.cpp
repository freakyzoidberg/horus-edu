#include <phonon/mediasource.h>

#include "AudioController.h"
#include "audioplayer.h"

#include "../../../../Common/PluginManager.h"

AudioController::AudioController()
{
}

AudioController::~AudioController()
{

}

const QString   AudioController::pluginName() const
{
    return "AudioController";
}

const QString   AudioController::pluginVersion() const
{
    return "0.2";
}

const QString   AudioController::getSupportedType() const
{
    return ("Audio");
}

QWidget*        AudioController::createDocumentWidget(IItems *parent, ILessonDocument *document)
{
    int         fileId;

    if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin AudioController] Type error:";
        qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller AudioController handle " << this->getSupportedType() << " type.";
        return NULL;
    }

    this->parent = parent;
    media = new Phonon::MediaObject(parent);
    AudioPlayer *reader = new AudioPlayer(parent, media);
    fileId = document->getParameters().value("name").toInt();
    data = pluginManager->findPlugin<FileDataPlugin*>()->getFile(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));
    this->parent = parent;
    parent->setMainWidget(reader);

    //if (data->isDownloaded())
    dl();
    return reader;
}

void    AudioController::dl()
{
    AudioPlayer *tmp;

    //this->Audio = new Phonon::AudioObject(parent);
    //Phonon::createPath(this->Audio, this->vid);

    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, parent);
    Phonon::createPath(media, audioOutput);

    tmp = qobject_cast<AudioPlayer *>(this->parent->getMainWidget());
    tmp->getVolumeSlider()->setAudioOutput(audioOutput);
    tmp->getSeekSlider()->setMediaObject(media);

    Phonon::MediaSource source(data->file()->fileName());
    tmp->getMedia()->setCurrentSource(source);
    tmp->getMedia()->play();
}

void    AudioController::reload()
{

}

void    AudioController::clean(IItems *widget)
{
    AudioPlayer *tmp;

    tmp = dynamic_cast<AudioPlayer *>(widget->getMainWidget());
    tmp->getMedia()->stop();
    delete tmp;
}

void    AudioController::resizeWidget(IItems *widget)
{

}

QWidget *AudioController::editDocument(QFile *metadata, QWidget *parent, ILessonDocument *)
{

}



