/****************************************************************************
** Meta object code from reading C++ file 'woogle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Experiment2/woogle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'woogle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_woogle_t {
    QByteArrayData data[6];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_woogle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_woogle_t qt_meta_stringdata_woogle = {
    {
QT_MOC_LITERAL(0, 0, 6), // "woogle"
QT_MOC_LITERAL(1, 7, 12), // "updataProBar"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 10), // "initProBar"
QT_MOC_LITERAL(4, 32, 10), // "appendText"
QT_MOC_LITERAL(5, 43, 12) // "initComplete"

    },
    "woogle\0updataProBar\0\0initProBar\0"
    "appendText\0initComplete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_woogle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    2,   37,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       5,    0,   45,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

void woogle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        woogle *_t = static_cast<woogle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updataProBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->initProBar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->appendText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->initComplete(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (woogle::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&woogle::updataProBar)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (woogle::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&woogle::initProBar)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (woogle::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&woogle::appendText)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (woogle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&woogle::initComplete)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject woogle::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_woogle.data,
      qt_meta_data_woogle,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *woogle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *woogle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_woogle.stringdata0))
        return static_cast<void*>(const_cast< woogle*>(this));
    return QThread::qt_metacast(_clname);
}

int woogle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void woogle::updataProBar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void woogle::initProBar(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void woogle::appendText(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void woogle::initComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
