#include "test_cppmodule.h"

#include "diagrams/valuediagram.h"
#include "diagrams/linediagrammodel.h"
#include "diagrams/legenddiagram.h"

#include <qqml.h>

void TestCppModule::registerTypes(const char *uri)
{
    // @uri test_module.test_cppmodule

    qmlRegisterType<ValueDiagram>(uri, 1, 0, "ValueDiagram");
    qmlRegisterType<LegendDiagram>(uri, 1, 0, "LegendDiagram");
    qmlRegisterType<LineDiagramModel>(uri, 1, 0, "LineDiagramModel");
}

