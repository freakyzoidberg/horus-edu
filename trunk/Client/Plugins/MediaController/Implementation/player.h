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
#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <phonon/volumeslider.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/videoplayer.h>

class Player : public QWidget
{
    Q_OBJECT
public:
    Player(QWidget *);
    ~Player();
    Phonon::VolumeSlider    *getVolumeSlider();
    Phonon::SeekSlider      *getSeekSlider();
    Phonon::MediaObject     *getMedia();
    QPushButton             *getStop();
    QPushButton             *getPause();
    QPushButton             *getPlay();
    Phonon::VideoPlayer     *getVidPlayer();

public slots:
    void                    tick(qint64);
    void                    fullScreen();
    void                    leaveFullScreen();

private:
    Phonon::SeekSlider      *seekSlider;
    Phonon::VolumeSlider    *volumeSlider;
    Phonon::MediaObject     *media;
    Phonon::VideoPlayer     *vidPlayer;
    QPushButton             *stopV, *pauseV, *playV, *toFullScreen, *noFullScreen;
    QLCDNumber              *timeLCD;
};

#endif // AUDIOPLAYER_H
