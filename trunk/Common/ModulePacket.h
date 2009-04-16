#ifndef MODULEPACKET_H
#define MODULEPACKET_H

class ModulePacket
{
  public:
    QByteArray        packetVerion;
    QByteArray        sourceModule;
    QByteArray        targetModule;

    QList<QByteArray> dataList;
};

#endif // MODULEPACKET_H
