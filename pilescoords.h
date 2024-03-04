#ifndef PILESCOORDS_H
#define PILESCOORDS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStandardItemModel>

namespace Ui {
class pilescoords;
}

class PilesCoords : public QWidget
{
    Q_OBJECT
public:
    explicit PilesCoords(QWidget *parent = nullptr);
    ~PilesCoords();

    QVBoxLayout *box;
    QPushButton *addPile;

private:
    Ui::pilescoords *ui;
    QStandardItemModel* model;
    void setCountPiles(int npiles);

signals:
    void sendData(QList<QList<int>> pilesCoords);

private slots:
    void on_buttonNPiles_clicked();
    void on_buttonOk_clicked();

};

#endif // PILESCOORDS_H
