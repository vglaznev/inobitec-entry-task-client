#ifndef CHART_H
#define CHART_H

#include "segmentqlineseries.h"

#include <QChart>

namespace QtCharts {
class QValueAxis;
class QLineSeries;
} // namespace QtCharts

class SegmentQLineSeries;

class Chart : public QtCharts::QChart
{
    Q_OBJECT

public slots:
    void setSignalWidth(int);
    void setSignalColor(QColor, SegmentQLineSeries::SegmentType);
    void render(QPointF);
    void zoomAmplitude(qreal);
    void zoomPeriod(qreal);
    void flush();

public:
    explicit Chart(QGraphicsItem *parent = nullptr);
    ~Chart();

private:
    //QtCharts::QLineSeries *series;
    SegmentQLineSeries* series;
    QtCharts::QValueAxis *xAxis;
    QtCharts::QValueAxis *yAxis;

    QPen seriesPen;

    const qreal DEFAULT_X_SIZE;
    const qreal DEFAULT_Y_SIZE;

    qreal zoomX;
    qreal zoomY;

    qreal yAxisMax;
    qreal yAxisMin;

    qreal xAxisMax;
    qreal xAxisMin;
};

#endif // CHART_H
