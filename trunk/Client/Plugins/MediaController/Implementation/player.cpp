#include "player.h"

#include <QIcon>
#include <QTime>
#include <QVBoxLayout>

Player::Player(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    vidPlayer = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
    this->media = vidPlayer->mediaObject();
    this->media->setTickInterval(1000);
    layout->addWidget(this->vidPlayer);

    seekSlider = new Phonon::SeekSlider(this);
    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setGeometry(0, 21, 100, 20);
    seekSlider->setGeometry(46, 0, 165, 20);

    stopV = new QPushButton(this);
    stopV->setIcon(QIcon(":/stop.png"));
    stopV->setGeometry(101, 21, 20, 20);

    pauseV = new QPushButton(this);
    pauseV->setIcon(QIcon(":/pause.png"));
    pauseV->setGeometry(122, 21, 20, 20);

    playV = new QPushButton(this);
    playV->setIcon(QIcon(":/play.png"));
    playV->setGeometry(143, 21, 20, 20);

    this->setMinimumWidth(200);
    connect(playV, SIGNAL(clicked()), media, SLOT(play()));
    connect(pauseV, SIGNAL(clicked()), media, SLOT(pause()));
    connect(stopV, SIGNAL(clicked()), media, SLOT(stop()));

    timeLCD = new QLCDNumber(this);
    QPalette palette;
    palette.setBrush(QPalette::Dark, Qt::darkBlue);
    timeLCD->setPalette(palette);
    timeLCD->setGeometry(164, 21, 50, 20);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
}

Player::~Player()
{
    delete seekSlider;
    delete volumeSlider;
}

void    Player::tick(qint64 time)
{
     QTime displayTime(0, (time / 60000) % 60, (time / 1000) % 60);

     timeLCD->display(displayTime.toString("mm:ss"));
}

Phonon::VolumeSlider    *Player::getVolumeSlider()
{
    return this->volumeSlider;
}

Phonon::SeekSlider      *Player::getSeekSlider()
{
    return this->seekSlider;
}

Phonon::MediaObject     *Player::getMedia()
{
    return this->media;
}

Phonon::VideoPlayer     *Player::getVidPlayer()
{
    return this->vidPlayer;
}

QPushButton             *Player::getPause()
{
    return this->pauseV;
}

QPushButton             *Player::getPlay()
{
    return this->playV;
}

QPushButton             *Player::getStop()
{
    return this->stopV;
}
