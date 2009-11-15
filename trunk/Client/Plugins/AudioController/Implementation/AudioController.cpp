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

QWidget*        AudioController::createDocumentWidget(ILessonDocument *document)
{
    int         fileId;

    if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin AudioController] Type error:";
        qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller AudioController handle " << this->getSupportedType() << " type.";
        return NULL;
    }

    media = new Phonon::MediaObject;
    AudioPlayer *reader = new AudioPlayer(media);
    fileId = document->getParameters().value("name").toInt();
	data = pluginManager->findPlugin<FileDataPlugin*>()->file(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));

    //if (data->isDownloaded())
    dl();
    return reader;
}

void    AudioController::dl()
{
    AudioPlayer *tmp;

    //this->Audio = new Phonon::AudioObject(parent);
    //Phonon::createPath(this->Audio, this->vid);

    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory);
    Phonon::createPath(media, audioOutput);

    //tmp = qobject_cast<AudioPlayer *>(this->parent->getMainWidget());
    //tmp->getVolumeSlider()->setAudioOutput(audioOutput);
    //tmp->getSeekSlider()->setMediaObject(media);

    //Phonon::MediaSource source(data->file()->fileName());
    //tmp->getMedia()->setCurrentSource(source);
    //tmp->getMedia()->play();
}

void    AudioController::reload()
{

}

QWidget   *AudioController::editDocument(QFile *metadata, ILessonDocument *doc)
{
	return (0);
}



