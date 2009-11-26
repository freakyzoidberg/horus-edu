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
#include "audioplayer.h"

#include <QIcon>
#include <QTime>

AudioPlayer::AudioPlayer(Phonon::MediaObject *media)
{
    seekSlider = new Phonon::SeekSlider(this);
    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setGeometry(0, 21, 100, 20);
    seekSlider->setGeometry(46, 0, 165, 20);
    stop = new QPushButton(this);
    stop->setIcon(QIcon(":/stop.png"));
    stop->setGeometry(101, 21, 20, 20);
    pause = new QPushButton(this);
    pause->setIcon(QIcon(":/pause.png"));
    pause->setGeometry(122, 21, 20, 20);
    play = new QPushButton(this);
    play->setIcon(QIcon(":/play.png"));
    play->setGeometry(143, 21, 20, 20);
    this->setMinimumWidth(200);
    connect(play, SIGNAL(clicked()), media, SLOT(play()));
    connect(pause, SIGNAL(clicked()), media, SLOT(pause()));
    connect(stop, SIGNAL(clicked()), media, SLOT(stop()));
    this->media = media;
    media->setTickInterval(1000);
    timeLCD = new QLCDNumber(this);
    QPalette palette;
    palette.setBrush(QPalette::Dark, Qt::darkBlue);
    timeLCD->setPalette(palette);
    timeLCD->setGeometry(164, 21, 50, 20);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
}

AudioPlayer::~AudioPlayer()
{
    delete seekSlider;
    delete volumeSlider;
}

void    AudioPlayer::tick(qint64 time)
{
     QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

     timeLCD->display(displayTime.toString("mm:ss"));
}

Phonon::VolumeSlider    *AudioPlayer::getVolumeSlider()
{
    return this->volumeSlider;
}

Phonon::SeekSlider      *AudioPlayer::getSeekSlider()
{
    return this->seekSlider;
}

Phonon::MediaObject     *AudioPlayer::getMedia()
{
    return media;
}

QPushButton             *AudioPlayer::getPause()
{
    return this->pause;
}

QPushButton             *AudioPlayer::getPlay()
{
    return this->play;
}

QPushButton             *AudioPlayer::getStop()
{
    return this->stop;
}
