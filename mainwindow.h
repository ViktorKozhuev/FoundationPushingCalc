#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMap>

#include "foundation.h"
#include "pilescoords.h"
#include "setloads.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPushButtonSetPileSchemeClicked();

    void on_pushButtonPilesNM_clicked();

    void on_pushButton_clicked();

    void on_setNPilesButton_clicked();

    void on_pushButtonMakeCalc_clicked();

    void on_setNButton_editingFinished();

    void on_radioUseN_toggled(bool checked);

    void on_radioUseNPilles_toggled(bool checked);

public slots:
    void getpilesCoords(QList<QList<int>> pilesCoords);
    void getPilesLoads(QList<int> pilesLoads);

signals:
    void sendNPiles(int nPiles);

private:
    Ui::MainWindow *ui;
    Foundation f;
    QGraphicsScene *scene;
    PilesCoords *pilescoordsview;
    SetLoads *setloads;
    QMap<QString, double> concrete{
        {"B15", 0.75},
        {"B20", 0.9},
        {"B25", 1.05},
        {"B30", 1.15},
        {"B35", 1.30},
        {"B40", 1.40},
        {"B45", 1.50},
        {"B50", 1.60},
        {"B55", 1.70},
        {"B60", 1.80},
        {"B70", 1.90},
        {"B80", 2.10},
        {"B90", 2.15}
        };

    QMap<QString, double> reinforcement{
        {"A240", 170.0},
        {"A400", 280.0},
        {"A500", 300.0}
        };

    QMap<int, double> diameters{
        {5, 0.196},
        {6, 0.283},
        {8, 0.503},
        {10, 0.789},
        {12, 1.131},
        {14, 1.539},
        {16, 2.011},
        {20, 3.142}
    };

    void setSettings();
    void makeDraft();
    void setFoundProperties();
    void configChooseSchemePilesButtons();
    void makeCalculation();
    void setLoadsByN();


};
#endif // MAINWINDOW_H
