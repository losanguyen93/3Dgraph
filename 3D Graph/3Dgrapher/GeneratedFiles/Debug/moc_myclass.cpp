/****************************************************************************
** Meta object code from reading C++ file 'myclass.h'
**
** Created: Sat 22. Nov 20:28:36 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myclass.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myclass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DataFun[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DataFun[] = {
    "DataFun\0\0begin()\0"
};

void DataFun::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DataFun *_t = static_cast<DataFun *>(_o);
        switch (_id) {
        case 0: _t->begin(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DataFun::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DataFun::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DataFun,
      qt_meta_data_DataFun, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DataFun::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DataFun::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DataFun::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DataFun))
        return static_cast<void*>(const_cast< DataFun*>(this));
    return QWidget::qt_metacast(_clname);
}

int DataFun::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_Win[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
      15,    4,    4,    4, 0x0a,
      23,    4,    4,    4, 0x0a,
      32,    4,    4,    4, 0x0a,
      53,   42,    4,    4, 0x0a,
      72,    4,    4,    4, 0x0a,
      79,    4,    4,    4, 0x0a,
      94,    4,    4,    4, 0x0a,
     108,    4,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Win[] = {
    "Win\0\0clicked()\0Build()\0Delete()\0"
    "refresh()\0row,column\0makepoint(int,int)\0"
    "open()\0PrintAScreen()\0ShotAScreen()\0"
    "closeD()\0"
};

void Win::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Win *_t = static_cast<Win *>(_o);
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->Build(); break;
        case 2: _t->Delete(); break;
        case 3: _t->refresh(); break;
        case 4: _t->makepoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->open(); break;
        case 6: _t->PrintAScreen(); break;
        case 7: _t->ShotAScreen(); break;
        case 8: _t->closeD(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Win::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Win::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Win,
      qt_meta_data_Win, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Win::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Win::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Win::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Win))
        return static_cast<void*>(const_cast< Win*>(this));
    return QWidget::qt_metacast(_clname);
}

int Win::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Win::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
