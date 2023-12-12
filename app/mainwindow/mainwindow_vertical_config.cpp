#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_rbtn_yFixRange_clicked(bool checked)
{
    if (checked)
    {
        ui->dsb_min->setDisabled(false);
        ui->dsb_max->setDisabled(false);
        // ui->graph->graph(0)
    }
}


void MainWindow::on_rbtn_yAutoScale_clicked(bool checked)
{
    ui->rbtn_yFixRange->setChecked(true);
    ui->rbtn_yAutoScale->setChecked(false);
    // if (checked)
    // {
    //     ui->dsb_min->setDisabled(true);
    //     ui->dsb_max->setDisabled(true);
    // }
}
