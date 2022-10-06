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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
