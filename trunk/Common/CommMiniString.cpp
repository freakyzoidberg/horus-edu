#include "CommMiniString.h"

CommMiniString::CommMiniString(QByteArray& s) : QByteArray(s)
{
}

CommMiniString::CommMiniString(const char* s) : QByteArray(s)
{
}

CommMiniString::CommMiniString() : QByteArray()
{
}

QDataStream& operator<<(QDataStream& ds, CommMiniString& cms)
{
    int l = cms.length();
    if (l > 255)
        return ds;

    ds << (quint8&)l;
    for (int i = 0; i < l; i++)
        ds << (quint8)cms[i];

    return ds;
}

QDataStream& operator>>(QDataStream& ds, CommMiniString& cms)
{
    int l;
    ds >> (quint8&)l;

    char c;
    for (int i = 0; i < l; i++)
    {
        ds >> (quint8&)c;
        cms.append(c);
    }
    return ds;
}
