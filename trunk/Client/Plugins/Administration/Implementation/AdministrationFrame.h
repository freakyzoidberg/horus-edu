#ifndef AdministrationFrame_H
#define AdministrationFrame_H

#include "ui_AdministrationFrame.h"
#include "TreeFrame.h"
#include "UserFrame.h"
#include "ClassFrame.h"
#include "FileFrame.h"
#include "ClassRoomFrame.h"
#include "TeacherFrame.h"
#include <QVariant>
#include <QQueue>

class AdministrationFrame : public QWidget, public Ui::AdminForm
{
    Q_OBJECT

    public:
         AdministrationFrame();
        void        packetManager(QVariantHash response);
    protected:
        virtual void changeEvent(QEvent *e);
    private:
        UserFrame    *uF;
        ClassFrame   *cF;
        TeacherFrame *teachF;
        ClassRoomFrame   *sF;
        FileFrame    *fF;

        void        fillTab();
        QQueue<QString> packetSender;
    protected slots:
        //! slot to send packet to a client
        void        sender(const QString&, PluginPacket *packet);
signals:
		void send(PluginPacket *packet);
};

#endif // AdministrationFrame_H
