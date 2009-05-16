/****************************************************************************
** Meta object code from reading C++ file 'SimpMessage.h'
**
** Created: Sat May 16 18:24:22 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SimpMessage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimpMessage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimpMessage[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_SimpMessage[] = {
    "SimpMessage\0"
};

const QMetaObject SimpMessage::staticMetaObject = {
    { &IServerPlugin::staticMetaObject, qt_meta_stringdata_SimpMessage,
      qt_meta_data_SimpMessage, 0 }
};

const QMetaObject *SimpMessage::metaObject() const
{
    return &staticMetaObject;
}

void *SimpMessage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimpMessage))
        return static_cast<void*>(const_cast< SimpMessage*>(this));
    if (!strcmp(_clname, "net.horus.Server.PluginInterface/1.0"))
        return static_cast< IServerPlugin*>(const_cast< SimpMessage*>(this));
    return IServerPlugin::qt_metacast(_clname);
}

int SimpMessage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IServerPlugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
