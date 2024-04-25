#include "test_cppmodule.h"

#include "diagrams/valuediagram.h"
#include "diagrams/linediagrammodel.h"
#include "diagrams/legenddiagram.h"

#include <qqml.h>

void Test_cppModulePlugin::registerTypes(const char *uri)
{
    // @uri test_module.test_cppmodule

    qmlRegisterType<ValueDiagram>(uri, 0,1, "ValueDiagram");
    qmlRegisterType<LegendDiagram>(uri, 0, 1, "LegendDiagram");
    qmlRegisterType<LineDiagramModel>(uri, 0, 1, "LineDiagramModel");
}

