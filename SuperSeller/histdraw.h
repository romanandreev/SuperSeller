#ifndef HistDRAW_H
#define HistDRAW_H

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



class Histdraw : public QWidget
{
    Q_OBJECT
public:
    Histdraw();
    Histdraw(vector<double>, QString);
    void change(vector<double>, QString);

private:
    QImage img, img2;    
    vector<double> list;
    QString name;
    void myresize();
protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent *);    
};

#endif // HistDRAW_H
