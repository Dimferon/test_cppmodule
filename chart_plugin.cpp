#include "chart_plugin.h"

#include "diagmrams/valuediagram.h"
#include "diagmrams/linediagrammodel.h"
#include "diagmrams/legenddiagram.h"

#include <qqml.h>

void ChartPlugin::registerTypes(const char *uri)
{
    // @uri test_module.chart

    qmlRegisterType<ValueDiagram>(uri, 1, 0, "ValueDiagram");
    qmlRegisterType<LegendDiagram>(uri, 1, 0, "LegendDiagram");
    qmlRegisterType<LineDiagramModel>(uri, 1, 0, "LineDiagramModel");
}

