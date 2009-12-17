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
#include "player.h"

#include <phonon/videowidget.h>
#include <QIcon>
#include <QTime>
#include <QVBoxLayout>
#include <QHBoxLayout>

Player::Player(FileData *fileData, QWidget* loadicon) : _fileData(fileData), _loadicon(loadicon)
{
	_layout = new QGridLayout();
	_layout->setMargin(2);
	setLayout(_layout);
	_loadicon->startTimer(100);
	_layout->addWidget(_loadicon);
	setStyleSheet("QFrame { background-color: rgb(236, 233, 216); }");
	if (fileData->isDownloaded() || fileData->status() == Data::UPTODATE)
	{
		downloaded();
	}
	else
	{
		connect(fileData, SIGNAL(downloaded()), this, SLOT(downloaded())); 	
	}
}

Player::~Player()
{

}

void	Player::downloaded()
{
	delete _loadicon;
	_mediaObject = new Phonon::MediaObject(this);
	_mediaObject->setCurrentSource(_fileData->file());
	_audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::createPath(_mediaObject, _audioOutput);
	_videoWidget = new Phonon::VideoWidget(this);
     Phonon::createPath(_mediaObject, _videoWidget);
	_slider = new Phonon::SeekSlider(_mediaObject, this);
	_stopButton = new QPushButton(QIcon(":/stop.png"), tr("Stop"));
	_playButton = new QPushButton(QIcon(":/play.png"), tr("Play"));
	connect(_playButton, SIGNAL(pressed()), this, SLOT(play()));
	connect(_stopButton, SIGNAL(pressed()), this, SLOT(stop()));
	connect(_mediaObject, SIGNAL(finished()), this, SLOT(stop()));
	_layout->addWidget(_videoWidget, 0, 0, 1, 2);
	_layout->addWidget(_slider, 1, 0, 1, 2);
	_layout->addWidget(_stopButton, 2, 0);
	_layout->addWidget(_playButton, 2, 1);
}

void	Player::play()
{
	if (_mediaObject->state() == Phonon::PlayingState)
	{
		_mediaObject->pause();
		_playButton->setText(tr("Play"));
		_playButton->setIcon(QIcon(":/play.png"));
	}
	else
	{
		_mediaObject->play();
		_playButton->setText(tr("Pause"));
		_playButton->setIcon(QIcon(":/pause.png"));
	}
}

void	Player::stop()
{
	_mediaObject->stop();
	_playButton->setText(tr("Play"));
	_playButton->setIcon(QIcon(":/play.png"));
}
