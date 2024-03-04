#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pilescoords.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRectF>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    f = Foundation();
    pilescoordsview = new PilesCoords;
    setloads = new SetLoads;
    scene = new QGraphicsScene(this);

    setSettings();
    configChooseSchemePilesButtons();
    setFoundProperties();

    connect(this, &MainWindow::sendNPiles, setloads, &SetLoads::getNPiles);
    connect(pilescoordsview, &PilesCoords::sendData, this, &MainWindow::getpilesCoords);
    connect(setloads, &SetLoads::sendData, this, &MainWindow::getPilesLoads);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makeDraft()
{
    ui->graphicsView->fitInView(QRect(10,10,f.a+40,f.b+40), Qt::KeepAspectRatio);
    scene->clear();
    QPen pen(Qt::black);
    pen.setWidth(2);
    scene->setSceneRect(10,10,f.a+10,f.b+10);
    scene->setSceneRect(QRect(10,10,f.a+10,f.b+10));

    scene->addRect(10, 10, f.a, f.b, pen);
    pen.setWidth(3);
    scene->addRect(
        10+f.colx - f.cola / 2,
        10+f.coly - f.colb / 2,
        f.cola, f.colb,
        pen,
        QBrush(Qt::lightGray, Qt::BDiagPattern)
        );

    for (int i = 1; i <= f.pcount; ++i) {
        scene->addRect(
            10 + f.piles[i][0] - f.psize / 2,
            10 + f.piles[i][1] - f.psize / 2,
            f.psize,
            f.psize);
        QGraphicsTextItem * io = new QGraphicsTextItem;
        io->setDefaultTextColor(Qt::blue);
        io->setPos(f.piles[i][0],f.piles[i][1]+(f.psize+3));
        io->setPlainText("№" + QString::number(i) + " " + "N=" +QString::number(f.piles[i][2]));
        scene->addItem(io);
    }
    if(f.c1 != f.b){
        scene->addLine(10+f.c2, 10+f.c1, 10+f.c4, 10+f.c1, QPen(Qt::red, 1, Qt::DashLine));
    }
    if(f.c2 != f.a) {
        scene->addLine(10+f.c2, 10+f.c1, 10+f.c2, 10+f.c3, QPen(Qt::red, 1, Qt::DashLine));
    }
    if(f.c3 != 0){
        scene->addLine(10+f.c2, 10+f.c3, 10+f.c4, 10+f.c3, QPen(Qt::red, 1, Qt::DashLine));
    }
    if(f.c4 != 0){
        scene->addLine(10+f.c4, 10+f.c1, 10+f.c4, 10+f.c3, QPen(Qt::red, 1, Qt::DashLine));
    }
}

void MainWindow::setFoundProperties()
{
    f.a = ui->foundDimX->value();
    f.b = ui->foundDimY->value();
    f.h = ui->foundDimHeight->value();

    int new_colx = f.a / 2 + ui->colShiftX->value();
    int new_coly = f.b / 2 + ui->colShiftY->value();
    if(new_colx >= f.cola / 2 && new_colx <= f.a - f.cola / 2) {
        f.colx = new_colx;
    }
    if(new_coly >= f.colb / 2 && new_coly <= f.b - f.colb / 2) {
        f.coly = new_coly;
    }

    if(f.colx < f.cola / 2) {
        f.colx = f.cola / 2;
    }

    if(f.colx > f.a - f.cola / 2){
        f.colx = f.a - f.cola / 2;
    }

    if(f.coly < f.colb / 2) {
        f.coly = f.colb / 2;
    }

    if(f.coly > f.b - f.colb / 2){
        f.coly = f.b - f.colb / 2;
    }

    f.cola = ui->colDimX->value();
    f.colb = ui->colDimY->value();
    f.a0 = ui->foundAz->value();
    f.psize = ui->pileSize->value();
    f.ax = ui->dimAx->value();
    f.ay = ui->dimAy->value();
}

void MainWindow::configChooseSchemePilesButtons()
{
    QHBoxLayout *box = qobject_cast<QHBoxLayout*>(ui->choosePilesScheme);
    for (int i = 0; i < box->count(); ++i) {
        QPushButton *btn = qobject_cast<QPushButton*>(box->itemAt(i)->widget());
        connect(btn, &QPushButton::clicked, this, &MainWindow::onPushButtonSetPileSchemeClicked);
    }
}

void MainWindow::makeCalculation()
{

    int l1 = 0, l2 = 0, l3 = 0, l4 = 0;

    if(f.c1 != f.b){
        if(f.c4 != 0 && f.c2 != f.a)
            l1 = (f.c2 - f.c4 + f.colb) / 2;
        if(f.c4 == 0)
            l1 = (f.c2 + f.colx + f.colb / 2) / 2;
        if(f.c2 == f.a)
            l1 = (f.a - f.c4 +(f.a - f.colx + f.colb / 2)) / 2 ;
    }

    if(f.c2 != f.a){
        if(f.c3 != 0 && f.c1 != f.b)
            l2 = (f.c1 - f.c3 + f.cola) / 2;
        if(f.c3 == 0)
            l2 = (f.c1 + f.coly + f.colb / 2) / 2;
        if(f.c1 == f.b)
            l2 = (f.b - f.c3 + (f.b - f.coly + f.cola / 2)) / 2 ;
    }

    if(f.c3 != 0) {
        if(f.c4 != 0 && f.c2 !=f.a)
            l3 = (f.c2 - f.c4 + f.colb) / 2;
        if(f.c4 == 0)
            l3 = (f.c2 + f.colx + f.colb / 2) / 2;
        if(f.c2 == f.a)
            l3 = (f.a - f.c4 +(f.a - f.colx + f.colb / 2)) / 2 ;
    }

    if(f.c4 != 0){
        if(f.c3 != 0 && f.c1 != f.b)
            l4 = (f.c1 - f.c3 + f.cola) / 2;
        if(f.c3 == 0)
            l4 = (f.c1 + f.coly + f.colb / 2) / 2;
        if(f.c1 == f.b)
            l4 = (f.b - f.c3 + (f.b - f.coly + f.cola / 2)) / 2 ;
    }

    double rFb;
    double rFa;
    double rb;
    double ra;
    double as;
    int h0;

    rb = concrete[ui->selectConcrete->currentText()] / 10;
    ra = reinforcement[ui->selectReinforcement->currentText()] / 10;
    as = diameters[ui->selectDiameter->currentText().toInt()];
    h0 = f.h - f.a0;

    double c1 = f.c1 - (f.coly + f.colb / 2);
    double c2 = f.c2 - (f.colx + f.cola / 2);
    double c3 = f.coly - f.colb / 2 - f.c3;
    double c4 = f.colx - f.cola / 2 - f.c4;

    int sa = ui->stepBar->value();
    int sk = ui->stepFrame->value();

    int N = 0;

    for (int i = 1; i <= f.pcount; ++i) {
        if(!(f.piles[i][0] >= f.c4 && f.piles[i][0] <= f.c2 && f.piles[i][1] >= f.c3 && f.piles[i][1] <= f.c1)) {
            N += f.piles[i][2];
        }
    }
    if(c1 == 0) c1 = 1;
    if(c2 == 0) c2 = 1;
    if(c3 == 0) c3 = 1;
    if(c4 == 0) c4 = 1;

    rFb = h0 * rb * (l1 * h0 / c1 + l2 *  h0 / c2 + l3 * h0 / c3 + l4 * h0 / c4);
    rFa = ra * as * (l1 * c1 + l2 * c2 + l3 * c3 + l4 * c4) / (sa * sk);

    // qDebug() << 1 << l1 << c1;
    // qDebug() << 2 << l2 << c2;
    // qDebug() << 3 << l3 << c3;
    // qDebug() << 4 << l4 << c4;
    // qDebug() << N << rFb << rFa;

    ui->textResult->clear();

    bool usereinforcement;
    usereinforcement = ui->checkBoxUseRein->isChecked();

    if(rFb <= N / 2) {
        QString res = QString("Расчетная продавливающая сила больше в два раза несущей способности.\n Fb = %1 кН\n N = %2 кН").arg(rFb, 0, 'f', 2).arg(N, 0, 10);
        ui->textResult->append(res);
        return;
    }

    if(rFb >= N && usereinforcement) {
        double kisp = N / rFb;
        QString res = QString("Прочность фундамента на продавливание обеспечена."
                              " Армирование не требуется. Коэффициент использования К = %1\n Fb = %2 кН\n Fsw = %3 кН\n N = %4 кН").arg(kisp, 0, 'f', 2).arg(rFb, 0, 'f', 2).arg(rFa, 0, 'f', 2).arg(N, 0, 10);
        ui->textResult->append(res);
        return;
    }

    if(rFb >= N) {
        double kisp = N / rFb;
        QString res = QString("Прочность фундамента на продавливание обеспечена. Коэффициент использования К = %1\n Fb = %2 кН\n N = %3 кН").arg(kisp, 0, 'f', 2).arg(rFb, 0, 'f', 2).arg(N, 0, 10);
        ui->textResult->append(res);
        return;
    }

    if(rFb < N && !usereinforcement) {
        double kisp = N / rFb;
        QString res = QString("Прочность фундамента на продавливание не обеспечена. Требуется армирование."
                              " Коэффициент использования К = %1\n Fb = %2 кН\n N = %3 кН").arg(kisp, 0, 'f', 2).arg(rFb, 0, 'f', 2).arg(N, 0, 10);
        ui->textResult->append(res);
        return;
    }

    if(rFb + rFa >= N && usereinforcement) {
        double kisp = N / (rFb + rFa);
        QString res = QString("Прочность фундамента на продавливание обеспечена. Коэффициент использования К = %1\n Fb = %2 кН\n Fsw = %3 кН\n N = %4 кН").arg(kisp, 0, 'f', 2).arg(rFb, 0, 'f', 2).arg(rFa, 0, 'f', 2).arg(N, 0, 10);
        ui->textResult->append(res);
        return;
    }

    if(rFb + rFa < N && usereinforcement) {
        double kisp = N / (rFb + rFa);
        QString res = QString("Прочность фундамента на продавливание не обеспечена. Коэффициент использования К = %1\n Fb = %2 кН\n Fsw = %3 кН\n N = %4 кН").arg(kisp, 0, 'f', 2).arg(rFb, 0, 'f', 2).arg(rFa, 0, 'f', 2).arg(N, 0, 10);
        ui->textResult->append(res);
        return;
    }
}

void MainWindow::setLoadsByN()
{
    int loadN;
    loadN = ui->setNButton->value();
    if(ui->radioUseN->isChecked()) {
        for (int i = 1; i <= f.pcount; ++i) {
            f.piles[i][2] = loadN / f.piles.count();
        }
    }
}

void MainWindow::onPushButtonSetPileSchemeClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int count = btn->text().toInt();
    setFoundProperties();
    bool res = f.setPiles(count);
    if(!res) {
        QMessageBox::warning(this, "Предупреждение","Проверьте геометрию свай");
        return;
    }
    f.setCValues();
    if(ui->radioUseN->isChecked()) {
        setLoadsByN();
    }
    makeDraft();
}

void MainWindow::on_pushButtonPilesNM_clicked()
{
    setFoundProperties();
    int n = ui->pilesN->value();
    int m = ui->pilesM->value();
    bool res = f.setPiles(n, m);
    if(!res) {
        QMessageBox::warning(this, "Предупреждение","Проверьте геометрию свай");
        return;
    }
    f.setCValues();
    if(ui->radioUseN->isChecked()) {
        setLoadsByN();
    }
    makeDraft();
}


void MainWindow::on_pushButton_clicked()
{
    pilescoordsview->show();
}

void MainWindow::getpilesCoords(QList<QList<int>> pilesCoords)
{
    setFoundProperties();
    bool res = f.setPiles(pilesCoords);
    if(!res) {
        QMessageBox::warning(this, "Предупреждение","Проверьте геометрию свай");
        return;
    }
    f.setCValues();
    if(ui->radioUseN->isChecked()) {
        setLoadsByN();
    }
    makeDraft();
}

void MainWindow::getPilesLoads(QList<int> pilesLoads)
{
    if(pilesLoads.length() == f.piles.count()){
        for (int i = 1; i <= f.pcount; ++i) {
            f.piles[i][2] = pilesLoads[i-1];
        }
        makeDraft();
    }

}

void MainWindow::setSettings()
{
    this->setWindowTitle("Расчет свайного фундамента на продавливание");
    ui->selectConcrete->addItems(concrete.keys());
    ui->selectReinforcement->addItems(reinforcement.keys());
    for (int i = 0; i < diameters.keys().length(); ++i) {
        ui->selectDiameter->addItem(QString::number(diameters.keys()[i]));
    }
    ui->graphicsView->setScene(scene);
}


void MainWindow::on_setNPilesButton_clicked()
{
    setloads->show();
    emit sendNPiles(f.pcount);

}


void MainWindow::on_pushButtonMakeCalc_clicked()
{
    makeCalculation();
}


void MainWindow::on_setNButton_editingFinished()
{
    if(ui->radioUseN->isChecked()) {
        setLoadsByN();
        makeDraft();
    }
}


void MainWindow::on_radioUseN_toggled(bool checked)
{
    ui->setNPilesButton->setEnabled(!checked);
    ui->setNButton->setEnabled(checked);
}


void MainWindow::on_radioUseNPilles_toggled(bool checked)
{
    ui->setNPilesButton->setEnabled(checked);
    ui->setNButton->setEnabled(!checked);
}

