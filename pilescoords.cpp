#include "pilescoords.h"
#include <QStandardItemModel>
#include <QTableView>
#include "ui_pilescoords.h"
#include "pilescoords.h"
#include <QDebug>


PilesCoords::PilesCoords(QWidget *parent)
    : QWidget{parent},
    ui(new Ui::pilescoords)
{
    ui->setupUi(this);
    this->setWindowTitle("Координаты свай");
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    int n_piles = 4;

    model =  new QStandardItemModel;
    setCountPiles(n_piles);

}


PilesCoords::~PilesCoords() {
    delete ui;
}

void PilesCoords::setCountPiles(int n)
{
    model->setColumnCount(2);
    model->setRowCount(n);
    model->setHeaderData(0, Qt::Horizontal, "X");
    model->setHeaderData(1, Qt::Horizontal, "Y");
    ui->tableView->setModel(model);
}

void PilesCoords::on_buttonNPiles_clicked()
{
    int n =ui->spinNPiles->value();
    setCountPiles(n);
}


void PilesCoords::on_buttonOk_clicked()
{
    QList<QList<int>> pilesCoords;
    for (int i = 0; i < model->rowCount(); ++i) {
        bool ok;
        if(model->item(i,0)){
            qDebug() << model->item(i,0)->text().toInt(&ok);
            pilesCoords.append({model->item(i,0)->text().toInt(&ok), model->item(i,1)->text().toInt(&ok)});
        }
    }
    emit sendData(pilesCoords);
    this->close();

}

