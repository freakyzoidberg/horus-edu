#include "FileTest.h"

#include <QDebug>
#include <QEvent>
#include <QTimer>
#include <QThread>
#include <QVariant>

Q_EXPORT_PLUGIN2(FileTest, FileTest)

FileTest::FileTest()
{
    QTimer::singleShot(500, this, SLOT(launchTest()));
}

const QByteArray    FileTest::getName() const
{
    return "FileTest";
}

const QByteArray    FileTest::getVersion() const
{
    return "0.1";
}

QStringList         FileTest::getPluginsRequired() const
{
    return (QStringList());
}

QStringList         FileTest::getPluginsConflicts() const
{
    return (QStringList());
}

QStringList         FileTest::getPluginsRecommended() const
{
    return (QStringList());
}

bool                FileTest::event(QEvent *event)
{
    qDebug() << "FileTest: Received Event not managed" << event;
    return false;
}

void FileTest::launchTest()
{
    qDebug() << "Debut de tests des fichiers.";

    f1 = fileManager->newFile(0);
//    f1 = fileManager->getFile(1);
//    connect(f1, SIGNAL(connexionOpened()), this, SLOT(t1()));
    qDebug() << f1->open(QIODevice::WriteOnly);
    t1();

//    f2 = fileManager->getFile(2);
//    connect(f2, SIGNAL(readyRead()), this, SLOT(t2()));
//    f2->open(QIODevice::ReadOnly);
}

void FileTest::t1()
{
    qDebug() << "FileTest::t1 start";
    for (int i=0; i < 100; i++)
        f1->write("samemeenshort"+QVariant(i).toByteArray());
//    f1->flush();
    qDebug() << "FileTest::t1 done";
}

void FileTest::t2()
{
    QByteArray buff = f2->readAll();
    qDebug() << "FileTest::t2" << buff.length();
}
