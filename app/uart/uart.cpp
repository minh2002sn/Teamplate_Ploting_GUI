#include "uart.h"
#include <QDebug>

Uart::Uart(QObject *parent)
    : QObject{parent}
{
    connect(&serial, &QSerialPort::readyRead, this, &Uart::handleData);

    this->state = RxState::WAITING_SOT;
}

void Uart::handleData()
{
    // qInfo() << "Receive data";
    QByteArray rxData = serial.readAll();
    for(int i = 0; i < rxData.size(); i++)
    {
        this->handleByte(rxData.at(i));
    }
}

void Uart::handleByte(unsigned char data)
{
    // qInfo() << data << '\n';
    switch(this->state)
    {
    case RxState::WAITING_SOT:
        if (data == Frame::START_OF_TEXT)
        {
            this->state = RxState::WAITING_DATA;
            this->numByte = 0;
        }
        break;
    case RxState::WAITING_DATA:
        this->rxBuff[this->numByte++] = data;
        if (this->numByte == 4)
        {
            this->state = RxState::WAITING_EOT;
        }
        break;
    case RxState::WAITING_EOT:
        if (data == Frame::END_OF_TEXT)
        {
            this->state = RxState::WAITING_SOT;
            emit readDone(this->rxBuff);
        }
        break;
    }
}
