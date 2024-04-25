TEMPLATE = lib
TARGET = ExampleModule

QT += qml quick
QT -= gui

CONFIG += plugin c++14 qmltypes

TARGET = $$qtLibraryTarget($$TARGET)

QML_IMPORT_NAME = test_module
QML_IMPORT_MAJOR_VERSION = 0.1

uri = test_module.chart

# Input
SOURCES += \
        $$PWD/diagrams/legenddiagram.cpp \
        $$PWD/diagrams/linediagrammodel.cpp \
        $$PWD/diagrams/valuediagram.cpp \
        $$PWD/chart_plugin.cpp

HEADERS += \
        $$PWD/diagrams/legenddiagram.h \
        $$PWD/diagrams/linediagrammodel.h \
        $$PWD/diagrams/valuediagram.h \
        $$PWD/chart_plugin.h

DISTFILES += \
             $$files(qml/*.qml)

OTHER_FILES = qmldir

MODULENAME = test_module/chart
TARGETPATH = $$[QT_INSTALL_QML]/$$MODULENAME

import.files += qmldir LineDiagram.qml LineDiagramItem.qml plugin.qmltypes

import.path = $$TARGETPATH
target.path = $$TARGETPATH

qmltypes.commands = qmlplugindump  test_module.chart 0.1 > $$TARGETPATH/plugin.qmltypes
QMAKE_EXTRA_TARGETS += qmltypes

INSTALLS += target import
