#ifndef VALUEDIAGRAM_H
#define VALUEDIAGRAM_H

#include <QList>
#include <QObject>
#include <QVariant>

class ValueDiagram: public QObject
{
    Q_OBJECT

public:
    explicit ValueDiagram(QObject *parent = nullptr);
    explicit ValueDiagram(QString text, QVariant value, QObject *parent = nullptr);
    ValueDiagram(const ValueDiagram &t);
    ValueDiagram &operator=(const ValueDiagram &t);

    Q_PROPERTY(bool isCorrect READ isCorrect WRITE setIsCorrect NOTIFY isCorrectChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QList<float> values READ values WRITE setValues NOTIFY valuesChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(float maxVal READ maxVal NOTIFY maxValChanged)

    const QString &text() const;
    void setText(const QString &newText);

    const QList<float> values() const;
    void setValues(const QList<float> &newValues);

    int count() const;

    float maxVal() const;

    bool isCorrect() const;
    void setIsCorrect(bool newIsCorrect);

public slots:
    void updateMax();

signals:
    void textChanged();
    void valuesChanged();
    void countChanged();
    void maxValChanged();
    void isCorrectChanged();

private:
    QString m_text;
    QList<float> m_values;

    float m_maxVal;

    bool m_isCorrect;
};

Q_DECLARE_METATYPE(ValueDiagram);

#endif // VALUEDIAGRAM_H
