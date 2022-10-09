#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QDebug>

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
    void zoomAmplitude(qreal);
    void zoomPeriod(qreal);

public:
    explicit Chart(QGraphicsItem *parent = nullptr);
    virtual ~Chart();

private:
    QLineSeries* series;
    QValueAxis* xAxis;
    QValueAxis* yAxis;

    QPen* seriesPen;

    const qreal DEFAULT_X_SIZE = 10;
    const qreal DEFAULT_Y_SIZE = 5;

    qreal zoomX;
    qreal zoomY;

    qreal yAxisMax;
    qreal yAxisMin;

    qreal xAxisMax;
    qreal xAxisMin;
};

#endif // CHART_H
