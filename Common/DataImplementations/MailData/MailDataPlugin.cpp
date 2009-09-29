#include "MailDataPlugin.h"
#include "MailData.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

MailData* MailDataPlugin::getMail(quint32 i)
{
    qDebug() << "Je passe dans le get mail par id";
        foreach (MailData* wb, Mails)
                if (wb->_id == i)
            {
            qDebug() << "Trouve";
			return wb;
                    }

        MailData* wb = new MailData(this);
        wb->setId(42);
        Mails.append(wb);
	return wb;
}


MailData* MailDataPlugin::createMail()
{
    qDebug() << "createMail";
        MailData* u = new MailData(this);
        u->setId(42);
        Mails.append(u);
    return u;
}


Data* MailDataPlugin::getDataWithKey(QDataStream& s)
{
    qDebug() << "getDataWithKey";
        quint32 Id;
        s >> Id;
        return getMail(42);
}

#ifdef HORUS_CLIENT
void MailDataPlugin::dataHaveNewKey(Data*d, QDataStream& s)
{
//    quint32 tmpId;
//    s >> tmpId;
//	((MailData*)(d))->_id = tmpId;
}
#endif
#ifdef HORUS_SERVER
void WhiteBoardDataPlugin::loadDataBase(QSqlQuery& query)
//{
//        query.prepare("SELECT id_tree,mode,items,mtime FROM white_board;");
//        if ( ! query.exec())
//        {
//                qDebug() << query.lastError();
//                return;
//        }
//        while (query.next())
//        {
//                WhiteBoardData* wb	= getWhiteBoard(query.value(0).toUInt());
//                wb->_syncMode		= (WhiteBoardData::SyncMode)(query.value(1).toUInt());
//                wb->_items			= query.value(2).toByteArray();
//                wb->_lastChange		= query.value(3).toDateTime();
//                wb->_status			= Data::UPTODATE;
//        }
}

void WhiteBoardDataPlugin::sendUpdates(QSqlQuery&, UserData* user, QDateTime date)
{
//	foreach (WhiteBoardData* data, whiteBoards)
//		if (data->lastChange() >= date)
//			dataManager->sendData(user, data);
}
#endif
