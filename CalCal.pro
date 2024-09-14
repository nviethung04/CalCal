QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/report.cpp \
    src/btap_calo_out.cpp \
    src/btaptab.cpp \
    src/databasemanager.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/inputdialog.cpp \
    src/personalinfo.cpp \
    src/food_calo_in.cpp \
    src/foodtab.cpp

HEADERS += \
    include/btap_calo_out.h \
    include/btaptab.h \
    include/databasemanager.h \
    include/mainwindow.h \
    include/inputdialog.h \
    include/personalinfo.h \
    include/food_calo_in.h \
    include/foodtab.h \
    include/report.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    forms/btap_calo_out.ui \
    forms/btaptab.ui \
    forms/mainwindow.ui \
    forms/inputdialog.ui \
    forms/personalinfo.ui \
    forms/food_calo_in.ui \
    forms/foodtab.ui \
    forms/report.ui

DISTFILES += \
    data/CalCaldb.db
