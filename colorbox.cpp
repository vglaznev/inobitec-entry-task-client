#include "colorbox.h"

ColorBox::ColorBox(QWidget *parent) : QLabel(parent)
{
    setAttribute(Qt::WA_SetPalette, false);
    setAutoFillBackground(true);
    setColor(Qt::red);
}

ColorBox::~ColorBox() { }

void ColorBox::setColor(QColor color)
{
    QPalette style = palette();
    style.setColor(backgroundRole(), color);
    setPalette(style);
    emit colorChanged(color);
}

QColor ColorBox::getColor() {
    return palette().color(backgroundRole());
}