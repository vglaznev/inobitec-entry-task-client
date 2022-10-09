#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chartView(nullptr),
    xAxisMaxZoom(2),
    yAxisMaxZoom(2)
{
    ui->setupUi(this);

    chartView = ui->graphicsView;
    Chart* chart = new Chart();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QTimer* m_timer = new QTimer();
    QElapsedTimer* currentTimeTimer = new QElapsedTimer();
    m_timer->start();
    currentTimeTimer->start();

    QObject::connect(m_timer, &QTimer::timeout, [=]() mutable {
        static qreal x = 1;
        chart->render(static_cast<qreal>(currentTimeTimer->elapsed()) / 1e3, sin(x)*log(x));
        x+=0.01;
    });

    layout()->addWidget(chartView);


    connect(ui->amplitudeZoomSlider, &QSlider::valueChanged, this, &MainWindow::convertSliderToZoomRange);
    connect(ui->periodZoomSlider, &QSlider::valueChanged, this, &MainWindow::convertSliderToZoomRange);

    connect(ui->curveWidthChangeSlider, &QSlider::valueChanged, chart, &Chart::setSignalWidth);

    connect(ui->colorBox, &ColorBox::colorChanged, chart, &Chart::setSignalColor);
    connect(this, &MainWindow::signalCurveColorChanged, ui->colorBox, &ColorBox::setColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_curveColorChangeButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red, this, tr("Выберите цвет"));
    emit signalCurveColorChanged(color, QPrivateSignal());
}

void MainWindow::convertSliderToZoomRange(int value){
    QObject* obj = sender();
    qreal zoom = static_cast<qreal>(value) / 10 + 1.1;
    if(obj == ui->amplitudeZoomSlider){
        static_cast<Chart*>(ui->graphicsView->chart())->zoomAmplitude(zoom);
    } else if(obj == ui->periodZoomSlider){
        static_cast<Chart*>(ui->graphicsView->chart())->zoomPeriod(zoom);
    }
}
