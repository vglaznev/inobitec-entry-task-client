#include "mainwindow.h"

#include <QMessageBox>
#include <QTcpSocket>

#include "chart.h"
#include "client.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), networkClient(new Client())
{
    ui->setupUi(this);

    QChartView *chartView = ui->graphicsView;
    Chart *chart = new Chart();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout()->addWidget(chartView);

    // Отрисовка нового значения
    connect(networkClient, &Client::newDataArrived,
            [chart](qreal x, qreal y) { chart->render(QPointF(x, y)); });

    // Управление амплитудой и периодом
    connect(ui->amplitudeZoomSlider, &QSlider::valueChanged,
            [this, chart](int value) { chart->zoomAmplitude(convertSliderValueToZoom(value)); });
    connect(ui->periodZoomSlider, &QSlider::valueChanged,
            [this, chart](int value) { chart->zoomPeriod(convertSliderValueToZoom(value)); });

    // Управление толщиной сигнальной кривой
    connect(ui->curveWidthChangeSlider, &QSlider::valueChanged, chart, &Chart::setSignalWidth);

    // Управлением цветом сигнальной кривой
    connect(ui->colorBox, &ColorBox::colorChanged, chart, &Chart::setSignalColor);
    connect(this, &MainWindow::signalCurveColorChanged, ui->colorBox, &ColorBox::setColor);

    connect(networkClient, &Client::connectionFailed, this, [this]() {
        QMessageBox::warning(this, "Ошибка подключения",
                             "Не удалось подключиться по указанному порту");
    });

    connect(networkClient, &Client::connected, this,
            [this]() { ui->connectionButton->setText("Закрыть подключение"); });

    connect(networkClient, &Client::disconnected, this,
            [this]() { ui->connectionButton->setText("Открыть подключение"); });

    // Очищаем область с сигналом после коннекта, чтобы отрисовка происходила корректно
    connect(networkClient, &Client::connected, chart, &Chart::flush);

    connect(ui->connectionButton, &QPushButton::clicked, networkClient, [this](bool checked) {
        if (checked) {
            networkClient->connectToServer(ui->hostname->text(), ui->portNumber->text().toInt());
        } else {
            networkClient->disconnectFromServer();
        }
    });

    networkThread = new QThread(this);
    networkClient->moveToThread(networkThread);
    networkThread->start();
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

qreal MainWindow::convertSliderValueToZoom(int value)
{
    // Приводим диапазон слайдера -10, -9, .., -10 к отрезку [0.1, 2.1]
    return static_cast<qreal>(value) / 10 + 1.1;
}
