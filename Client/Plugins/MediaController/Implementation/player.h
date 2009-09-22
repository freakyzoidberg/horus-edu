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
