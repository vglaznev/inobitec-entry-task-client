#include "chart.h"
#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtMath>
#include <QTimer>
#include <QtWidgets>

QT_CHARTS_USE_NAMESPACE

static qreal x = 0.0;

static void modifyX(){
    x+=0.01;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Chart* chart = new Chart();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QTimer *m_timer = new QTimer();
    QObject::connect(m_timer, &QTimer::timeout, [=](){chart->render(x, qSin(x)); modifyX();});
    m_timer->setInterval(10);
    chart->setSignalWidth(4);
    chart->setSignalColor(Qt::red);
    m_timer->start();

    MainWindow w;
    w.setCentralWidget(chartView);
    w.show();

    return a.exec();
}
