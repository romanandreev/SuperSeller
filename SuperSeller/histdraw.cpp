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
    //painter.drawLine(0, 0, w, h);
    sort(list.begin(), list.end());
    double mnx = floor(list[0]);
    double mxx = ceil(list[list.size() - 1]);
    if (fabs(mxx - mnx) <= 1e-9) {
        mnx--;
        mxx++;
    }
    vector<double> x, rx;
    vector<int> count;
    for (int i = 0; i <= N; i++) {
        rx.push_back(mnx + (mxx - mnx) / N * i);
        x.push_back(s + (w - 2 * s) * i / N);
    }
    int yk = 0;
    for (int i = 0; i < N; i++) {
        double r = rx[i + 1];
        int cnt = yk;
        while (yk < list.size() && list[yk] <= r) {
            yk++;
        }
        cnt = yk - cnt;
        count.push_back(cnt);
    }
    int mxcount = *max_element(count.begin(), count.end());
    painter.drawLine(s, h - s, w - s, h - s);

    int shift = N;

    for (int i = 0; i <= N; i++) {
        if (x[i] - x[0] >= s / 2) {
            shift = i;
            break;
        }
    }

    for (int i = 0; i <= N; i += shift) {
        painter.drawLine(x[i], h - s, x[i], h - (s - s / 4));
        painter.drawText(x[i], h - (s * 1 / 4), QString::number(rx[i]));
    }

    int cy = 0;
    for (int i = 1; ; i++) {
        if ((h - 2 * s) / i >= s) {
            cy = i;
        } else {
            break;
        }
    }
    int dy = ceil(mxcount / cy);
    for (int i = 0; i <= mxcount; i += dy) {
        painter.drawLine(s, h - (s + (double)(h - 2 * s) * i / mxcount), 0, h - (s + (double)(h - 2 * s) * i / mxcount));
        painter.drawText(2, h - (s + (double)(h - 2 * s) * i / mxcount) - 1,
                         QString::number(i));
    }

    painter.setBrush(Qt::blue);

    for (int i = 0; i < N; i++) {
        double dh = (double)(h - 2 * s) / mxcount * count[i];
        painter.drawRect(x[i], h - s - dh, x[i + 1] - x[i], dh);
    }    

    painter.drawText(w / 2 - s, s / 4, name);
    double mean = 0;
    double s2 = 0;
    //cerr<<"("<<mnx<<" "<<mxx<<")"<<endl;
    for (int i = 0; i < list.size(); i++) {
        mean += list[i];
      //  cerr<<list[i]<<" ";
        s2 += list[i] * list[i];
    }
    //cerr<<endl;
    mean = mean / list.size();
    s2 = s2 / list.size() - mean * mean;
    painter.drawText(w / 2 - 2 * s, s / 2, "Mean = " + QString::number(mean, 'g', 3) + ", S.E. = " + QString::number(sqrt(s2 / list.size()), 'g', 3));
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

