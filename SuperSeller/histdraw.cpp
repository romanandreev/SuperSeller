#include "Histdraw.h"


void Histdraw::paintEvent(QPaintEvent*) {
    QPainter outpainter(this);
    outpainter.drawImage(0,0, img2);
}


void Histdraw::resizeEvent(QResizeEvent *){
    myresize();
}
void Histdraw::myresize() {
    img = QImage(width(), height(), QImage::Format_RGB32);
    int w = width();
    int h = height();
    int s = 40;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            img.setPixel(i, j, QColor(255, 255, 255).rgb());
        }
    }
    QPainter painter(&img);
    //painter.setRenderHint(QPainter::Antialiasing);
    QPen Pen((QColor(0,0,0)),1);
    painter.setPen(Pen);
    painter.drawLine(0, 0, w, h);

    /*painter.drawLine(s, h - s, w - s, h - s);
    QPolygonF arrowHead;
    painter.setBrush(Qt::black);    
    painter.drawLine(s, 0, s, h - s);
    arrowHead.clear();
    arrowHead << QPointF(s, 0)
              << QPointF(s - s / 4, s / 2)
              << QPointF(s + s / 4, s / 2);
    painter.drawPolygon(arrowHead);
    painter.drawLine(s, s, s, h - s);

    painter.drawLine(w - s, 0, w - s, h - s);
    arrowHead.clear();
    arrowHead << QPointF(w - s, 0)
              << QPointF(w - s - s / 4, s / 2)
              << QPointF(w - s + s / 4, s / 2);
    painter.drawPolygon(arrowHead);



    vector<double> x;
    int shift = n;
    for (int i = 0; i <= n; i++) {
        x.push_back(s + (w - 2 * s) * i / n);
    }
    for (int i = 0; i <= n; i += 5) {
        if (x[i] - x[0] >= s) {
            shift = i;
            break;
        }
    }
    for (int i = 0; i <= n; i += shift) {
        painter.drawLine(x[i], h - s, x[i], h - (s - s / 4));
        painter.drawText(x[i], h - (s * 1 / 4), QString::number(i));
    }

    int cy = 0;
    for (int i = 1; ; i++) {
        if ((h - 2 * s) / i >= s) {
            cy = i;
        } else {
            break;
        }
    }

    double mny = floor(*min_element(val2.begin(), val2.end()));
    double mxy = ceil(*max_element(val2.begin(), val2.end()));
    if (fabs(mxy - mny) <= 1e-9) {
        mny--;
        mxy++;
    }


    for (int i = 0; i <= cy; i++) {
        painter.drawLine(w - s, h - (s + (double)(h - 2 * s) * i / cy), w, h - (s + (double)(h - 2 * s) * i / cy));
        painter.drawText(w - s + 2, h - (s + (double)(h - 2 * s) * i / cy) - 1,
                         QString::number((mny + (mxy - mny) * ((double)i / cy)), 'g', 5));
    }

    Pen.setColor(QColor(255, 0, 0));
    Pen.setWidth(2);
    painter.setPen(Pen);

    for (int i = 0; i < n; i++) {
        painter.drawLine(x[i], h - ((val2[i] - mny) * (h - 2 * s) / (mxy - mny) + s),
                         x[i + 1], h - ((val2[i + 1] - mny) * (h - 2 * s) / (mxy - mny) + s));
    }


    Pen.setColor(QColor(0, 0, 0));
    Pen.setWidth(1);
    painter.setPen(Pen);

    mny = floor(*min_element(val1.begin(), val1.end()));
    mxy = ceil(*max_element(val1.begin(), val1.end()));
    mny = min(mny, floor(*min_element(val3.begin(), val3.end())));
    mxy = max(mxy, ceil(*max_element(val3.begin(), val3.end())));

    if (fabs(mxy - mny) <= 1e-9) {
        mny--;
        mxy++;
    }



    for (int i = 0; i <= cy; i++) {
        painter.drawLine(s, h - (s + (double)(h - 2 * s) * i / cy), 0, h - (s + (double)(h - 2 * s) * i / cy));
        painter.drawText(2, h - (s + (double)(h - 2 * s) * i / cy) - 1,
                         QString::number((mny + (mxy - mny) * ((double)i / cy)), 'g', 5));
    }

    Pen.setColor(QColor(0, 0, 255));
    Pen.setWidth(2);
    painter.setPen(Pen);

    for (int i = 0; i < n; i++) {
        painter.drawLine(x[i], h - ((val1[i] - mny) * (h - 2 * s) / (mxy - mny) + s),
                         x[i + 1], h - ((val1[i + 1] - mny) * (h - 2 * s) / (mxy - mny) + s));
    }

    Pen.setColor(QColor(0, 255, 0));
    Pen.setWidth(2);
    painter.setPen(Pen);

    for (int i = 0; i < n; i++) {
        painter.drawLine(x[i], h - ((val3[i] - mny) * (h - 2 * s) / (mxy - mny) + s),
                         x[i + 1], h - ((val3[i + 1] - mny) * (h - 2 * s) / (mxy - mny) + s));
    }

    for (int i = 0; i <= n; i++) {
        if (abs(events[i]) == 1) {
            Pen.setColor(QColor(0, 0, 0));
            Pen.setWidth(1);
            painter.setPen(Pen);
            if (events[i] > 0)
                painter.setBrush(QColor(255, 0, 255));
            else
                painter.setBrush(QColor(255, 255, 0));
            double R = 7;
            painter.drawEllipse(x[i] - R / 2, h - ((val3[i] - mny) * (h - 2 * s) / (mxy - mny) + s + R / 2),
                             R, R);
        }
    }*/


    img2 = img;
}

Histdraw::Histdraw() {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(200, 200);
}

Histdraw::Histdraw(vector<double> ls, QString nm):list(ls),name(nm)
{
     setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
     setMinimumSize(200, 200);     
}
void Histdraw::change(vector<double> ls, QString nm)
{
     list = ls;
     name = nm;
     myresize();
     repaint();
}

