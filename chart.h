#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
    Q_OBJECT

public slots:
    void setSignalWidth(int);
    void setSignalColor(QColor);
    void render(qreal x, qreal y);
    void zoomAmplitude();
    void zoomPeriod();

public:
    Chart(QGraphicsItem *parent = nullptr);
    virtual ~Chart();

private:
    QLineSeries* series;
    QValueAxis* xAxis;
    QValueAxis* yAxis;

    QPen* seriesPen;
};

#endif // CHART_H
