#ifndef SETLOADS_H
#define SETLOADS_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class SetLoads;
}

class SetLoads : public QWidget
{
    Q_OBJECT

public:
    explicit SetLoads(QWidget *parent = nullptr);
    ~SetLoads();

private:
    Ui::SetLoads *ui;
    QStandardItemModel* model;
    void setCountPiles(int npiles);

public slots:
    void getNPiles(int npiles);
private slots:
    void on_buttonOk_clicked();

signals:
    void sendData(QList<int> pilesLoads);
};

#endif // SETLOADS_H
