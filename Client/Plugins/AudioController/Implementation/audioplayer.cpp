#include "audioplayer.h"

AudioPlayer::AudioPlayer(QWidget *parent, Phonon::MediaObject *media) : QWidget(parent)
{
    seekSlider = new Phonon::SeekSlider(this);
    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setGeometry(0, 21, 100, 20);
    seekSlider->setGeometry(46, 0, 100, 20);
    stop = new QPushButton("S", this);
    stop->setGeometry(101, 21, 20, 20);
    pause = new QPushButton("P", this);
    pause->setGeometry(122, 21, 20, 20);
    play = new QPushButton("R", this);
    play->setGeometry(143, 21, 20, 20);
    this->setMinimumWidth(200);
    connect(play, SIGNAL(clicked()), media, SLOT(play()));
    connect(pause, SIGNAL(clicked()), media, SLOT(pause()));
    connect(stop, SIGNAL(clicked()), media, SLOT(stop()));
    this->media = media;
}

AudioPlayer::~AudioPlayer()
{
    delete seekSlider;
    delete volumeSlider;
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
