QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    credit.cpp \
    deposit.cpp \
    graph_parameters.cpp \
    grid_graphics.cpp \
    main.cpp \
    qcustomplot.cpp \
    s21_calc_back.c \
    s21_sm_calc.cpp \
    variable_x.cpp

HEADERS += \
    credit.h \
    deposit.h \
    graph_parameters.h \
    grid_graphics.h \
    qcustomplot.h \
    s21_calc_back.h \
    s21_sm_calc.h \
    variable_x.h

FORMS += \
    credit.ui \
    deposit.ui \
    graph_parameters.ui \
    grid_graphics.ui \
    s21_sm_calc.ui \
    variable_x.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
