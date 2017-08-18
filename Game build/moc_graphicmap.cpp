/****************************************************************************
** Meta object code from reading C++ file 'graphicmap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Farm/graphicmap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graphicmap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicMap_t {
    QByteArrayData data[11];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicMap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicMap_t qt_meta_stringdata_GraphicMap = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GraphicMap"
QT_MOC_LITERAL(1, 11, 13), // "beast_clicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "Beast"
QT_MOC_LITERAL(4, 32, 5), // "beast"
QT_MOC_LITERAL(5, 38, 14), // "beast_selected"
QT_MOC_LITERAL(6, 53, 10), // "move_enemy"
QT_MOC_LITERAL(7, 64, 2), // "id"
QT_MOC_LITERAL(8, 67, 21), // "on_enemy_double_click"
QT_MOC_LITERAL(9, 89, 12), // "container_id"
QT_MOC_LITERAL(10, 102, 14) // "on_enemy_click"

    },
    "GraphicMap\0beast_clicked\0\0Beast\0beast\0"
    "beast_selected\0move_enemy\0id\0"
    "on_enemy_double_click\0container_id\0"
    "on_enemy_click"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicMap[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   45,    2, 0x0a /* Public */,
       8,    1,   48,    2, 0x0a /* Public */,
      10,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void GraphicMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphicMap *_t = static_cast<GraphicMap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->beast_clicked((*reinterpret_cast< Beast(*)>(_a[1]))); break;
        case 1: _t->beast_selected((*reinterpret_cast< Beast(*)>(_a[1]))); break;
        case 2: _t->move_enemy((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_enemy_double_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_enemy_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphicMap::*_t)(Beast );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicMap::beast_clicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GraphicMap::*_t)(Beast );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicMap::beast_selected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject GraphicMap::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphicMap.data,
      qt_meta_data_GraphicMap,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GraphicMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicMap::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicMap.stringdata0))
        return static_cast<void*>(const_cast< GraphicMap*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GraphicMap::beast_clicked(Beast _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GraphicMap::beast_selected(Beast _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
