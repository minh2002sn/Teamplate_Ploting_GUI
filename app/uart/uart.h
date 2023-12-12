#ifndef UART_H
#define UART_H

#include <QObject>
#include <QSerialPort>

class Uart : public QObject
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
    explicit Uart(QObject *parent = nullptr);

    QSerialPort serial;

signals:
    void readDone(unsigned char *);

private slots:
    void handleData();

private:
    void handleByte(unsigned char data);

    unsigned char rxBuff[4];
    unsigned char numByte;
    RxState state;

};

#endif // UART_H
