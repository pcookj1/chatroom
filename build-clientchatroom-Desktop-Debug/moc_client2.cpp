/****************************************************************************
** Meta object code from reading C++ file 'client2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../clientchatroom/client2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Client_t {
    QByteArrayData data[23];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Client_t qt_meta_stringdata_Client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Client"
QT_MOC_LITERAL(1, 7, 9), // "connected"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "loggedIn"
QT_MOC_LITERAL(4, 27, 11), // "loginFailed"
QT_MOC_LITERAL(5, 39, 5), // "error"
QT_MOC_LITERAL(6, 45, 12), // "disconnected"
QT_MOC_LITERAL(7, 58, 15), // "messageReceived"
QT_MOC_LITERAL(8, 74, 4), // "user"
QT_MOC_LITERAL(9, 79, 3), // "msg"
QT_MOC_LITERAL(10, 83, 7), // "addUser"
QT_MOC_LITERAL(11, 91, 10), // "deleteUser"
QT_MOC_LITERAL(12, 102, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(13, 131, 11), // "socketError"
QT_MOC_LITERAL(14, 143, 15), // "connectToServer"
QT_MOC_LITERAL(15, 159, 8), // "QString&"
QT_MOC_LITERAL(16, 168, 8), // "serverIp"
QT_MOC_LITERAL(17, 177, 10), // "serverPort"
QT_MOC_LITERAL(18, 188, 5), // "login"
QT_MOC_LITERAL(19, 194, 8), // "userName"
QT_MOC_LITERAL(20, 203, 11), // "sendMessage"
QT_MOC_LITERAL(21, 215, 20), // "disconnectFromServer"
QT_MOC_LITERAL(22, 236, 14) // "processMessage"

    },
    "Client\0connected\0\0loggedIn\0loginFailed\0"
    "error\0disconnected\0messageReceived\0"
    "user\0msg\0addUser\0deleteUser\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "connectToServer\0QString&\0serverIp\0"
    "serverPort\0login\0userName\0sendMessage\0"
    "disconnectFromServer\0processMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    1,   81,    2, 0x06 /* Public */,
       6,    0,   84,    2, 0x06 /* Public */,
       7,    2,   85,    2, 0x06 /* Public */,
      10,    1,   90,    2, 0x06 /* Public */,
      11,    1,   93,    2, 0x06 /* Public */,
       5,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    2,   99,    2, 0x0a /* Public */,
      18,    1,  104,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,
      21,    0,  110,    2, 0x0a /* Public */,
      22,    0,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 12,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15, QMetaType::UShort,   16,   17,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Client *_t = static_cast<Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->loggedIn(); break;
        case 2: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->disconnected(); break;
        case 4: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->addUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->deleteUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: _t->connectToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 9: _t->login((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->disconnectFromServer(); break;
        case 12: _t->processMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::connected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::loggedIn)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::loginFailed)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Client::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::disconnected)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::messageReceived)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::addUser)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Client::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::deleteUser)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Client::*_t)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Client::error)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject Client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Client.data,
      qt_meta_data_Client,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Client.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Client::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Client::loggedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Client::loginFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Client::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Client::messageReceived(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Client::addUser(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Client::deleteUser(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Client::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
