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
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

#include <phonon/mediaobject.h>
#include <phonon/audiooutput.h>
#include <phonon/videowidget.h>
#include <phonon/seekslider.h>

#include "../../../../Common/FileData.h"
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardItem.h"

class Player : public QFrame
{
    Q_OBJECT
public:
    Player(FileData *, QWidget* loadicon);
    ~Player();

signals:
	void	command(quint32, WhiteBoardItem::Command, qint64);

public slots:
	void	downloaded();
	void	play();
	void	stop();
	void	finished();
	void	switchSync(bool);
	void	setCommand(quint32, WhiteBoardItem::Command, qint64);

protected slots:
	void	tick(qint64 time);

private:
	QGridLayout*			_layout;
	FileData*				_fileData;
	Phonon::MediaObject*	_mediaObject;
	Phonon::AudioOutput*	_audioOutput;
	QWidget*				_loadicon;
	Phonon::SeekSlider*		_slider;
	QPushButton*			_playButton;
	QPushButton*			_stopButton;
	Phonon::VideoWidget*	_videoWidget;
	quint32					_commandId;
	quint32					_checkId;
	qint64					_lastTick;
	bool					_playing;
};

#endif // VIDEOPLAYER_H
