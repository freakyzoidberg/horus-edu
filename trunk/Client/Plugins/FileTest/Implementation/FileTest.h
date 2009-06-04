#ifndef FILETEST_H
#define FILETEST_H

#include "FileTest_global.h"

#include <QtPlugin>

#include "../../../IClientPlugin.h"
#include "../../../IFilePlugin.h"
#include "../../../IFileManager.h"
#include "../../../IFile.h"

class FILETESTSHARED_EXPORT FileTest : public IClientPlugin, public IFilePlugin
{
    Q_OBJECT
    Q_INTERFACES(IClientPlugin)
    Q_INTERFACES(IFilePlugin)

public:
    FileTest();
    IClient             *client;
    const QByteArray    getName() const;
    const QByteArray    getVersion() const;
    QStringList         getPluginsConflicts() const;
    QStringList         getPluginsRequired() const;
    QStringList         getPluginsRecommended() const;
    bool                event(QEvent *event);

private:
    IFile* f1;
    IFile* f2;

private slots:
    void launchTest();
    void t1();
    void t2();
};

#endif // FILETEST_H
