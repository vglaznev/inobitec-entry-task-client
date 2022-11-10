#include "ColorChooseWidget.h"

#include "colorbox.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QColorDialog>

ColorChooseWidget::ColorChooseWidget(QWidget* parent) :
	QWidget(parent),
	colorBox(new ColorBox(this)),
	button(new QPushButton(this))
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	colorBox->setFixedSize(QSize(20, 20));
	button->setMaximumSize(QSize(230, 23));
	layout->addWidget(colorBox, Qt::AlignLeft);
	layout->addWidget(button, Qt::AlignRight);

	connect(button, &QPushButton::clicked, this, [this]() {
		QColor color = QColorDialog::getColor(getColor(), this, "Выберите цвет");
		if (color.isValid()) {
			setColor(color);
			emit colorChanged(color);
		}
	});
}

void ColorChooseWidget::setButtonTitle(QString title) {
	button->setText(title);
}

QColor ColorChooseWidget::getColor() {
	return colorBox->getColor();
}

void ColorChooseWidget::setColor(QColor color) {
	colorBox->setColor(color);
}