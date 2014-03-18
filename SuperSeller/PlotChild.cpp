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
    Pen.setColor(QColor(0, 0, 255));
    painter.setPen(Pen);
    int mny = *min_element(prices.begin(), prices.end());
    int mxy = *max_element(prices.begin(), prices.end());
    mny = min(mny, *min_element(profit.begin(), profit.end()));
    mxy = max(mxy, *max_element(profit.begin(), profit.end()));
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

    img2 = img;
}


PlotChild::PlotChild()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(300, 300);
    static int num = 0;
    num++;
    setWindowTitle("Plot " + QString::number(num));



    static default_random_engine eng;
    geometric_distribution<> geom(geom_p);
    normal_distribution<> tan_norm(tan_mean, tan_sigma);
    normal_distribution<> noise_norm(0, noise_sigma);

    {
        prices.push_back(start);
        vector<int> lsx;
        int cur = 0;
        while (cur < n) {
            lsx.push_back(cur);
            cur += geom(eng) + 1;
        }
        lsx.push_back(n);
        for (int i = 0; i < (int)lsx.size() - 1; i++) {
            int dx = lsx[i + 1] - lsx[i];
            int price0 = prices[lsx[i]];
            double tan = tan_norm(eng);
            for (int j = 1; j <= dx; j++) {
                prices.push_back(price0 + (int)(j * tan + noise_norm(eng)));
            }
        }
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
