#include "valuediagram.h"
#include <QDebug>

ValueDiagram::ValueDiagram(QObject *parent): QObject(parent)
{
    connect(this, &ValueDiagram::countChanged, this, &ValueDiagram::updateMax);
}

ValueDiagram::ValueDiagram(QString text, QVariant value, QObject *parent): QObject(parent)
{
    connect(this, &ValueDiagram::countChanged, this, &ValueDiagram::updateMax);
    QList<float> vals;
    switch (value.type()) {
    case QVariant::Double:
    case QVariant::Int:
    {
        vals.append(value.toFloat());
    }break;
    case QVariant::List:{
        auto list = value.toList();
        std::for_each(list.begin(), list.end(), [&vals](const QVariant& vItem){
           vals.append(vItem.toFloat());
        });
        setValues(vals);
    }break;

    default:
        if( value.canConvert<QList<float>>() ){
            vals = value.value<QList<float>>();
        }else {
            setIsCorrect(false);
            return;
        }
    }
    setIsCorrect(true);
    setText(text);
    setValues(vals);
}

ValueDiagram::ValueDiagram(const ValueDiagram &t):QObject(t.parent())
{
    connect(this, &ValueDiagram::countChanged, this, &ValueDiagram::updateMax);
    this->operator=(t);
}

ValueDiagram &ValueDiagram::operator=(const ValueDiagram &t)
{
    m_isCorrect = t.m_isCorrect;
    m_maxVal= t.m_maxVal;
    m_text= t.m_text;
    m_values= t.m_values;
    return *this;
}

const QString &ValueDiagram::text() const
{
    return m_text;
}

void ValueDiagram::setText(const QString &newText)
{
    if (m_text == newText)
        return;
    m_text = newText;
    emit textChanged();
}

const QList<float> ValueDiagram::values() const
{
    return m_values;
}

void ValueDiagram::setValues(const QList<float> &newValues)
{
    if (m_values == newValues)
        return;
    m_values = newValues;

    emit valuesChanged();
    emit countChanged();
}

int ValueDiagram::count() const
{
    return m_values.count();
}

float ValueDiagram::maxVal() const
{
    return m_maxVal;
}

bool ValueDiagram::isCorrect() const
{
    return m_isCorrect;
}

void ValueDiagram::setIsCorrect(bool newIsCorrect)
{
    if (m_isCorrect == newIsCorrect)
        return;
    m_isCorrect = newIsCorrect;
    emit isCorrectChanged();
}

void ValueDiagram::updateMax()
{
    if(m_values.count() > 0)
    {
        m_maxVal = *m_values.begin();
        std::for_each(m_values.begin(), m_values.end(), [this](const float& val) {
            if(val > m_maxVal) {
                m_maxVal = val;
            }
        });
        emit maxValChanged();
    }
}
