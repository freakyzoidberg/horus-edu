/****************************************************************************
** Meta object code from reading C++ file 'testmodule.h'
**
** Created: Thu Apr 9 18:31:12 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../testmodule.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testmodule.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TestModule[] = {

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

static const char qt_meta_stringdata_TestModule[] = {
    "TestModule\0"
};

const QMetaObject TestModule::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TestModule,
      qt_meta_data_TestModule, 0 }
};

const QMetaObject *TestModule::metaObject() const
{
    return &staticMetaObject;
}

void *TestModule::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TestModule))
        return static_cast<void*>(const_cast< TestModule*>(this));
    if (!strcmp(_clname, "IClientPlugin"))
        return static_cast< IClientPlugin*>(const_cast< TestModule*>(this));
    if (!strcmp(_clname, "net.horus.Client.PluginInterface/1.0"))
        return static_cast< IClientPlugin*>(const_cast< TestModule*>(this));
    return QObject::qt_metacast(_clname);
}

int TestModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
