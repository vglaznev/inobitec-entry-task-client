#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chart.h"
#include "client.h"
#include "timer.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    chartView(nullptr),
    networkClient(new Client()),
    //timer(new Timer()),
    pointMutex()
{
    ui->setupUi(this);

    chartView = ui->graphicsView;
    Chart* chart = new Chart();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout()->addWidget(chartView);


    //Отрисовка новой точки
    //connect(this, &MainWindow::renderNewPoint, chart, &Chart::render);

    connect(networkClient, &Client::newDataArrived, chart, &Chart::render);

    //connect(timer, &Timer::elapsed, [this](qreal x){preparePoint(x);});
    //connect(networkClient, &Client::newDataArrived, [this](qreal y){preparePoint(y);});

    //Управление амплитудой и периодом
    connect(ui->amplitudeZoomSlider, &QSlider::valueChanged,
            [=](int value){
                chart->zoomAmplitude(convertSliderValueToZoom(value));
    });
    connect(ui->periodZoomSlider, &QSlider::valueChanged,
            [=](int value){
                chart->zoomPeriod(convertSliderValueToZoom(value));
    });

    //Управление шириной сигнальной кривой
    connect(ui->curveWidthChangeSlider, &QSlider::valueChanged, chart, &Chart::setSignalWidth);

    //Управлением цветом сигнальной кривой
    connect(ui->colorBox, &ColorBox::colorChanged, chart, &Chart::setSignalColor);
    connect(this, &MainWindow::signalCurveColorChanged, ui->colorBox, &ColorBox::setColor);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::preparePoint(qreal value) {
    static bool xPresented = false;
    static bool yPresented = false;
    static QPointF point(0, 0);
    QMutexLocker lock(&pointMutex);
    if((sender() == timer) && !xPresented){
        qDebug() << "aaaa";
        point.setX(value);
    } else if (sender() == networkClient && !yPresented){
        qDebug() << "bbb";
        point.setY(value);
    }
    if(xPresented && yPresented){
       qDebug() << point;
       emit renderNewPoint(point, QPrivateSignal());
       xPresented = false;
       yPresented = false;
    }
}*/

void MainWindow::on_curveColorChangeButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red, this, tr("Выберите цвет"));
    emit signalCurveColorChanged(color, QPrivateSignal());
}


void MainWindow::on_connectionButton_clicked(bool checked)
{
    if(checked){
        networkThread = new QThread();
        //timerThread   = new QThread();

        //при старте потока подключаемся к серверу
        connect(networkThread, &QThread::started, networkClient, [this](){
            networkClient->connectToServer(ui->hostname->text(), ui->portNumber->text().toInt());
        });
        //при завершении потока отключаемся от сервера
        connect(networkThread, &QThread::finished, networkClient, &Client::disconnectFromServer);
        //если произошел разрыв соединения, завершаем поток
        connect(networkClient, &Client::disconnected, networkThread, &QThread::quit);
        //при старте потока запускаем таймер
        //connect(timerThread, &QThread::started, timer, &Timer::start);
        //фиксируем время получения новых данных
        //connect(networkClient, &Client::newDataArrived, [this](){timer->stop();});

        networkClient->moveToThread(networkThread);
        //timer->moveToThread(timerThread);

        networkThread->start();
        //timerThread->start();

        ui->connectionButton->setText("Отключиться");
    } else {
        networkThread->quit();
        //timerThread->quit();

        ui->connectionButton->setText("Подключиться");
    }
}

qreal MainWindow::convertSliderValueToZoom(int value)
{
    return static_cast<qreal>(value) / 10 + 1.1;
}
