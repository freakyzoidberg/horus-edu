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

AudioPlayer::AudioPlayer(FileData *fileData, QWidget *loadicon) : _fileData(fileData), _loadicon(loadicon), _commandId(1), _checkId(0), _lastTick(0), _playing(false)
{
	_layout = new QGridLayout();
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

AudioPlayer::~AudioPlayer()
{

}

void	AudioPlayer::downloaded()
{
	delete _loadicon;
	_mediaObject = new Phonon::MediaObject(this);
	QFile *file = new QFile(_fileData->fileName());
	_mediaObject->setCurrentSource(Phonon::MediaSource(file));
	_audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
	Phonon::createPath(_mediaObject, _audioOutput);
	_slider = new Phonon::SeekSlider(_mediaObject, this);
	_stopButton = new QPushButton(QIcon(":/stop.png"), tr("Stop"));
	_playButton = new QPushButton(QIcon(":/play.png"), tr("Play"));
	connect(_playButton, SIGNAL(pressed()), this, SLOT(play()));
	connect(_stopButton, SIGNAL(pressed()), this, SLOT(stop()));
	connect(_mediaObject, SIGNAL(finished()), this, SLOT(finished()));
	connect(_mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
	_layout->addWidget(_slider, 0, 0, 1, 2);
	_layout->addWidget(_stopButton, 1, 0);
	_layout->addWidget(_playButton, 1, 1);
}

void	AudioPlayer::play()
{
	if (_mediaObject->state() == Phonon::PlayingState)
	{
		_mediaObject->pause();
		_playButton->setText(tr("Play"));
		_playButton->setIcon(QIcon(":/play.png"));
		_playing = false;
		emit command(_commandId++, WhiteBoardItem::PAUSE, _mediaObject->currentTime());
	}
	else
	{
		_mediaObject->play();
		_playButton->setText(tr("Pause"));
		_playButton->setIcon(QIcon(":/pause.png"));
		_playing = true;
		emit command(_commandId++, WhiteBoardItem::PLAY, _mediaObject->currentTime());
	}
}

void	AudioPlayer::stop()
{
	_mediaObject->stop();
	_playButton->setText(tr("Play"));
	_playButton->setIcon(QIcon(":/play.png"));
	_playing = false;
	_lastTick = 0;
	emit command(_commandId++, WhiteBoardItem::STOP, 0);
}

void	AudioPlayer::finished()
{
	_mediaObject->stop();
	_playButton->setText(tr("Play"));
	_playButton->setIcon(QIcon(":/play.png"));
	_playing = false;
}

void	AudioPlayer::tick(qint64 time)
{
	if ((time - _lastTick) > _mediaObject->tickInterval() * 2 || time < _lastTick)
	{
		if (_playing)
		{
			emit command(_commandId++, WhiteBoardItem::PLAY, time);
		}
	}
	_lastTick = time;
}

void	AudioPlayer::switchSync(bool sync)
{
	if (sync == true)
	{
		_playButton->setEnabled(false);
		_stopButton->setEnabled(false);
		_slider->setEnabled(false);
	}
	else
	{
		_playButton->setEnabled(true);
		_stopButton->setEnabled(true);
		_slider->setEnabled(true);
	}
}

void	AudioPlayer::setCommand(quint32 id, WhiteBoardItem::Command command, qint64 argument)
{
	if (id > _checkId)
	{
		if (command == WhiteBoardItem::PLAY)
		{
			_mediaObject->seek(argument);
			_mediaObject->play();
			_playButton->setText(tr("Pause"));
			_playButton->setIcon(QIcon(":/pause.png"));
		}
		else if (command == WhiteBoardItem::STOP)
		{
			_mediaObject->stop();
			_playButton->setText(tr("Play"));
			_playButton->setIcon(QIcon(":/play.png"));
		}
		else if (command == WhiteBoardItem::PAUSE)
		{
			_mediaObject->seek(argument);
			_mediaObject->pause();
			_playButton->setText(tr("Play"));
			_playButton->setIcon(QIcon(":/play.png"));
		}
		id = _checkId;
	}
}
