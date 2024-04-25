#ifndef CHART_PLUGIN_H
#define CHART_PLUGIN_H

#include <QQmlExtensionPlugin>

class Test_cppModulePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // MRMCHART_PLUGIN_H
