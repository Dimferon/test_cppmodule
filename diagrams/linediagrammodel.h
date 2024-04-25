#ifndef LINEDIAGRAMMODEL_H
#define LINEDIAGRAMMODEL_H

#include "legenddiagram.h"
#include "valuediagram.h"

#include <QAbstractTableModel>
#include <QQmlListProperty>
#include <QQmlParserStatus>

using LegendDiagramListPtr = QList<LegendDiagram*>;
using ValueDiagramListPtr = QList<ValueDiagram*>;

class LineDiagramModel : public QObject
{
    Q_OBJECT
public:
    explicit LineDiagramModel(QObject *parent = nullptr);

    Q_PROPERTY( QQmlListProperty<ValueDiagram> diagramValues
               READ diagramValues NOTIFY diagramValuesChanged)

    Q_PROPERTY( QQmlListProperty<LegendDiagram> legends
               READ diagramLegends NOTIFY diagramValuesChanged)

    Q_PROPERTY(bool needFindMaxValue READ needFindMaxValue  WRITE setNeedFindMaxValue  NOTIFY needFindMaxValueChanged)
    Q_PROPERTY(qreal diagramMaxValue READ diagramMaxValue NOTIFY diagramMaxValueChanged)

    Q_INVOKABLE void addValue(QString text, QList<float> values);

    Q_INVOKABLE QList<LegendDiagram> getLegends();

    Q_INVOKABLE void clearValue();

public:

    qreal maxValue() const;

    bool needFindMaxValue() const;
    void setNeedFindMaxValue(bool newNeedFindMaxValue);

    qreal diagramMaxValue() const;
    void setMaxValueDiagram(qreal newMaxValueDiagram);

protected slots:
    void updateMaxValue();

signals:
    void diagramLegendsChanged();
    void diagramValuesChanged();

    void needFindMaxValueChanged();


    void diagramMaxValueChanged();

private:
    QQmlListProperty<ValueDiagram> diagramValues();

    static void valuesListAppend(QQmlListProperty<ValueDiagram>* list, ValueDiagram* mfd);
    static int valuesListCount(QQmlListProperty<ValueDiagram>* list );
    static ValueDiagram* valuesListAt(QQmlListProperty<ValueDiagram>* list, int idx);
    static void valuesListClear(QQmlListProperty<ValueDiagram>* list );

private:
    QQmlListProperty<LegendDiagram> diagramLegends();

    static void legendsListAppend(QQmlListProperty<LegendDiagram>* list, LegendDiagram* mfd);
    static int legendsListCount(QQmlListProperty<LegendDiagram>* list );
    static LegendDiagram* legendsListAt(QQmlListProperty<LegendDiagram>* list, int idx);
    static void legendsListClear(QQmlListProperty<LegendDiagram>* list );

private:
    ValueDiagramListPtr mValues;
    LegendDiagramListPtr m_diagramLegends;
    bool m_needFindMaxValue{true};
    qreal m_maxValueDiagram;
};

#endif // LINEDIAGRAMMODEL_H
