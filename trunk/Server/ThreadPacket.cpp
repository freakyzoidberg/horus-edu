#include <QDateTime>

#include "ThreadPacket.h"

#include "PluginManager.h"
#include "User.h"
#include "UserSettings.h"
#include "FileTransfert.h"
#include "FileManagment.h"
#include "../Common/CommInit.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "../Common/CommFile.h"
#include "../Common/CommSettings.h"

//ZoidTest
#include "Tree.h"

ThreadPacket::ThreadPacket(ClientSocket* cs, const QByteArray& pac)
{
    socket = cs;
    packet = pac;//copy
}

void ThreadPacket::run()
{
    CommPacket pac(packet);
    // redirect to the good method
   (this->*packetDirections[ pac.packetType ])();
}

ThreadPacket::packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUndefined,
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketFile,
    &ThreadPacket::PacketSettings,
    &ThreadPacket::PacketPlugin
};

void ThreadPacket::PacketUndefined()
{
    CommPacket p(CommPacket::UNDEFINED);
    qDebug() << "[ in]" << p;
}

void ThreadPacket::PacketError()
{
    CommError err(packet);
    qDebug() << "[ in]" << err;
}

void ThreadPacket::PacketInit()
{
    CommInit init(packet);
    qDebug() << "[ in]" << init;

    if (socket->vState != ClientSocket::INIT)
        return sendError(CommError::ALREADY_INITIALIZED);

    socket->vState = ClientSocket::CONNECTED;
}

void ThreadPacket::PacketAlive()
{
    CommPacket a(CommPacket::ALIVE);
    qDebug() << "[ in]" << a;

    emit sendPacket(a.getPacket());
    qDebug() << "[out]" << a;
}

void ThreadPacket::PacketLogin()
{
    CommLogin login(packet);
    qDebug() << "[ in]" << login;

    if (socket->vState != ClientSocket::CONNECTED)
      return sendError(CommError::NOT_INITIALIZED);

    if (login.method != CommLogin::LOGIN_PASSWORD &&
        login.method != CommLogin::LOGIN_SESSION &&
        login.method != CommLogin::LOGOUT)
      return sendError(CommError::PROTOCOL_ERROR);

    socket->waitOtherThreads();

    User& user = socket->user;
    user.init();

    if (login.method == CommLogin::LOGOUT)
        user.logout();
    else if (login.method == CommLogin::LOGIN_SESSION)
        user.login(login.login, true, login.sessionString);
    else
        user.login(login.login, false, login.sha1Pass);

    if ( ! user.isLoggedIn())
    {
        CommLogin response(CommLogin::REFUSED);
        emit sendPacket(response.getPacket());
        qDebug() << "[out]" << response;
        return;
    }

    user.renewSession(DEFAULT_SESSION_LIFETIME * 60);
    CommLogin response(CommLogin::ACCEPTED);
    response.level = user.getLevel();
    response.sessionString = user.getSessionString();
    response.sessionTime =   user.getSessionEnd().toTime_t() - QDateTime::currentDateTime().toTime_t();

    emit sendPacket(response.getPacket());
    socket->allowOtherThreads();
    qDebug() << "[out]" << response;
}

void ThreadPacket::PacketFile()
{
    CommFile f(packet);
    qDebug() << "[ in]" << f;

    if (socket->vState != ClientSocket::CONNECTED)
      return sendError(CommError::NOT_INITIALIZED);

    if ( ! socket->user.isLoggedIn())
      return sendError(CommError::NOT_AUTHENTICATED);

    FileManagment fileMgmt;
    QSettings settings;
    f.error = CommFile::NO_ERROR;

    if (f.method == CommFile::NODE_LIST) //TODO: more permitions checks: ACCESS_DIR and exists
        f.fileList = fileMgmt.getNodeList(f.fileInfo.id);

    else if (f.method == CommFile::USER_LIST) //TODO: more permitions checks: ACCESS_DIR and exists
        f.fileList = fileMgmt.getUserList(socket->user.getId());

    else if (f.method == CommFile::DELETE_FILE
          || f.method == CommFile::ACCESS_FILE
          || f.method == CommFile::NEW_FILE
          || f.method == CommFile::STAT_FILE)
    {
        QFile* qfile = 0;
        if (f.method != CommFile::NEW_FILE)
        {
            qfile = new QFile(settings.value("SETTINGS/FilesDirectory", "/opt/Horus/Files").toString() + '/' + QVariant(f.fileInfo.id).toString());

            if ( ! fileMgmt.fileExist(f.fileInfo.id) || ! qfile->exists())
                f.error = CommFile::NOT_FOUND;

            else
                f.fileInfo = fileMgmt.getFileInfo(f.fileInfo.id);
        }

        if (f.error == CommFile::NO_ERROR)
        {
            //check user can create or remove a file in the node
            if ((f.method == CommFile::DELETE_FILE
              || f.method == CommFile::NEW_FILE)
            && ! fileMgmt.userCanChangeNode(socket->user.getId(), f.fileInfo.nodeId))
                f.error = CommFile::PERMITION_DENIED;

            //check if the file can be removed from the filesystem
            else if (f.method == CommFile::DELETE_FILE
                     &&  ! qfile->remove())
                f.error = CommFile::PERMITION_DENIED;

            if (f.method == CommFile::ACCESS_FILE
             || f.method == CommFile::NEW_FILE)
            {
                if (f.method == CommFile::NEW_FILE)
                {
                    //TODO check fileInfo
                    f.fileInfo.ownerId = socket->user.getId();
                    fileMgmt.insertNewFile(f.fileInfo);
                    qfile = new QFile(settings.value("SETTINGS/FilesDirectory", "/opt/Horus/Files").toString() + '/' + QVariant(f.fileInfo.id).toString());
                }

                //check if the file can be created/read/write from the filesystem
                if (qfile->open(f.mode))
                {
                    //refresh FileInfo to be sure
                    f.fileInfo = fileMgmt.getFileInfo(f.fileInfo.id);
                    f.key = (new FileTransfert(qfile))->getKey();// activate the FileTransfert
                }

                else
                    f.error = CommFile::PERMITION_DENIED;
            }
        }

        if ( ! f.key.length() && qfile)
            delete qfile;
    }
    else
        return sendError(CommError::PROTOCOL_ERROR);

    emit sendPacket(f.getPacket());
    qDebug() << "[out]" << f;
}

void ThreadPacket::PacketSettings()
{
    int len = packet.length();
    CommSettings s(packet);
    qDebug() << "[ in]" << s << "length" << len ;

    if (socket->vState != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if ( ! socket->user.isLoggedIn())
        return sendError(CommError::NOT_AUTHENTICATED);
    if (s.method != CommSettings::GET && s.method != CommSettings::SET)
        return sendError(CommError::PROTOCOL_ERROR);

    if ( s.scope == CommSettings::CLIENT_USER_SCOPE   || s.scope == CommSettings::SERVER_USER_SCOPE || //USER_SCOPE
        (s.scope == CommSettings::CLIENT_SYSTEM_SCOPE && s.method == CommSettings::GET) || //Read Client SYSTEM_SCOPE
        socket->user.getLevel() <= LEVEL_ADMINISTRATOR) // ADMIN
    {
        UserSettings userSettings(socket->user.getId(), s.plugin, s.scope);

        if (s.method == CommSettings::SET)
            userSettings.set(s.getBinarySettings());

        s.method = CommSettings::VALUE;
        s.setBinarySettings(userSettings.get());
    }
    else
        s.method = CommSettings::PERMISSION_DENIED;

    sendPacket(s.getPacket());
    qDebug() << "[out]" << s;
}

void ThreadPacket::PacketPlugin()
{
    int len = packet.length();
    CommPlugin mod(packet);
    qDebug() << "[ in]" << mod << "length:" << len;

    if (socket->vState != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if ( ! socket->user.isLoggedIn())
        return sendError(CommError::NOT_AUTHENTICATED);

    IServerPlugin* plugin = PluginManager::globalInstance()->getPlugin(mod.packet.targetPlugin);
    if (plugin)
    {
        plugin->recvPacket(socket->user.getId(), mod.packet);
        ((InterfaceServer*)plugin->server)->cleanInterface();
    }
    // else TODO send an error "Plugin not found"

}

void ThreadPacket::sendError(CommError::Error error, const char* str) const
{
    CommError err(error, str);
    qDebug() << "[out]" << err;
    emit sendPacket(err.getPacket());
}
