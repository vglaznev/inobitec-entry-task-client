#ifndef COLORBOX_H
#define COLORBOX_H

#include <QLabel>

class ColorBox : public QLabel
{
    Q_OBJECT
public:
    explicit ColorBox(QWidget *parent = nullptr);
    ~ColorBox();

    QColor getColor();

public slots:
    void setColor(QColor);

signals:
    void colorChanged(QColor);
};

#endif // COLORBOX_H
