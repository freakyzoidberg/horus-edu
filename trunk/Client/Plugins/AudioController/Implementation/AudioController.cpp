/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
    //AudioPlayer *tmp;

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

QWidget   *AudioController::editDocument(QFile *, ILessonDocument *)
{
	return (0);
}



