TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    album.cpp \
    artistas.cpp \
    cancion.cpp \
    creditos.cpp \
    interfaz.cpp \
    playlist.cpp \
    usuario.cpp

HEADERS += \
    album.h \
    artistas.h \
    cancion.h \
    config.h \
    creditos.h \
    interfaz.h \
    playlist.h \
    usuario.h

DISTFILES += \
    ads.dat \
    songs.dat \
    songs.txt \
    users.dat \
    users.txt
