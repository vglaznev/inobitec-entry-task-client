#include <QApplication>
#include <QMainWindow>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QtMath>
#include <QTimer>

QT_CHARTS_USE_NAMESPACE

static qreal x = 0.0;

static void modifyX(){
    x+=0.01;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineSeries* series= new QLineSeries();

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QPen pen(QRgb(0x00000));
    pen.setWidth(2);
    series->setPen(pen);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QTimer *m_timer = new QTimer();
    QObject::connect(m_timer, &QTimer::timeout,
                     [=](){series->append(x, qSin(x));
                        modifyX();
                       chart->scroll(1, 0);
        });
    m_timer->setInterval(20);
    m_timer->start();

    QMainWindow w;
    w.setCentralWidget(chartView);
    w.resize(500, 300);
    w.show();

    return a.exec();
}
