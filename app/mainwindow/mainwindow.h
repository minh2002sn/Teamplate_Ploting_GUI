#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include "qcustomplot.h"
#include "uart.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

enum Frame
{
    START_OF_TEXT = 0x02,
    END_OF_TEXT = 0x03,
};

enum RxState
{
    WAITING_SOT,
    WAITING_DATA,
    WAITING_EOT,
};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void plotData(unsigned char *rxData);

    void plotting();

private slots:
    void on_btn_refresh_clicked();

    void on_btn_connect_clicked();

    void on_btn_run_clicked();

    void on_btn_clear_clicked();

    void on_btn_saveGraph_clicked();

    void on_rbtn_xFixRange_clicked(bool checked);

    void on_rbtn_xAutoScale_clicked(bool checked);

    void on_sb_numSamples_valueChanged(int arg1);

    void on_rbtn_yFixRange_clicked(bool checked);

    void on_rbtn_yAutoScale_clicked(bool checked);

    void on_chb_scaleEnable_clicked(bool checked);


private:
    Ui::MainWindow *ui;
    Uart uart;
    // QSerialPort serial;
    QVector<double> xVal;
    QVector<double> yVal;
    QCPItemStraightLine *updateLine;
    qint64 dataIndex;
    QTimer timer;
};
#endif // MAINWINDOW_H
