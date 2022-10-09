#ifndef CHART_H
#define CHART_H

#include <QChart>

namespace QtCharts {
   class QValueAxis;
   class QLineSeries;
}

class Chart : public QtCharts::QChart
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
    QtCharts::QLineSeries* series;
    QtCharts::QValueAxis* xAxis;
    QtCharts::QValueAxis* yAxis;

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
