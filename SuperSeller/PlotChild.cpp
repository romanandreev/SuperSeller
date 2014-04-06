#include "plotchild.h"


void PlotChild::paintEvent(QPaintEvent*) {
    QPainter outpainter(this);
    outpainter.drawImage(0,0, img2);
}


void PlotChild::resizeEvent(QResizeEvent *){    
    img = QImage(width(), height(), QImage::Format_RGB32);
    int w = width();
    int h = height();
    int s = 24;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            img.setPixel(i, j, QColor(255, 255, 255).rgb());
        }
    }
    QPainter painter(&img);
    //painter.setRenderHint(QPainter::Antialiasing);
    QPen Pen((QColor(0,0,0)),1);
    painter.setPen(Pen);
    painter.drawLine(s, h - s, w - s, h - s);
    QPolygonF arrowHead;
    painter.setBrush(Qt::black);
    arrowHead.clear();
    arrowHead << QPointF(w - s, h - s)
              << QPointF(w - s - s / 2, h - (s - s / 4))
              << QPointF(w - s - s / 2, h - (s + s / 4));
    painter.drawPolygon(arrowHead);
    painter.drawLine(s, s, s, h - s);
    arrowHead.clear();
    arrowHead << QPointF(s, s)
              << QPointF(s - s / 4, s + s / 2)
              << QPointF(s + s / 4, s + s / 2);
    painter.drawPolygon(arrowHead);
    painter.drawLine(s, s, s, h - s);



    vector<int> x;
    int shift = n;
    for (int i = 0; i <= n; i++) {
        x.push_back(s + (w - 3 * s) * i / n);
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


    double mny = *min_element(prices.begin(), prices.end());
    double mxy = *max_element(prices.begin(), prices.end());
    mny = min(mny, *min_element(profit.begin(), profit.end()));
    mxy = max(mxy, *max_element(profit.begin(), profit.end()));
    mny = min(mny, *min_element(trend.begin(), trend.end()));
    mxy = max(mxy, *max_element(trend.begin(), trend.end()));

    int cy = 0;
    for (int i = 1; ; i++) {
        if ((h - 4 * s) / i >= s) {
            cy = i;
        } else {
            break;
        }
    }

    for (int i = 0; i <= cy; i ++) {
        painter.drawLine(s, h - (s * 2 + (double)(h - 4 * s) * i / cy), 0, h - (s * 2 + (double)(h - 4 * s) * i / cy));
        painter.drawText(0, h - (s * 2 + (double)(h - 4 * s) * i / cy) - 1,
                         QString::number((int)(mny + (mxy - mny) * ((double)i / cy))));
    }

    Pen.setColor(QColor(0, 0, 255));
    Pen.setWidth(2);
    painter.setPen(Pen);

    for (int i = 0; i < n; i++) {
        painter.drawLine(x[i], h - ((prices[i] - mny) * (h - 4 * s) / (mxy - mny) + 2 * s),
                         x[i + 1], h - ((prices[i + 1] - mny) * (h - 4 * s) / (mxy - mny) + 2 * s));
    }
    Pen.setColor(QColor(255, 0, 0));
    painter.setPen(Pen);
    for (int i = 0; i < n; i++) {
        painter.drawLine(x[i], h - ((profit[i] - mny) * (h - 4 * s) / (mxy - mny) + 2 * s),
                         x[i + 1], h - ((profit[i + 1] - mny) * (h - 4 * s) / (mxy - mny) + 2 * s));
    }
    Pen.setColor(QColor(0, 255, 0));
    painter.setPen(Pen);
    for (int i = 0; i < n; i++) {        
        painter.drawLine(x[i], h - ((trend[i] - mny) * (h - 4 * s) / (mxy - mny) + 2 * s),
                         x[i + 1], h - ((trend[i + 1] - mny) * (h - 4 * s) / (mxy - mny) + 2 * s));
    }    
    for (int i = 0; i <= n; i++) {
        if (abs(buy[i]) == 1) {
            Pen.setColor(QColor(0, 0, 0));
            Pen.setWidth(1);
            painter.setPen(Pen);
            if (buy[i] > 0)
                painter.setBrush(QColor(255, 0, 255));
            else
                painter.setBrush(QColor(255, 255, 0));
            double R = 7;
            painter.drawEllipse(x[i] - R / 2, h - ((prices[i] - mny) * (h - 4 * s) / (mxy - mny) + 2 * s + R / 2),
                             R, R);
        }
    }
    img2 = img;
}


PlotChild::PlotChild()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(200, 200);
    static int num = 0;
    num++;
    setWindowTitle("Plot " + QString::number(num));



    static default_random_engine eng;
    geometric_distribution<> geom(geom_p);
    normal_distribution<> tan_norm(tan_mean, tan_sigma);
    normal_distribution<> noise_norm(0, noise_sigma);

    {
        trend.push_back(start);
        vector<int> lsx;
        int cur = 0;
        while (cur < n) {
            lsx.push_back(cur);
            cur += geom(eng) + 1;
        }
        lsx.push_back(n);
        for (int i = 0; i < (int)lsx.size() - 1; i++) {
            double dx = lsx[i + 1] - lsx[i];
            double price0 = trend[lsx[i]];
            double tan = tan_norm(eng);
            for (int j = 1; j <= dx; j++) {
                trend.push_back(price0 + (j * tan));
            }
        }
        double sum_norm = 0;
        for (int i = 0; i <= n; i++) {
            sum_norm += (i == 0 ? 0 : noise_norm(eng));
            prices.push_back(trend[i] + sum_norm);
        }
        assert((int)trend.size() == n + 1);
        assert((int)prices.size() == n + 1);
    }
    {
        int cur = 0;
        bool has = false;
        for (int i = 0; i <= n; i++) {
            if (i == n) {
                buy.push_back(has ? -1 : 0);
                continue;
            }
            if (!has) {
                buy.push_back(1);
                has = true;
                cur = prices[i];
                continue;
            }
            if (prices[i] > cur) {
                buy.push_back(-1);
                has = false;
            } else {
                buy.push_back(0);
            }
        }
        assert((int)buy.size() == n + 1);
    }
    {
        double share = 0;
        double money = 1000;
        bool has = false;
        for (int i = 0; i <= n; i++) {
            if (buy[i] == 1) {
                assert(!has);
                has = true;
                share = 100. / prices[i];
                money -= 100;
            } else
            if (buy[i] == -1) {
                assert(has);
                has = false;
                money += share * prices[i];
                share = 0;
            }
            profit.push_back(money + share * prices[i]);
        }
        assert((int)profit.size() == n + 1);
    }
}
