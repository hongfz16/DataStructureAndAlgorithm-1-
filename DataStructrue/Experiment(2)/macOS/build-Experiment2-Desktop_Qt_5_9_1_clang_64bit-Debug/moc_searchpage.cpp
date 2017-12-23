/****************************************************************************
** Meta object code from reading C++ file 'searchpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Experiment2/searchpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_searchPage_t {
    QByteArrayData data[11];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_searchPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_searchPage_t qt_meta_stringdata_searchPage = {
    {
QT_MOC_LITERAL(0, 0, 10), // "searchPage"
QT_MOC_LITERAL(1, 11, 7), // "display"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 20), // "passInfoToDetailPage"
QT_MOC_LITERAL(4, 41, 19), // "searchButtonClicked"
QT_MOC_LITERAL(5, 61, 6), // "useAVL"
QT_MOC_LITERAL(6, 68, 21), // "pageItemDoubleClicked"
QT_MOC_LITERAL(7, 90, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 107, 4), // "item"
QT_MOC_LITERAL(9, 112, 22), // "AVLSearchButtonClicked"
QT_MOC_LITERAL(10, 135, 23) // "HashSearchButtonClicked"

    },
    "searchPage\0display\0\0passInfoToDetailPage\0"
    "searchButtonClicked\0useAVL\0"
    "pageItemDoubleClicked\0QListWidgetItem*\0"
    "item\0AVLSearchButtonClicked\0"
    "HashSearchButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_searchPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   50,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void searchPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        searchPage *_t = static_cast<searchPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->display((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->passInfoToDetailPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->searchButtonClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->pageItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->AVLSearchButtonClicked(); break;
        case 5: _t->HashSearchButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (searchPage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&searchPage::display)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (searchPage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&searchPage::passInfoToDetailPage)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject searchPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_searchPage.data,
      qt_meta_data_searchPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *searchPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *searchPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_searchPage.stringdata0))
        return static_cast<void*>(const_cast< searchPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int searchPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void searchPage::display(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void searchPage::passInfoToDetailPage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
