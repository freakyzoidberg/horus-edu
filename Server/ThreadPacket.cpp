#include <QDateTime>
#include <QDebug>

#include "Sql.h"

#include "ThreadPacket.h"
#include "../Common/DataManager.h"
#include "PluginManagerServer.h"
#include "../Common/UserDataPlugin.h"
#include "../Common/TreeData.h"
#include "../Common/TreeDataPlugin.h"
#include "../Common/SettingsData.h"
#include "../Common/SettingsDataPlugin.h"
#include "UserSettings.h"
#include "../Common/CommInit.h"
#include "../Common/CommData.h"
#include "../Common/CommLogin.h"
#include "../Common/CommPlugin.h"
#include "NetworkPlugin.h"

//ZoidTest
#include "Tree.h"

ThreadPacket::ThreadPacket(ClientSocket* cs, const QByteArray& pac)
{
    socket = cs;
    packet = pac;//copy
}

void ThreadPacket::run()
{
    PluginManagerServer::instance()->setCurrentUser(socket->user);
    CommPacket pac(packet);
    // redirect to the good method
    (this->*packetDirections[ pac.packetType ])();
    PluginManagerServer::instance()->setCurrentUser(0);
}

ThreadPacket::packetDirection ThreadPacket::packetDirections[] =
{
    &ThreadPacket::PacketUndefined,
    &ThreadPacket::PacketError,
    &ThreadPacket::PacketInit,
    &ThreadPacket::PacketAlive,
    &ThreadPacket::PacketLogin,
    &ThreadPacket::PacketData,
    &ThreadPacket::PacketPlugin
};

void ThreadPacket::PacketUndefined()
{
//    CommPacket p(CommPacket::UNDEFINED);
}

void ThreadPacket::PacketError()
{
//    CommError err(packet);
}

void ThreadPacket::PacketInit()
{
    CommInit init(packet);

    if (socket->status != ClientSocket::INIT)
        return sendError(CommError::ALREADY_INITIALIZED);

    socket->status = ClientSocket::CONNECTED;
}

void ThreadPacket::PacketAlive()
{
    CommPacket a(CommPacket::ALIVE);
    emit sendPacket(a.getPacket());
}

void ThreadPacket::PacketLogin()
{
    CommLogin login(packet);

    // wait other threads for this connexion if needed
    socket->waitOtherThreads();

    if (socket->status != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if (login.method != CommLogin::LOGIN_PASSWORD && login.method != CommLogin::LOGIN_SESSION && login.method != CommLogin::LOGOUT)
        return sendError(CommError::PROTOCOL_ERROR);

    UserDataPlugin* plugin = PluginManagerServer::instance()->findPlugin<UserDataPlugin*>();
//    UserDataPlugin* plugin = (UserDataPlugin*)PluginManagerServer::instance()->findPlugin("UserDataPlugin");
    if ( ! plugin)
        return sendError(CommError::INTERNAL_ERROR, "No UserDataPlugin found. Cannot authenticate the user.");

    Sql conn;
    QSqlQuery query(QSqlDatabase::database(conn));

    UserData* user = 0;
    if (login.method == CommLogin::LOGIN_SESSION)
        user = plugin->authenticateSession(query, login.login, login.sessionString);

    else if (login.method == CommLogin::LOGIN_PASSWORD)
        user = plugin->authenticatePassword(query, login.login, login.password);

    else if (socket->user)
    {
        ClientSocket::connectedUsers.remove(socket->user);
        socket->user->destroySession(query);
        socket->user = 0;
        CommLogin resp(CommLogin::DISCONNECTED);
        emit sendPacket(resp.getPacket());
        qDebug() << "[out]" << resp;
        return;
    }

    if ( ! user)
    {
        CommLogin resp(CommLogin::REFUSED);
        emit sendPacket(resp.getPacket());
        qDebug() << "[out]" << resp;
        return;
    }

    // if the user is already connected, disconnect him from the other socket
    if (socket->connectedUsers.contains(user))
    {
        connect(this, SIGNAL(sendPacketToAnotherSocket(QByteArray)), ClientSocket::connectedUsers[user], SLOT(sendPacket(QByteArray)));
        emit sendPacketToAnotherSocket( CommLogin(CommLogin::DISCONNECTED).getPacket() );
        ClientSocket::connectedUsers[user]->user = 0;
    }
    ClientSocket::connectedUsers[user] = socket;
    socket->user = user;
    PluginManagerServer::instance()->setCurrentUser(socket->user);

    qDebug() << "ThreadPacket::PacketLogin : ACCEPTED" << user;

    CommLogin resp(CommLogin::ACCEPTED);
    resp.serverDateTime = QDateTime::currentDateTime();
    resp.sessionEnd = QDateTime::currentDateTime().addSecs( DEFAULT_SESSION_LIFETIME * 60 );
    resp.sessionString = socket->user->newSession(query, resp.sessionEnd);
    resp.user = user;
    emit sendPacket(resp.getPacket());

    // send user data
    plugin->dataManager->sendData(user,user);

    TreeDataPlugin* treePlugin = PluginManagerServer::instance()->findPlugin<TreeDataPlugin*>();
    if ( ! treePlugin)
        qDebug() << "Warning: no TreeDataPlugin found. Check your configuration.";
    else
    {
        TreeData* node = treePlugin->getNode(0);

        node->fillFromDatabase(query);
        node->setStatus(Data::UPTODATE);
        treePlugin->dataManager->sendData(user, node);
//        qDebug() << node;

        //send the node between 0 and user nodeId
        for (node = user->node();
             node->id() > 0;
             node = (TreeData*)(node->parent()))
        {
            node->fillFromDatabase(query);
            node->setStatus(Data::UPTODATE);
            treePlugin->dataManager->sendData(user, node );
//            qDebug() << node;
        }
    }

    SettingsDataPlugin* settingsPlugin = PluginManagerServer::instance()->findPlugin<SettingsDataPlugin*>();
    if ( ! settingsPlugin)
        qDebug() << "Warning: no SettingsDataPlugin found. Check your configuration.";
    else
    {
        SettingsData* setting = settingsPlugin->getSettings("test");

        setting->fillFromDatabase(query);
        setting->setStatus(Data::UPTODATE);
        settingsPlugin->dataManager->sendData(user, setting);
//        qDebug() << setting;
    }


    //allow other threads to be started
    socket->allowOtherThreads();
}

void ThreadPacket::PacketData()
{
    CommData data(packet);
    foreach (DataPlugin* plugin, PluginManagerServer::instance()->findPlugins<DataPlugin*>())
        if (plugin->getDataType() == data.type)
            plugin->dataManager->receiveData(socket->user, data.data);
}
//void ThreadPacket::PacketFile()
//{
//    CommFile f(packet);
//    qDebug() << "[ in]" << f;
//
//    if (socket->staus != ClientSocket::CONNECTED)
//      return sendError(CommError::NOT_INITIALIZED);
//
//    if ( ! socket->user)
//      return sendError(CommError::NOT_AUTHENTICATED);
//
//    FileManagment fileMgmt;
//    QSettings settings;
//    f.error = CommFile::NO_ERROR;
//
//    if (f.method == CommFile::NODE_LIST) //TODO: more permitions checks: ACCESS_DIR and exists
//        f.fileList = fileMgmt.getNodeList(f.fileInfo.id);
//
//    else if (f.method == CommFile::USER_LIST) //TODO: more permitions checks: ACCESS_DIR and exists
//        f.fileList = fileMgmt.getUserList(socket->user.getId());
//
//    else if (f.method == CommFile::DELETE_FILE
//          || f.method == CommFile::ACCESS_FILE
//          || f.method == CommFile::NEW_FILE
//          || f.method == CommFile::STAT_FILE)
//    {
//        QFile* qfile = 0;
//        if (f.method != CommFile::NEW_FILE)
//        {
//            qfile = new QFile(settings.value("SETTINGS/SoftFullPath", "/opt/Horus").toString() + '/' + settings.value("SETTINGS/FilesDirectory", "Files").toString() + '/' + QVariant(f.fileInfo.id).toString());
//
//            if ( ! fileMgmt.fileExist(f.fileInfo.id) || ! qfile->exists())
//                f.error = CommFile::NOT_FOUND;
//
//            else
//                f.fileInfo = fileMgmt.getFileInfo(f.fileInfo.id);
//        }
//
//        if (f.error == CommFile::NO_ERROR)
//        {
//            //check user can create or remove a file in the node
//            if ((f.method == CommFile::DELETE_FILE
//              || f.method == CommFile::NEW_FILE)
//            && ! fileMgmt.userCanChangeNode(socket->user.getId(), f.fileInfo.nodeId))
//                f.error = CommFile::PERMITION_DENIED;
//
//            //check if the file can be removed from the filesystem
//            else if (f.method == CommFile::DELETE_FILE
//                     &&  ! qfile->remove())
//                f.error = CommFile::PERMITION_DENIED;
//
//            if (f.method == CommFile::ACCESS_FILE
//             || f.method == CommFile::NEW_FILE)
//            {
//                if (f.method == CommFile::NEW_FILE)
//                {
//                    //TODO check fileInfo
//                    f.fileInfo.ownerId = socket->user.getId();
//                    fileMgmt.insertNewFile(f.fileInfo);
//                    qfile = new QFile(settings.value("SETTINGS/FilesDirectory", "/opt/Horus/Files").toString() + '/' + QVariant(f.fileInfo.id).toString());
//                }
//
//                //check if the file can be created/read/write from the filesystem
//                if (qfile->open(f.mode))
//                {
//                    //refresh FileInfo to be sure
//                    f.fileInfo = fileMgmt.getFileInfo(f.fileInfo.id);
//                    f.key = (new FileTransfert(qfile))->getKey();// activate the FileTransfert
//                }
//
//                else
//                    f.error = CommFile::PERMITION_DENIED;
//            }
//        }
//
//        if ( ! f.key.length() && qfile)
//            delete qfile;
//    }
//    else
//        return sendError(CommError::PROTOCOL_ERROR);
//
//    emit sendPacket(f.getPacket());
//    qDebug() << "[out]" << f;
//}

void ThreadPacket::PacketPlugin()
{
    CommPlugin mod(packet);

    if (socket->status != ClientSocket::CONNECTED)
        return sendError(CommError::NOT_INITIALIZED);
    if ( ! socket->user)
        return sendError(CommError::NOT_AUTHENTICATED);

    QString target = mod.packet.targetPlugin;

    NetworkPlugin* plugin = PluginManagerServer::instance()->findPlugin<NetworkPlugin*>(target);
    mod.packet.user = socket->user;
    if (plugin)
        return plugin->receivePacket(socket->user, mod.packet);

    mod.packet.targetPlugin = mod.packet.sourcePlugin;
    mod.packet.sourcePlugin = target;
    mod.packet.error = 1;
    mod.packet.errorMessage = "Plugin " + target + " not found or doesn't receive PluginPacket.";
    emit sendPacket(CommPlugin(mod.packet).getPacket());
}

void ThreadPacket::sendError(CommError::Error error, const char* str) const
{
    emit sendPacket(CommError(error, str).getPacket());
}
