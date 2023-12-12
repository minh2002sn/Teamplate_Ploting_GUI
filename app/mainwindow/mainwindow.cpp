#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->dataIndex = 0;

    // Connect signal to slot
    connect(&uart, &Uart::readDone, this, &MainWindow::plotData);
    // connect(&serial, &QSerialPort::readyRead, this, &MainWindow::rxData);
    connect(&timer, &QTimer::timeout, this, &MainWindow::plotting);

    setFixedSize(width(), height());
    setWindowTitle("[Deltacross] Plotting");

    // Serial port init
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QList<QString> strPorts;
    for (int i = 0; i < ports.size();i++)
    {
        strPorts.append(ports.at(i).portName() + " (" + ports.at(i).description() + ")");
    }
    ui->cb_port->addItems(strPorts);

    // Disable run button
    ui->btn_run->setDisabled(true);

    // Find baudrate and set initial baudrate
    QList<qint32> baudrates = QSerialPortInfo::standardBaudRates();
    QList<QString> strBaudrates;
    for(int i = 0; i < baudrates.size(); i++)
    {
        strBaudrates.append(QString::number(baudrates.at(i)));
    }
    ui->cb_baud->addItems(strBaudrates);
    ui->cb_baud->setCurrentText("115200");

    //Init graph
    ui->graph->addGraph();
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ScatterShape::ssNone);
    ui->graph->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->graph->xAxis->setRange(0, ui->sb_numSamples->value());
    ui->graph->yAxis->setRange(ui->dsb_min->value(), ui->dsb_max->value());
    ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    this->updateLine = new QCPItemStraightLine(ui->graph);
    this->updateLine->point1->setCoords(this->dataIndex, 1);
    this->updateLine->point2->setCoords(this->dataIndex, 2);

    // Disable data scale
    ui->chb_scaleEnable->setCheckState(Qt::CheckState::Checked);
    ui->dsb_minRaw->setValue(0);
    ui->dsb_maxRaw->setValue(4095);
    ui->dsb_minScale->setValue(0);
    ui->dsb_maxScale->setValue(3.3);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotting()
{
    this->updateLine->point1->setCoords(this->dataIndex, 1);
    this->updateLine->point2->setCoords(this->dataIndex, 2);
    ui->graph->graph(0)->setData(this->xVal, this->yVal);
    // ui->graph->rescaleAxes();
    ui->graph->replot();
    ui->graph->update();
}

void MainWindow::plotData(unsigned char *rxData)
{
    if (ui->btn_run->text() != "Run")
    {
        // this->yVal.append((*(quint32 *)rxBuff)*3.3/4095);
        double minRaw = ui->dsb_minRaw->value();
        double maxRaw = ui->dsb_maxRaw->value();
        double minScale = ui->dsb_minScale->value();
        double maxScale = ui->dsb_maxScale->value();
        double val = (*(quint32 *)rxData - minRaw)*(maxScale - minScale)/(maxRaw - minRaw) + minScale;
        // qInfo() << val << '\n';
        if (this->yVal.size() < ui->sb_numSamples->value())
        {
            this->xVal.append(dataIndex);
            this->yVal.append(val);
        }
        else
        {
            // qInfo() << "dataIndex: " << dataIndex << '\n';
            this->yVal[dataIndex] = val;
        }
        this->dataIndex++;
        if (this->dataIndex >= ui->sb_numSamples->value())
        {
            this->dataIndex = 0;
        }
    }
}

