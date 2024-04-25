TEMPLATE = lib
TARGET = test_cppmodule

QT += qml quick
QT -= gui

CONFIG += plugin c++14 qmltypes

TARGET = $$qtLibraryTarget($$TARGET)

QML_IMPORT_NAME = test_module.test_cppmodule
QML_IMPORT_MAJOR_VERSION = 0.1

uri = test_module.test_cppmodule

# Input
SOURCES += \
        $$PWD/diagrams/legenddiagram.cpp \
        $$PWD/diagrams/linediagrammodel.cpp \
        $$PWD/diagrams/valuediagram.cpp \
        $$PWD/test_cppmodule.cpp

HEADERS += \
        $$PWD/diagrams/legenddiagram.h \
        $$PWD/diagrams/linediagrammodel.h \
        $$PWD/diagrams/valuediagram.h \
        $$PWD/test_cppmodule.h

DISTFILES += \
             $$files(qml/*.qml)

OTHER_FILES = qmldir

MODULENAME = test_module/test_cppmodule
TARGETPATH = $$[QT_INSTALL_QML]/$$MODULENAME

import.files += qmldir LineDiagram.qml LineDiagramItem.qml plugin.qmltypes

import.path = $$TARGETPATH
target.path = $$TARGETPATH

qmltypes.commands = qmlplugindump  test_module.test_cppmodule 0.1 > $$TARGETPATH/plugin.qmltypes
QMAKE_EXTRA_TARGETS += qmltypes

INSTALLS += target import
