#ifndef LEGENDDIAGRAM_H
#define LEGENDDIAGRAM_H

#include <QColor>
#include <QObject>

class LegendDiagram : public QObject
{
    Q_OBJECT
    QColor m_color;
    QString m_text;

public:
    explicit LegendDiagram(QObject *parent = nullptr);
    LegendDiagram(const LegendDiagram& legend);
    const LegendDiagram& operator=(LegendDiagram legend);

    void swap(LegendDiagram & first, LegendDiagram & second);

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

    const QColor &color() const;
    void setColor(const QColor &newColor);
    const QString &text() const;
    void setText(const QString &newText);

signals:
    void colorChanged();
    void textChanged();
};

Q_DECLARE_METATYPE(LegendDiagram);

#endif // LEGENDDIAGRAM_H
