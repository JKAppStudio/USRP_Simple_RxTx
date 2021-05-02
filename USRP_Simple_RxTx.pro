QT += quick \
    widgets \
    gui     \
    quickcontrols2

CONFIG += c++17\

macx: {
CONFIG += sdk_no_version_check \
          lib_no_version_check
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/UHDGUIWrapper.cpp \
    Sources/UhdDeviceList.cpp \
    main.cpp

HEADERS += \
    Include/UHDGUIWrapper.h \
    Include/UhdDevicesList.h

RESOURCES += qml.qrc


INCLUDEPATH += \
            Include \
            /usr/local/include
macx: {
INCLUDEPATH += \
            /opt/local/include
}


DEPENDPATH += \
            /usr/local/include \

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = GUI/Controls \

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/release/ -luhd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/debug/ -luhd
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -luhd


