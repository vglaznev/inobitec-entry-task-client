#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>


Chart::Chart(QGraphicsItem *parent) :
    series(nullptr),
    xAxis(new QValueAxis()),
    yAxis(new QValueAxis()),
    seriesPen(new QPen())
{
    legend()->hide();

    series = new QLineSeries(this);
    addSeries(series);
    series->setPen(*seriesPen);

    addAxis(xAxis, Qt::AlignBottom);
    addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);
    xAxis->setTickCount(5);
    xAxis->setRange(0, 6.28);
    yAxis->setRange(-1, 1);
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
}
void Chart::zoomAmplitude(){
    yAxis->setMax(yAxis->max() + 0.001);
    yAxis->setMin(yAxis->min() - 0.001);
}
void Chart::zoomPeriod(){
    xAxis->setMax(xAxis->max() + 0.1);

}
