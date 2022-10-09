#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chart.h"

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
        static qreal x = 0;
        chart->render(static_cast<qreal>(currentTimeTimer->elapsed()) / 1e3, sin(x));
        x+=0.01;
    });

    layout()->addWidget(chartView);


    connect(ui->amplitudeZoomSlider, &QSlider::valueChanged,
            [=](int value){
                chart->zoomAmplitude(convertSliderValueToZoom(value));
    });
    connect(ui->periodZoomSlider, &QSlider::valueChanged,
            [=](int value){
                chart->zoomPeriod(convertSliderValueToZoom(value));
    });

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

qreal MainWindow::convertSliderValueToZoom(int value){
    return static_cast<qreal>(value) / 10 + 1.1;
}
