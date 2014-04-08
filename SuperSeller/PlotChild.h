#ifndef PLOTCHILD_H
#define PLOTCHILD_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include "mdichild.h"
#include "plotdraw.h"
#include "oracle.h"
#include <vector>
#include <random>
#include <assert.h>
#include <iostream>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

using namespace std;



class PlotChild : public MdiChild
{
    Q_OBJECT
public:
    PlotChild();
private slots:
    void pressed();
private:    
    QImage img, img2;    
    vector<double> prices1, prices2;
    vector<double> profit1, profit2;
    vector<double> trend1, trend2;
    vector<int> buysell1, buysell2;
    QLineEdit * str1, *str2, *str3, *str4, *str5, *str6, *str7;
    QLabel* text8, *text9;
    Plotdraw *plotdraw1, *plotdraw2;
    Oracle o;
};

#endif // PLOTCHILD_H
