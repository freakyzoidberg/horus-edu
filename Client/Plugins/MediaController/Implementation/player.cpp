#include "player.h"

#include <phonon/videowidget.h>
#include <QIcon>
#include <QTime>
#include <QVBoxLayout>
#include <QHBoxLayout>

Player::Player(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *hLayout = new QHBoxLayout();
    QHBoxLayout *hLayout2 = new QHBoxLayout();

    vidPlayer = new Phonon::VideoPlayer(Phonon::VideoCategory, this);
    this->media = vidPlayer->mediaObject();
    this->media->setTickInterval(1000);
    layout->addWidget(this->vidPlayer);

    seekSlider = new Phonon::SeekSlider(this);
    volumeSlider = new Phonon::VolumeSlider(this);
    //volumeSlider->setGeometry(0, 21, 100, 20);
    //seekSlider->setGeometry(46, 0, 165, 20);

    stopV = new QPushButton(this);
    stopV->setIcon(QIcon(":/stop.png"));
    //stopV->setGeometry(101, 21, 20, 20);

    pauseV = new QPushButton(this);
    pauseV->setIcon(QIcon(":/pause.png"));
    //pauseV->setGeometry(122, 21, 20, 20);

    playV = new QPushButton(this);
    playV->setIcon(QIcon(":/play.png"));
    //playV->setGeometry(143, 21, 20, 20);

    toFullScreen = new QPushButton(this);
    toFullScreen->setIcon(QIcon(":/fullscreen.png"));

    noFullScreen = new QPushButton(vidPlayer->videoWidget());
    noFullScreen->setIcon(QIcon(":/fullscreen.png"));

    //this->setMinimumWidth(200);
    connect(playV, SIGNAL(clicked()), media, SLOT(play()));
    connect(pauseV, SIGNAL(clicked()), media, SLOT(pause()));
    connect(stopV, SIGNAL(clicked()), media, SLOT(stop()));
    connect(toFullScreen, SIGNAL(clicked()), this, SLOT(fullScreen()));
    connect(noFullScreen, SIGNAL(clicked()), this, SLOT(leaveFullScreen()));

    timeLCD = new QLCDNumber(this);
    QPalette palette;
    palette.setBrush(QPalette::Dark, Qt::darkBlue);
    timeLCD->setPalette(palette);
    //timeLCD->setGeometry(164, 21, 20, 20);
    connect(media, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));

    hLayout->addWidget(playV);
    hLayout->addWidget(stopV);
    hLayout->addWidget(pauseV);
    hLayout->addWidget(toFullScreen);
    hLayout->addWidget(volumeSlider);
    hLayout2->addWidget(seekSlider);
    hLayout2->addWidget(timeLCD);

    layout->addLayout(hLayout2);
    layout->addLayout(hLayout);

    hLayout->maximumSize().setHeight(10);
    hLayout2->maximumSize().setHeight(10);
    hLayout->setSizeConstraint(QLayout::SetMaximumSize);
    hLayout2->setSizeConstraint(QLayout::SetMaximumSize);
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

void                    Player::fullScreen()
{
    this->vidPlayer->videoWidget()->setFullScreen(true);
    this->noFullScreen->show();
}

void                    Player::leaveFullScreen()
{
   this->vidPlayer->videoWidget()->setFullScreen(false);
   this->noFullScreen->hide();
}
