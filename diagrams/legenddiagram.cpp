#include "legenddiagram.h"

LegendDiagram::LegendDiagram(QObject *parent) : QObject(parent)
{

}

LegendDiagram::LegendDiagram(const LegendDiagram &legend):QObject(legend.parent()){
    operator=(legend);
}

const LegendDiagram &LegendDiagram::operator=(LegendDiagram legend){
    swap(*this, legend);
    this->m_color = legend.m_color;
    this->m_text = legend.m_text;
    return *this;
}

void LegendDiagram::swap(LegendDiagram &first, LegendDiagram &second) {
    // d_ptr swap doesn't take care of parentage
    QObject * firstParent = first.parent();
    QObject * secondParent = second.parent();
    first.setParent(0);
    second.setParent(0);
    first.d_ptr.swap(second.d_ptr);
    second.setParent(firstParent);
    first.setParent(secondParent);
}

const QColor &LegendDiagram::color() const
{
    return m_color;
}

void LegendDiagram::setColor(const QColor &newColor)
{
    if (m_color == newColor)
        return;
    m_color = newColor;
    emit colorChanged();
}

const QString &LegendDiagram::text() const
{
    return m_text;
}

void LegendDiagram::setText(const QString &newText)
{
    if (m_text == newText)
        return;
    m_text = newText;
    emit textChanged();
}
