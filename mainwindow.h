#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChartView>
#include <QtMath>
#include "chart.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_curveColorChangeButton_clicked();

signals:
    void signalCurveColorChanged(QColor, QPrivateSignal);

private:
    Ui::MainWindow *ui;
    QChartView* chartView;
};

#endif // MAINWINDOW_H
