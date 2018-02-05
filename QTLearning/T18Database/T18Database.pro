HEADERS += \
    Widget01.h \
    Widget02.h \
    Widget03.h \
    Widget04.h \
    Contact.h \
    Widget05.h

SOURCES += \
    Widget01.cpp \
    main.cpp \
    Widget02.cpp \
    Widget03.cpp \
    Widget04.cpp \
    Contact.cpp \
    Widget05.cpp

QT += gui widgets sql

CONFIG += C++11

INCLUDEPATH += "C:\Program Files\MySQL\MySQL Server 5.6\include"
LIBS += "C:\Program Files\MySQL\MySQL Server 5.6\lib\libmysql.lib"
