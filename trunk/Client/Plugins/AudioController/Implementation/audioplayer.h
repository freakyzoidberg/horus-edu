#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <phonon/volumeslider.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>

class AudioPlayer : public QWidget
{
    Q_OBJECT
public:
    AudioPlayer(QWidget *, Phonon::MediaObject *);
    ~AudioPlayer();
    Phonon::VolumeSlider    *getVolumeSlider();
    Phonon::SeekSlider      *getSeekSlider();
    Phonon::MediaObject     *getMedia();
    QPushButton             *getStop();
    QPushButton             *getPause();
    QPushButton             *getPlay();

public slots:
    void                    tick(qint64);

private:
    Phonon::SeekSlider      *seekSlider;
    Phonon::VolumeSlider    *volumeSlider;
    Phonon::MediaObject     *media;
    QPushButton             *stop, *pause, *play;
    QLCDNumber              *timeLCD;
};

#endif // AUDIOPLAYER_H
