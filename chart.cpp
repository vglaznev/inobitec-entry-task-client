#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

Chart::Chart(QGraphicsItem *parent) :
    series(nullptr),
    xAxis(new QValueAxis()),
    yAxis(new QValueAxis()),
    seriesPen(new QPen(Qt::red)),
    zoomX(1),
    zoomY(1),
    yAxisMax(DEFAULT_Y_SIZE / 2),
    yAxisMin(-DEFAULT_Y_SIZE / 2),
    xAxisMax(DEFAULT_X_SIZE),
    xAxisMin(0)
{
    legend()->hide();

    series = new QLineSeries(this);
    addSeries(series);
    series->setPen(*seriesPen);
    series->setUseOpenGL(true);

    xAxis->setTickType(QValueAxis::TicksDynamic);
    xAxis->setTickAnchor(0.0);
    xAxis->setTickInterval(2);

    addAxis(xAxis, Qt::AlignBottom);
    addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);
    xAxis->setRange(xAxisMin, xAxisMax);
    yAxis->setRange(yAxisMin, yAxisMax);

}

Chart::~Chart()
{

}

void Chart::setSignalWidth(int width){
    seriesPen->setWidth(width);
    series->setPen(*seriesPen);

}

void Chart::setSignalColor(QColor color){
    seriesPen->setColor(color);
    series->setPen(*seriesPen);
}

void Chart::render(qreal x, qreal y){
    series->append(x, y);
    if(x > xAxis->max()){
        //scroll(x, 0);
        xAxis->setMin(xAxis->min() + (x - xAxis->max()));
        xAxis->setMax(x);
    }
    if(y < yAxisMin || y > yAxisMax){
        if(y < yAxisMin){
            yAxisMin = y;
        }
        if(y > yAxisMax){
            yAxisMax = y;
        }
        yAxis->setRange(yAxisMin * zoomY, yAxisMax * zoomY);
    }
}

void Chart::zoomAmplitude(qreal zoom) {
    if(zoom > 0){
        zoomY = zoom;
        yAxis->setRange(yAxisMin * zoomY, yAxisMax * zoomY);
    }
}

void Chart::zoomPeriod(qreal zoom){
    if(zoom > 0){
        zoomX = zoom;
        qreal lastPointInSeries = series->at(series->count() - 1).x();
        if(lastPointInSeries < xAxis->max()){
            xAxis->setMax(zoomX * xAxisMax);
        } else {
            xAxis->setMin(xAxis->max() - zoomX*(xAxisMax - xAxisMin));
        }
    }
}
