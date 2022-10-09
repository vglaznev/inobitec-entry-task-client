#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace QtCharts {
    class QChartView;
}

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
    QtCharts::QChartView* chartView;

    const qreal xAxisMaxZoom;
    const qreal yAxisMaxZoom;

    qreal convertSliderValueToZoom(int);
};

#endif // MAINWINDOW_H
