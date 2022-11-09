#ifndef COLORCHOOSEWIDGET_H
#define COLORCHOOSEWIDGET_H

#include <QWidget>

class ColorBox;
class QPushButton;

class ColorChooseWidget : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(QString buttonTitle WRITE setButtonTitle)
	Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)

public:

	explicit ColorChooseWidget(QWidget* parent = nullptr);

	void setButtonTitle(QString title);

	QColor getColor();
	void setColor(QColor);


signals:
	void colorChanged(QColor);

private:
	ColorBox* colorBox;
	QPushButton* button;
};

#endif

