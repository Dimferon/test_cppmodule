#include "linediagrammodel.h"

#include <QDebug>

LineDiagramModel::LineDiagramModel(QObject *parent) : QObject(parent)
{
}

void LineDiagramModel::addValue(QString text, QList<float> values)
{
    ValueDiagram *val = new ValueDiagram(text, QVariant::fromValue(values));
    if(val->isCorrect())
    {
        mValues.push_back(val);
    }else{
        delete val;
    }
    emit diagramValuesChanged();
}

QList<LegendDiagram> LineDiagramModel::getLegends()
{
    QList<LegendDiagram> legends;
    for(auto it = m_diagramLegends.begin(); it != m_diagramLegends.end(); it++){
        legends.push_back(**it);
    };
    return legends;
}

void LineDiagramModel::clearValue()
{
    mValues.clear();
    emit diagramValuesChanged();
}

QQmlListProperty<ValueDiagram> LineDiagramModel::diagramValues()
{
    return QQmlListProperty<ValueDiagram>(
                this,
                &mValues,
                &LineDiagramModel::valuesListAppend,
                &LineDiagramModel::valuesListCount,
                &LineDiagramModel::valuesListAt,
                &LineDiagramModel::valuesListClear);
}

void LineDiagramModel::valuesListAppend(QQmlListProperty<ValueDiagram>* list, ValueDiagram* mfd)
{
    ValueDiagramListPtr* pList = reinterpret_cast<ValueDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    pList->append( mfd );
}

int LineDiagramModel::valuesListCount(QQmlListProperty<ValueDiagram>* list )
{
    ValueDiagramListPtr* pList = reinterpret_cast<ValueDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    return pList->count();
}

ValueDiagram* LineDiagramModel::valuesListAt(QQmlListProperty<ValueDiagram>* list, int idx)
{
    ValueDiagramListPtr* pList = reinterpret_cast<ValueDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    return pList->at( idx );
}

void LineDiagramModel::valuesListClear(QQmlListProperty<ValueDiagram> *list)
{
    ValueDiagramListPtr* pList = reinterpret_cast<ValueDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    return pList->clear();
}


QQmlListProperty<LegendDiagram> LineDiagramModel::diagramLegends()
{
    return { this, &m_diagramLegends,
          &LineDiagramModel::legendsListAppend,
          &LineDiagramModel::legendsListCount,
          &LineDiagramModel::legendsListAt,
          &LineDiagramModel::legendsListClear
    };
}

void LineDiagramModel::legendsListAppend(QQmlListProperty<LegendDiagram>* list, LegendDiagram* mfd)
{
    LegendDiagramListPtr* pList = reinterpret_cast<LegendDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    pList->append( mfd );
}

int LineDiagramModel::legendsListCount(QQmlListProperty<LegendDiagram>* list )
{
    LegendDiagramListPtr* pList = reinterpret_cast<LegendDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    return pList->count();
}

LegendDiagram* LineDiagramModel::legendsListAt(QQmlListProperty<LegendDiagram>* list, int idx)
{
    LegendDiagramListPtr* pList = reinterpret_cast<LegendDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    return pList->at( idx );
}

void LineDiagramModel::legendsListClear(QQmlListProperty<LegendDiagram> *list)
{
    LegendDiagramListPtr* pList = reinterpret_cast<LegendDiagramListPtr*>( list->data );
    Q_ASSERT( pList );
    return pList->clear();
}

void LineDiagramModel::updateMaxValue()
{
    float newMaxValue=0;
    if(needFindMaxValue()  && mValues.count()>0)
    {
        newMaxValue = (*mValues.begin())->maxVal();
        std::for_each(mValues.begin(), mValues.end(), [&newMaxValue](const ValueDiagram* val){
            if(val->maxVal() > newMaxValue)
            {
                newMaxValue = val->maxVal();
            }
        });
        setMaxValueDiagram(newMaxValue);
    }
}

bool LineDiagramModel::needFindMaxValue() const
{
    return m_needFindMaxValue;
}

void LineDiagramModel::setNeedFindMaxValue(bool newNeedFindMaxValue)
{
    if (m_needFindMaxValue == newNeedFindMaxValue)
        return;
    m_needFindMaxValue = newNeedFindMaxValue;
    emit needFindMaxValueChanged();
}

qreal LineDiagramModel::diagramMaxValue() const
{
    return m_maxValueDiagram;
}

void LineDiagramModel::setMaxValueDiagram(qreal newMaxValueDiagram)
{
    if (not qFuzzyCompare(m_maxValueDiagram, newMaxValueDiagram))
    {
        m_maxValueDiagram = newMaxValueDiagram;
    }
    emit diagramMaxValueChanged();
}
