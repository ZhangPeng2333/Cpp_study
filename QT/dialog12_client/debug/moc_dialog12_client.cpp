/****************************************************************************
** Meta object code from reading C++ file 'dialog12_client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog12_client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog12_client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_dialog12_client_t {
    QByteArrayData data[7];
    char stringdata[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_dialog12_client_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_dialog12_client_t qt_meta_stringdata_dialog12_client = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 18),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 18),
QT_MOC_LITERAL(4, 55, 13),
QT_MOC_LITERAL(5, 69, 16),
QT_MOC_LITERAL(6, 86, 14)
    },
    "dialog12_client\0btnConnClickedSlot\0\0"
    "btnSendClickedSlot\0connectedSlot\0"
    "disconnectedSlot\0readyReadySlot\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dialog12_client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08,
       3,    0,   40,    2, 0x08,
       4,    0,   41,    2, 0x08,
       5,    0,   42,    2, 0x08,
       6,    0,   43,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dialog12_client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        dialog12_client *_t = static_cast<dialog12_client *>(_o);
        switch (_id) {
        case 0: _t->btnConnClickedSlot(); break;
        case 1: _t->btnSendClickedSlot(); break;
        case 2: _t->connectedSlot(); break;
        case 3: _t->disconnectedSlot(); break;
        case 4: _t->readyReadySlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject dialog12_client::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dialog12_client.data,
      qt_meta_data_dialog12_client,  qt_static_metacall, 0, 0}
};


const QMetaObject *dialog12_client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dialog12_client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dialog12_client.stringdata))
        return static_cast<void*>(const_cast< dialog12_client*>(this));
    return QDialog::qt_metacast(_clname);
}

int dialog12_client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
