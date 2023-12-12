#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDebug>

void MainWindow::on_btn_refresh_clicked()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QString> strPorts;
    while (ui->cb_port->count() > 0)
    {
        ui->cb_port->removeItem(0);
    }
    for (int i = 0; i < ports.size();i++)
    {
        strPorts.append(ports.at(i).portName() + " (" + ports.at(i).description() + ")");
    }
    ui->cb_port->addItems(strPorts);
}


void MainWindow::on_btn_connect_clicked()
{
    if (ui->btn_connect->text() == "Connect")
    {
        int space_index = ui->cb_port->currentText().indexOf(' ');
        uart.serial.setPortName(ui->cb_port->currentText().mid(0, space_index));
        uart.serial.open(QIODevice::ReadWrite);
        if (!uart.serial.isOpen())
        {

        }
        else
        {
            // qInfo() << "Connected\n";
            // qInfo() << "Baudrate: " << ui->cb_baud->currentText() << '\n';
            uart.serial.setBaudRate(ui->cb_baud->currentText().toInt());
            uart.serial.setDataBits(QSerialPort::Data8);
            uart.serial.setStopBits(QSerialPort::OneStop);
            uart.serial.setParity(QSerialPort::NoParity);

            ui->btn_connect->setText("Disconnect");
            ui->cb_port->setDisabled(true);
            ui->cb_baud->setDisabled(true);
            ui->btn_refresh->setDisabled(true);
            ui->btn_run->setDisabled(false);
        }
    }
    else
    {
        uart.serial.close();
        ui->btn_connect->setText("Connect");
        ui->cb_port->setDisabled(false);
        ui->cb_baud->setDisabled(false);
        ui->btn_refresh->setDisabled(false);
        ui->btn_run->setDisabled(true);
    }
}


void MainWindow::on_btn_run_clicked()
{
    if (ui->btn_run->text() == "Run")
    {
        this->timer.start(10);
        ui->btn_run->setText("Stop");
        ui->btn_connect->setDisabled(true);
        ui->btn_saveGraph->setDisabled(true);
        ui->btn_clear->setDisabled(true);
        ui->gb_horizontal->setDisabled(true);
        ui->gb_vertical->setDisabled(true);
        ui->gb_dataScale->setDisabled(true);

        ui->graph->xAxis->setRange(0, ui->sb_numSamples->value());
        ui->graph->yAxis->setRange(ui->dsb_min->value(), ui->dsb_max->value());
        ui->graph->replot();
        ui->graph->update();
    }
    else
    {
        this->timer.stop();
        ui->btn_run->setText("Run");
        ui->btn_connect->setDisabled(false);
        ui->btn_saveGraph->setDisabled(false);
        ui->btn_clear->setDisabled(false);
        ui->gb_horizontal->setDisabled(false);
        ui->gb_vertical->setDisabled(false);
        ui->gb_dataScale->setDisabled(false);
        // Stop plotting
    }
}


void MainWindow::on_btn_clear_clicked()
{
    this->xVal.clear();
    this->yVal.clear();
    this->dataIndex = 0;
    this->updateLine->point1->setCoords(this->dataIndex, 1);
    this->updateLine->point2->setCoords(this->dataIndex, 2);
    ui->graph->graph(0)->data()->clear();
    ui->graph->replot();
    ui->graph->update();
}


void MainWindow::on_btn_saveGraph_clicked()
{
    QString fileName = ".\\output\\graph.jpg";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        ui->graph->saveJpg(fileName);
    }
    file.close();
}
