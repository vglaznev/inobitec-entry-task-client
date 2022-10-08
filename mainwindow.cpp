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

    QTimer* m_timer = new QTimer();
    QElapsedTimer* currentTimeTimer = new QElapsedTimer();
    m_timer->start();
    currentTimeTimer->start();

    QObject::connect(m_timer, &QTimer::timeout, [=](){chart->render(static_cast<qreal>(currentTimeTimer->elapsed()) / 1e3, sin(x)*log(x)); x+=0.01;});

    m_timer->setInterval(10);
    chart->setSignalWidth(4);
    chart->setSignalColor(Qt::red);

    layout()->addWidget(chartView);
    connect(ui->horizontalSlider, &QSlider::valueChanged, chart, &Chart::setSignalWidth);
    connect(ui->verticalSlider, &QSlider::valueChanged, chart, &Chart::zoomAmplitude);
    connect(this, &MainWindow::signalCurveColorChanged, chart, &Chart::setSignalColor);
    connect(ui->horizontalSlider_2, &QSlider::valueChanged, chart, &Chart::zoomPeriod);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, tr("Выберите цвет"));
    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->backgroundRole(), color);
    ui->label->setPalette(palette);
    emit signalCurveColorChanged(color, QPrivateSignal());

    qDebug() << color;
}
