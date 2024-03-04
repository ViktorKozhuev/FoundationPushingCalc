#include "foundation.h"
#include <math.h>
#include <QDebug>

//Foundation::Foundation() {}

Foundation::Foundation(
    int a,
    int b,
    int h,
    int a0,
    int ax,
    int ay,
    int psize,
    int cola,
    int colb,
    QList<QList<int>> pilesCoords
    )
{
    this->a = a;
    this->b = b;
    this->h = h;
    this->a0 = a0;
    this->ax = ax;
    this->ay = ay;

    this->psize = psize;

    this->cola = cola;
    this->colb = colb;

    this->colx = a / 2;
    this->coly = b / 2;


    this->setPiles(4);


    int c1;
    int c2;
    int c3;
    int c4;
}

bool Foundation::setPiles(int n)
{
    QMap<int, QList<int>> piles;
    int p_count = 0;
    if(n == 4) {
        p_count = 4;
        piles[1] = {this->ax, this->ay, 0};
        piles[2] = {a - this->ax, this->ay, 0};
        piles[3] = {this->ax, b - this->ay, 0};
        piles[4] = {a - this->ax, b - this->ay, 0};
    }
    if(n == 5) {
        p_count = 5;
        piles[1] = {this->ax, this->ay, 0};
        piles[2] = {a - this->ax, this->ay, 0};
        piles[3] = {a / 2, b / 2, 0};
        piles[4] = {this->ax, b - this->ay, 0};
        piles[5] = {a - this->ax, b - this->ay, 0};
    }
    if(n == 6) {
        p_count = 6;
        piles[1] = {this->ax, this->ay, 0};
        piles[2] = {a - this->ax, this->ay, 0};
        piles[3] = {a / 2, b / 2 - (b / 6 + this->ay / 2), 0};
        piles[4] = {a / 2, b / 2 + (b / 6 + this->ay / 2), 0};
        piles[5] = {this->ax, b - this->ay, 0};
        piles[6] = {a - this->ax, b - this->ay, 0};
    }
    if(n == 7) {
        p_count = 7;
        piles[1] = {a / 2, this->ay, 0};
        piles[2] = {this->ax, b / 2 - (b / 6 + this->ay / 2), 0};
        piles[3] = {a - this->ax, b / 2 - (b / 6 + this->ay / 2), 0};
        piles[4] = {a / 2, b / 2, 0};
        piles[5] = {this->ax, b / 2 + (b / 6 + this->ay / 2), 0};
        piles[6] = {a - this->ax, b / 2 + (b / 6 + this->ay / 2), 0};
        piles[7] = {a / 2, b - this->ay, 0};
    }
    if(n == 8) {
        p_count = 8;
        piles[1] = {this->ax, this->ay, 0};
        piles[2] = {a - this->ax, this->ay, 0};
        piles[3] = {a / 2, b / 2 - (b / 6 + this->ay / 2), 0};
        piles[4] = {this->ax, b / 2, 0};
        piles[5] = {a - this->ax, b / 2, 0};
        piles[6] = {a / 2, b / 2 + (b / 6 + this->ay / 2), 0};
        piles[7] = {this->ax, b - this->ay, 0};
        piles[8] = {a - this->ax, b - this->ay, 0};
    }


    if(Foundation::checkPilesGeometry(piles)){
        this->piles = piles;
        this->pcount = p_count;
        return true;
    }
    return false;

}

bool Foundation::setPiles(int n, int m)
{
    int space_x = (this->a - 2 * this->ax) / (n - 1);
    int space_y = (this->b - 2 * this->ay) / (m - 1);

    QMap<int, QList<int>> piles;
    int p_count = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            piles[++p_count] = QList<int> {this->ax + space_x * j, this->ay + space_y * i, 0};
        }
    }
    if(Foundation::checkPilesGeometry(piles)){
        this->piles = piles;
        this->pcount = p_count;
        return true;
    }
    return false;
}

bool Foundation::setPiles(QList<QList<int> > pilesCoords)
{
    QMap<int, QList<int>> piles;
    for (int i = 0; i < pilesCoords.length(); ++i) {
        piles[i+1] = QList<int>{pilesCoords[i][0], pilesCoords[i][1], 0};
    }
    if(Foundation::checkPilesGeometry(piles)){
        this->piles = piles;
        this->pcount = pilesCoords.length();
        return true;
    }
    return false;

}

bool Foundation::checkPilesGeometry(QMap<int, QList<int>> piles)
{
    for (int i = 1; i <= piles.size(); ++i) {
        for (int j = 1; j <= piles.size(); ++j) {
            int space = sqrt(pow(piles[i][0] - piles[j][0], 2) + pow(piles[i][1] - piles[j][1], 2));
            if(piles[i][0] < ax || piles[i][0] > a - ax || piles[i][1] < ay || piles[i][1] > b - ay)
            {
                return false;
            }
            if(i != j && space < psize * 3) {
                return false;
            }
        }
    }
    return true;
}

void Foundation::setCValues()
{
    c1 = coly + colb / 2 + (h-a0);
    int minc1 = c1;
    for (int i = 1; i <= piles.size(); ++i) {
        bool state1 = (piles[i][0]+psize/2 > colx-(cola/2+(h-a0))) && (piles[i][0]-psize/2 < colx+(cola/2+(h-a0)));
        bool state2 = ((piles[i][1] - psize / 2) >= (coly + colb / 2 + (h-a0) * 0.4));
        bool state3 = piles[i][1] - psize / 2 < minc1;
        if(state1 && state2 && state3) {
            minc1 = piles[i][1] - psize / 2;
        }
    }
    c1 = minc1;
    if(c1 > b - ay - psize/2) {
        c1 = b;
    }
    // qDebug() << c1 << "-c1";

    c2 = colx + cola / 2 + (h-a0);
    int minc2 = c2;
    for (int i = 1; i <= piles.size(); ++i) {
        bool state1 = (piles[i][1]+psize/2 > coly-(colb/2+(h-a0))) && (piles[i][1]-psize/2 < coly+(colb/2+(h-a0)));
        bool state2 = ((piles[i][0] - psize / 2) >= (colx + cola / 2 + (h-a0) * 0.4));
        bool state3 = piles[i][0] - psize / 2 < minc2;
        if(state1 && state2 && state3) {
            minc2 = piles[i][0] - psize / 2;
        }
    }
    c2 = minc2;
    if(c2 > a - ax - psize/2) {
        c2 = a;
    }
    // qDebug() << c2 << "-c2";

    c3 = coly - colb / 2 - (h-a0);
    int maxc3 = c3;
    for (int i = 1; i <= piles.size(); ++i) {
        bool state1 = (piles[i][0]+psize/2 > colx-(cola/2+(h-a0))) && (piles[i][0]-psize/2 < colx+(cola/2+(h-a0)));
        bool state2 = ((piles[i][1] + psize / 2) <= (coly - colb / 2 - (h-a0)*0.4));
        bool state3 = piles[i][1] + psize / 2 > maxc3;
        if(state1 && state2 && state3) {
            maxc3 = piles[i][1] + psize / 2;
        }
    }
    c3 = maxc3;
    if(c3 < ay + psize/2) {
        c3 = 0;
    }
    // qDebug() << c3 << "-c3";

    c4 = colx - cola / 2 - (h-a0);
    int max4 = c4;
    for (int i = 1; i <= piles.size(); ++i) {
        bool state1 = (piles[i][1]+psize/2 > coly-(colb/2+(h-a0))) && (piles[i][1]-psize/2 < coly+(colb/2+(h-a0)));
        bool state2 = ((piles[i][0] + psize / 2) <= (colx - cola / 2 - (h-a0) * 0.4));
        bool state3 = piles[i][0] + psize / 2 > max4;
        if(state1 && state2 && state3) {
            max4 = piles[i][0] + psize / 2;
        }
    }
    c4 = max4;
    if(c4 < ax + psize/2) {
        c4 = 0;
    }
    // qDebug() << c4 << "-c4";

}


