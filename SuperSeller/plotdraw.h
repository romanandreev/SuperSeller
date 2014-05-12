#ifndef PLOTDRAW_H
#define PLOTDRAW_H

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
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

using namespace std;



class Plotdraw : public QWidget
{
    Q_OBJECT
public:
    Plotdraw();
    Plotdraw(vector<double>, vector<double>, vector<double>, vector<int>);
    void change(vector<double>, vector<double>, vector<double>, vector<int>);

private:
    QImage img, img2;    
    vector<double> val1; //price, blue
    vector<double> val2; //profit, red
    vector<double> val3; //trend, green
    vector<int> events; //buysell
    int n;
    void myresize();
protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent *);    
};

#endif // PLOTDRAW_H
