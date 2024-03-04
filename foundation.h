#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <QMap>
#include <QList>

class Foundation
{
public:
    Foundation(
        int a = 200,
        int b = 200,
        int h = 50,
        int a0 = 5,
        int ax = 30,
        int ay = 30,
        int psize = 30,
        int cola = 50,
        int colb = 50,
        QList<QList<int>> pilesCoords = {{30, 30}, {170, 30}, {30, 170}, {170,170}}
        );

    QMap<int, QList<int>> piles;

    int a;
    int b;
    int h;
    int a0;
    int ax;
    int ay;
    int psize;
    int pcount;

    int cola;
    int colb;

    int colx;
    int coly;

    int c1;
    int c2;
    int c3;
    int c4;

    bool setPiles(int n);
    bool setPiles(int n, int m);
    bool setPiles(QList<QList<int>> pilesCoords);
    bool checkPilesGeometry(QMap<int, QList<int>> piles);
    void setCValues();


};

#endif // FOUNDATION_H
