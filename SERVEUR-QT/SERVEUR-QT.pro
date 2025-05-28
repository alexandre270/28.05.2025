# Nom de la cible et type de projet
TARGET = SERVEUR-QT
TEMPLATE = app

# Modules Qt requis
QT += core gui sql network serialport bluetooth

# Ajouter les widgets si Qt5+
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Fichiers source
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    servo_server.cpp \
    videostream.cpp \
    server.cpp \
    client.cpp \
    camera.cpp \
    dbmanager.cpp

# Fichiers d'en-tête
HEADERS += \
    mainwindow.h \
    servo_server.h \
    videostream.h \
    server.h \
    client.h \
    camera.h \
    dbmanager.h

# Fichiers d'interface utilisateur (UI)
FORMS += \
    mainwindow.ui

# Chemins d'inclusion pour FFmpeg (ajuste selon ton système)
INCLUDEPATH += /usr/include/ffmpeg

# Lier les bibliothèques FFmpeg (assure-toi qu'elles sont bien installées)
LIBS += -lavformat -lavcodec -lavutil -lswscale

# Lier la bibliothèque MySQL (si utilisée avec QSqlDatabase)
LIBS += -lmysqlclient

# Optionnel : ajouter un dossier d’images ou de ressources si nécessaire
# RESOURCES += resources.qrc
