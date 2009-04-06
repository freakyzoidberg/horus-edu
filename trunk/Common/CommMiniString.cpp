#include "CommMiniString.h"

CommMiniString::CommMiniString(QByteArray& s) : QByteArray(s) {}

CommMiniString::CommMiniString(const char* s) : QByteArray(s) {}

CommMiniString::CommMiniString() : QByteArray() {}

QDataStream& operator<<(QDataStream& ds, CommMiniString& cms)
{
    int l = cms.length();
    if (l > 255)
    {
        qWarning() << "CommMiniString length is" << l << ". Truncated to 255.";
        l = 255;
    }

    ds << (quint8&)l;
    for (int i = 0; i < l; i++)
        ds << (quint8)cms[i];

    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommMiniString& cms)
{
    quint8 l;
    ds >> l;

    quint8 c;
    for (quint8 i = 0; i < l; i++)
    {
        ds >> c;
        cms.append(c);
    }
    return ds;
}
