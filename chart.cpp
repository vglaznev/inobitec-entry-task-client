#include "chart.h"

#include <QValueAxis>
#include <QLineSeries>

using QtCharts::QLineSeries;
using QtCharts::QValueAxis;

Chart::Chart(QGraphicsItem *parent)
    : QtCharts::QChart(parent),
      series(new SegmentQLineSeries(this)),
      xAxis(new QValueAxis(this)),
      yAxis(new QValueAxis(this)),
      seriesPen(QPen(Qt::red)),
      DEFAULT_X_SIZE(10),
      DEFAULT_Y_SIZE(5),
      zoomX(1),
      zoomY(1),
      yAxisMax(DEFAULT_Y_SIZE / 2),
      yAxisMin(-DEFAULT_Y_SIZE / 2),
      xAxisMax(DEFAULT_X_SIZE),
      xAxisMin(0)
{
    legend()->hide();

    xAxis->setTickType(QValueAxis::TicksDynamic);
    xAxis->setTickAnchor(0.0);
    xAxis->setTickInterval(2);

    addAxis(xAxis, Qt::AlignBottom);
    addAxis(yAxis, Qt::AlignLeft);

    xAxis->setRange(xAxisMin, xAxisMax);
    yAxis->setRange(yAxisMin, yAxisMax);


    connect(series, &SegmentQLineSeries::newSegmentAppend, this, &Chart::attachNewSegment);
    connect(series, &SegmentQLineSeries::segmentRemoved, this, &Chart::removeSegment);
}

Chart::~Chart() { 
    series->clear();
}

void Chart::flush()
{
    series->clear();
    removeAllSeries();
    xAxis->setRange(0, zoomX * xAxisMax);
}

void Chart::setSignalWidth(int width)
{
    series->setWidth(width);
}

void Chart::setSignalColor(QColor color, SegmentQLineSeries::SegmentType segmentType)
{
    series->setColor(color, segmentType);
}

void Chart::render(QPointF point)
{
    series->append(point);

    // Если на графике достаточно много точек, убираем половину,
    // чтобы не терять в производительности
    // Эти точки (наиболее вероятно) не отображаются на графике
    /*if (series->count() > 2000) {
        series->replace(series->points().mid(1000, 2000));
    }*/

    // Если точка выходит за пределы абциссы, сдвигаем ось
    if (point.x() > xAxis->max()) {
        xAxis->setMin(xAxis->min() + (point.x() - xAxis->max()));
        xAxis->setMax(point.x());
    }

    // Если точка выходит за пределы ординаты, увеличиваем её границы
    if (point.y() < yAxisMin || point.y() > yAxisMax) {
        if (point.y() < yAxisMin) {
            yAxisMin = point.y();
        }
        if (point.y() > yAxisMax) {
            yAxisMax = point.y();
        }
        yAxis->setRange(yAxisMin * zoomY, yAxisMax * zoomY);
    }
}

void Chart::zoomAmplitude(qreal zoom)
{
    if (zoom > 0) {
        zoomY = zoom;
        yAxis->setRange(yAxisMin * zoomY, yAxisMax * zoomY);
    }
}

void Chart::zoomPeriod(qreal zoom)
{
    if (zoom > 0) {
        zoomX = zoom;
        if (series->size() == 0 || series->getLastPoint().x() < zoomX * DEFAULT_X_SIZE) {
            xAxis->setMax(zoomX * xAxisMax);
        } else {
            xAxis->setMin(xAxis->max() - zoomX * (xAxisMax - xAxisMin));
        }
    }
}

void Chart::attachNewSegment(QLineSeries* segment)
{
    segment->setUseOpenGL(true);
    addSeries(segment);

    segment->attachAxis(xAxis);
    segment->attachAxis(yAxis);
}

void Chart::removeSegment(QLineSeries* segment) {
    removeSeries(segment);
}