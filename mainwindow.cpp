#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chartView(nullptr),
    x(1.0)
{
    ui->setupUi(this);

    chartView = ui->graphicsView;
    Chart* chart = new Chart();

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing); //?

    QTimer *m_timer = new QTimer();
    QObject::connect(m_timer, &QTimer::timeout, [=](){chart->render(x, sin(x)*log(x)); x+=0.01;});
    m_timer->setInterval(1);
    chart->setSignalWidth(4);
    chart->setSignalColor(Qt::red);
    m_timer->start();

    layout()->addWidget(chartView);
    connect(ui->horizontalSlider, &QSlider::valueChanged, chart, &Chart::setSignalWidth);
    connect(ui->verticalSlider, &QSlider::valueChanged, chart, &Chart::zoomAmplitude);
    //connect(ui->horizontalSlider_2, &QSlider::valueChanged, chart, &Chart::zoomPeriod);
}

MainWindow::~MainWindow()
{
    delete ui;
}
