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
    vector<double> prices;
    vector<double> trend;
    vector<int> buy;
    vector<double> profit;
    int n = 1001;
    int start = 1000;
    double noise_sigma = 0;
    double tan_mean = 0;
    double tan_sigma = 0.3;

    double geom_p = 0.05;
protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent *);    
};

#endif // DRAWWIDGET_H
