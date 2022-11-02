#include "chart.h"

#include <QValueAxis>
#include <QLineSeries>

Chart::Chart(QGraphicsItem *parent)
    : QChart(parent),
      increasingSeries(new QLineSeries(this)),
      decreasingSeries(new QLineSeries(this)),
      xAxis(new QValueAxis(this)),
      yAxis(new QValueAxis(this)),
      lastPoint(QPointF(0.0, 0.0)),
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

    addSeries(increasingSeries);
    addSeries(decreasingSeries);
    
    decreasingSeries->setPen(QPen(Qt::red));
    decreasingSeries->setPen(QPen(Qt::blue));

    increasingSeries->setUseOpenGL(true);
    decreasingSeries->setUseOpenGL(true);

    xAxis->setTickType(QValueAxis::TicksDynamic);
    xAxis->setTickAnchor(0.0);
    xAxis->setTickInterval(2);

    addAxis(xAxis, Qt::AlignBottom);
    addAxis(yAxis, Qt::AlignLeft);

    increasingSeries->attachAxis(xAxis);
    increasingSeries->attachAxis(yAxis);
    decreasingSeries->attachAxis(xAxis);
    decreasingSeries->attachAxis(yAxis);

    xAxis->setRange(xAxisMin, xAxisMax);
    yAxis->setRange(yAxisMin, yAxisMax);
}

Chart::~Chart() { }

void Chart::flush()
{
    increasingSeries->clear();
    decreasingSeries->clear();
    xAxis->setRange(0, zoomX * xAxisMax);
}

void Chart::setSignalWidth(int width)
{
    QPen pen = increasingSeries->pen();
    pen.setWidth(width);
    increasingSeries->setPen(pen);

    pen = decreasingSeries->pen();
    pen.setWidth(width);
    decreasingSeries->setPen(pen);
}

void Chart::setSignalColorIncreasing(QColor color)
{
    QPen pen = increasingSeries->pen();
    pen.setColor(color);
    increasingSeries->setPen(pen);
}

void Chart::setSignalColorDecreasing(QColor color)
{
    QPen pen = decreasingSeries->pen();
    pen.setColor(color);
    increasingSeries->setPen(pen);
}

void Chart::render(QPointF point)
{
    QLineSeries* series = point.y() > lastPoint.y() ? increasingSeries : decreasingSeries;

    series->append(point);

    // Если на графике достаточно много точек, убираем половину,
    // чтобы не терять в производительности
    // Эти точки (наиболее вероятно) не отображаются на графике
    if (series->count() > 2000) {
        series->replace(series->points().mid(1000, 2000));
    }

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

    lastPoint = point;
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
        if (lastPoint.x() < zoomX * DEFAULT_X_SIZE) {
            xAxis->setMax(zoomX * xAxisMax);
        } else {
            xAxis->setMin(xAxis->max() - zoomX * (xAxisMax - xAxisMin));
        }
    }
}
