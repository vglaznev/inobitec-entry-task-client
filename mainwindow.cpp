#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chartView(nullptr)
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

    m_timer->setInterval(10);
    chart->setSignalWidth(4);
    chart->setSignalColor(Qt::red);

    layout()->addWidget(chartView);

    connect(ui->amplitudeZoomSlider, &QSlider::valueChanged, chart, &Chart::zoomAmplitude);
    connect(ui->periodZoomSlider, &QSlider::valueChanged, chart, &Chart::zoomPeriod);

    connect(ui->curveWidthChangeSlider, &QSlider::valueChanged, chart, &Chart::setSignalWidth);
    connect(this, &MainWindow::signalCurveColorChanged, chart, &Chart::setSignalColor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_curveColorChangeButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, tr("Выберите цвет"));
    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->backgroundRole(), color);
    ui->label->setPalette(palette);
    emit signalCurveColorChanged(color, QPrivateSignal());
}
