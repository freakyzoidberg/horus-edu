#include "MailDataPlugin.h"
#include "MailData.h"

#include "../../TreeDataPlugin.h"

#include "../../PluginManager.h"
#include "../../Plugin.h"

MailData* MailDataPlugin::getMail(quint32 i)
{
   foreach (MailData* wb, Mails)
    {
                if (wb->_id == i)
            {
			return wb;
                    }
            }
        MailData* wb = new MailData(this);
        Mails.append(wb);
	return wb;
}


MailData* MailDataPlugin::createMail()
{
        MailData* u = new MailData(this);
        Mails.append(u);
    return u;
}


Data* MailDataPlugin::getDataWithKey(QDataStream& s)
{
        quint32 Id;
        s >> Id;
        return getMail(Id);
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
void MailDataPlugin::loadDataBase(QSqlQuery& query)
{
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

void MailDataPlugin::sendUpdates(QSqlQuery&, UserData* user, QDateTime date)
{
//	foreach (WhiteBoardData* data, whiteBoards)
//		if (data->lastChange() >= date)
//			dataManager->sendData(user, data);
}
#endif
