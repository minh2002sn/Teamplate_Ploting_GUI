#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_chb_scaleEnable_clicked(bool checked)
{
    if (checked)
    {
        ui->dsb_minRaw->setDisabled(false);
        ui->dsb_maxRaw->setDisabled(false);
        ui->dsb_minScale->setDisabled(false);
        ui->dsb_maxScale->setDisabled(false);
    }
    else
    {
        ui->chb_scaleEnable->setCheckState(Qt::CheckState::Checked);
        // ui->dsb_minRaw->setDisabled(true);
        // ui->dsb_maxRaw->setDisabled(true);
        // ui->dsb_minScale->setDisabled(true);
        // ui->dsb_maxScale->setDisabled(true);
    }
}

