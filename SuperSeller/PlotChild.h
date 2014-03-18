#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include "mdichild.h"
#include <vector>
#include <random>
#include <assert.h>
#include <iostream>

using namespace std;



class PlotChild : public MdiChild
{
    Q_OBJECT
public:
    PlotChild();

private:
    QImage img, img2;    
    vector<int> prices;
    vector<int> buy;
    vector<int> profit;
    int n = 100;
    int start = 1000;
    double noise_sigma = 1;
    double tan_mean = 0.2;
    double tan_sigma = 0.3;

    double geom_p = 0.05;
protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent *);    
};

#endif // DRAWWIDGET_H
