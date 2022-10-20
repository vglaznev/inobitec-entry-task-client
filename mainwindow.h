#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Client;
class Timer;

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
    void renderNewPoint(QPointF, QPrivateSignal);

private:
    Ui::MainWindow *ui;

    Client* networkClient;
    QThread* networkThread;

    qreal convertSliderValueToZoom(int);

};

#endif // MAINWINDOW_H
