#ifndef CHART_H
#define CHART_H

#include <QChart>

class QLineSeries;
class QValueAxis;
class SegmentQLineSeries;

class Chart : public QChart
{
    Q_OBJECT

public slots:
    void setSignalWidth(int);
    void setSignalColorIncreasing(QColor);
    void setSignalColorDecreasing(QColor);
    void render(QPointF);
    void zoomAmplitude(qreal);
    void zoomPeriod(qreal);
    void flush();

public:
    explicit Chart(QGraphicsItem *parent = nullptr);
    ~Chart();

private:
    SegmentQLineSeries *series;
    QValueAxis *xAxis;
    QValueAxis *yAxis;
    
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
