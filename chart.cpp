#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>


Chart::Chart(QGraphicsItem *parent) :
    series(nullptr),
    xAxis(new QValueAxis()),
    yAxis(new QValueAxis()),
    seriesPen(new QPen()),
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
    series->setUseOpenGL(true); //?

    addAxis(xAxis, Qt::AlignBottom);
    addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);
    xAxis->setTickCount(5);
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
void Chart::zoomAmplitude(int delta) {
    zoomY = static_cast<qreal>(delta) / 10 + 1;
    if(zoomY != 0.0){
        yAxis->setRange(yAxisMin * zoomY, yAxisMax * zoomY);
    }
}
void Chart::zoomPeriod(int delta){
    zoomX = static_cast<qreal>(delta) / 10 + 1;
    if(zoomY != 0.0){
        xAxis->setRange(yAxisMax - (yAxisMax - yAxisMin) * zoomY, yAxisMax);
    }
}
