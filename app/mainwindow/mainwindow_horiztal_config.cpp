#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_rbtn_xFixRange_clicked(bool checked)
{
    if (checked)
    {
        ui->sb_numSamples->setDisabled(false);
    }
}


void MainWindow::on_rbtn_xAutoScale_clicked(bool checked)
{
    ui->rbtn_xFixRange->setChecked(true);
    ui->rbtn_xAutoScale->setChecked(false);
    // if (checked)
    // {
    //     ui->sb_numSamples->setDisabled(true);
    // }
}


void MainWindow::on_sb_numSamples_valueChanged(int arg1)
{
    if (arg1 < 10)
    {
        ui->sb_numSamples->setValue(10);
    }
    else
    {
        ui->sb_numSamples->setValue(arg1 - (arg1 % 10));
    }
}
