/****************************************************************************
** Meta object code from reading C++ file 'initpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Experiment2/initpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'initpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_initPage_t {
    QByteArrayData data[15];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_initPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_initPage_t qt_meta_stringdata_initPage = {
    {
QT_MOC_LITERAL(0, 0, 8), // "initPage"
QT_MOC_LITERAL(1, 9, 7), // "display"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 19), // "reloadButtonClicked"
QT_MOC_LITERAL(4, 38, 17), // "initButtonClicked"
QT_MOC_LITERAL(5, 56, 19), // "cancelButtonClicked"
QT_MOC_LITERAL(6, 76, 17), // "nextButtonClicked"
QT_MOC_LITERAL(7, 94, 7), // "addinfo"
QT_MOC_LITERAL(8, 102, 4), // "info"
QT_MOC_LITERAL(9, 107, 10), // "initProBar"
QT_MOC_LITERAL(10, 118, 3), // "min"
QT_MOC_LITERAL(11, 122, 3), // "max"
QT_MOC_LITERAL(12, 126, 12), // "updataProBar"
QT_MOC_LITERAL(13, 139, 4), // "curr"
QT_MOC_LITERAL(14, 144, 12) // "initComplete"

    },
    "initPage\0display\0\0reloadButtonClicked\0"
    "initButtonClicked\0cancelButtonClicked\0"
    "nextButtonClicked\0addinfo\0info\0"
    "initProBar\0min\0max\0updataProBar\0curr\0"
    "initComplete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_initPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   62,    2, 0x0a /* Public */,
       4,    0,   63,    2, 0x0a /* Public */,
       5,    0,   64,    2, 0x0a /* Public */,
       6,    0,   65,    2, 0x0a /* Public */,
       7,    1,   66,    2, 0x0a /* Public */,
       9,    2,   69,    2, 0x0a /* Public */,
      12,    1,   74,    2, 0x0a /* Public */,
      14,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void initPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        initPage *_t = static_cast<initPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->display((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->reloadButtonClicked(); break;
        case 2: _t->initButtonClicked(); break;
        case 3: _t->cancelButtonClicked(); break;
        case 4: _t->nextButtonClicked(); break;
        case 5: _t->addinfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->initProBar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->updataProBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->initComplete(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (initPage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&initPage::display)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject initPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_initPage.data,
      qt_meta_data_initPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *initPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *initPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_initPage.stringdata0))
        return static_cast<void*>(const_cast< initPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int initPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void initPage::display(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
