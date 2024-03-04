#include "setloads.h"
#include "ui_setloads.h"
//#include "mainwindow.h"

SetLoads::SetLoads(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetLoads)
{
    ui->setupUi(this);
    this->setWindowTitle("Нагрузки на сваи");
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    model =  new QStandardItemModel;
}

SetLoads::~SetLoads()
{
    delete ui;
}

void SetLoads::setCountPiles(int npiles)
{
    model->setColumnCount(1);
    model->setRowCount(npiles);
    model->setHeaderData(0, Qt::Horizontal, "N");
    ui->tableView->setModel(model);
}

void SetLoads::getNPiles(int npiles)
{
    setCountPiles(npiles);
}

void SetLoads::on_buttonOk_clicked()
{
    QList<int> pilesLoads;
    for (int i = 0; i < model->rowCount(); ++i) {
        bool ok;
        if(model->item(i,0)){
            qDebug() << model->item(i,0)->text().toInt(&ok);
            pilesLoads.append(model->item(i,0)->text().toInt(&ok));
        }
    }
    emit sendData(pilesLoads);
    this->close();
}

