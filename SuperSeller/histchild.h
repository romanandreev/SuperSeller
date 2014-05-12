#ifndef HistCHILD_H
#define HistCHILD_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QColor>
#include <QMouseEvent>
#include "mdichild.h"
#include "Histdraw.h"
#include "oracle.h"
#include "gen.h"

#include <vector>
#include <random>
#include <assert.h>
#include <iostream>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressDialog>

using namespace std;



class HistChild : public MdiChild
{
    Q_OBJECT
public:
    HistChild();
private slots:
    void pressed();
private:    
    QImage img, img2;    
    vector<double> prices1, prices2;
    vector<double> profit1, profit2;
    vector<double> trend1, trend2;
    vector<int> buysell1, buysell2;
    QLineEdit * str1, *str2, *str3, *str4, *str5, *str6, *str7;
    Histdraw *Histdraw1, *Histdraw2,*Histdraw3, *Histdraw4,*Histdraw5, *Histdraw6;    
    Gen gen;
    Oracle orac;
};

#endif // HistCHILD_H
