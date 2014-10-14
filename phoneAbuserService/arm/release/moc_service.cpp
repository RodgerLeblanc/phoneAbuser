/****************************************************************************
** Meta object code from reading C++ file 'service.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/service.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Service[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       3,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      27,    8,    8,    8, 0x05,
      50,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      72,    8,    8,    8, 0x08,
     120,  112,    8,    8, 0x08,
     165,  147,    8,    8, 0x08,
     234,  225,    8,    8, 0x08,
     267,    8,    8,    8, 0x08,
     302,    8,    8,    8, 0x08,
     326,    8,    8,    8, 0x08,

 // properties: name, type, flags
     343,  338, 0x01495103,
     352,  338, 0x01495103,
     366,  338, 0x01495103,

 // properties: notify_signal_id
       0,
       1,
       2,

       0        // eod
};

static const char qt_meta_stringdata_Service[] = {
    "Service\0\0screenOnChanged()\0"
    "bedsideModeOnChanged()\0deviceActiveChanged()\0"
    "handleInvoke(bb::system::InvokeRequest)\0"
    "udpData\0onUdpDataReceived(QString)\0"
    "userActivityState\0"
    "onActivityStateChanged(bb::device::UserActivityState::Type)\0"
    "newState\0onBedsideModeActiveChanged(bool)\0"
    "onScreenOnOrBedsideModeOnChanged()\0"
    "onDeviceActiveChanged()\0onTimeout()\0"
    "bool\0screenOn\0bedsideModeOn\0deviceActive\0"
};

void Service::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Service *_t = static_cast<Service *>(_o);
        switch (_id) {
        case 0: _t->screenOnChanged(); break;
        case 1: _t->bedsideModeOnChanged(); break;
        case 2: _t->deviceActiveChanged(); break;
        case 3: _t->handleInvoke((*reinterpret_cast< const bb::system::InvokeRequest(*)>(_a[1]))); break;
        case 4: _t->onUdpDataReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->onActivityStateChanged((*reinterpret_cast< bb::device::UserActivityState::Type(*)>(_a[1]))); break;
        case 6: _t->onBedsideModeActiveChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onScreenOnOrBedsideModeOnChanged(); break;
        case 8: _t->onDeviceActiveChanged(); break;
        case 9: _t->onTimeout(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Service::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Service::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Service,
      qt_meta_data_Service, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Service::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Service::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Service::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Service))
        return static_cast<void*>(const_cast< Service*>(this));
    return QObject::qt_metacast(_clname);
}

int Service::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = getScreenOn(); break;
        case 1: *reinterpret_cast< bool*>(_v) = getBedsideModeOn(); break;
        case 2: *reinterpret_cast< bool*>(_v) = getDeviceActive(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setScreenOn(*reinterpret_cast< bool*>(_v)); break;
        case 1: setBedsideModeOn(*reinterpret_cast< bool*>(_v)); break;
        case 2: setDeviceActive(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Service::screenOnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Service::bedsideModeOnChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Service::deviceActiveChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
