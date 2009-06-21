#include "Data.h"

#include "DataPlugin.h"

const char* Data::errorMessage()
{
    return "TODO";
}

const QString Data::getType() const
{
    return _plugin->getDataType();
}

void  Data::setStatus(UserData* user, DataStatus status)
{
    DataStatus old=(DataStatus)(_status);
    _status=status;
    _plugin->dataStatusChange(user, this, old);
}
