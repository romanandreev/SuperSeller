#include "Histchild.h"


HistChild::HistChild()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(750, 450);
    static int num = 0;
    num++;
    setWindowTitle("Hist " + QString::number(num));

    QWidget *centralW = new QWidget(this);
    QHBoxLayout *centralL = new QHBoxLayout;    
    QVBoxLayout *right = new QVBoxLayout;
    QLabel *text1 = new QLabel("<b>N:</b>");
    str1 = new QLineEdit;
    QString ss;
    ss.setNum(gen.n);
    str1->setText(ss);

    QLabel *text2 = new QLabel("<b>Start money:</b>");
    str2 = new QLineEdit;
    ss.setNum(orac.startm);
    str2->setText(ss);

    QLabel *text7 = new QLabel("<b>Start price <br>(buying on 100$):</b>");
    str7 = new QLineEdit;
    ss.setNum(gen.startp);
    str7->setText(ss);

    QLabel *text3 = new QLabel("<b>Mean of tangent:</b>");
    str3 = new QLineEdit;
    ss.setNum(gen.tan_mean);
    str3->setText(ss);

    QLabel *text4 = new QLabel("<b>S.D. of tangent:</b>");
    str4 = new QLineEdit;
    ss.setNum(gen.tan_sigma);
    str4->setText(ss);

    QLabel *text5 = new QLabel("<b>S.D. of noise:</b>");
    str5 = new QLineEdit;
    ss.setNum(gen.noise_sigma);
    str5->setText(ss);

    QLabel *text6 = new QLabel("<b>Geometric p:</b>");
    str6 = new QLineEdit;
    ss.setNum(gen.geom_p);
    str6->setText(ss);

    QPushButton *button = new QPushButton;
    button->setText("Construct");
    //button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    right->addWidget(text1);
    right->addWidget(str1);
    right->addWidget(text2);
    right->addWidget(str2);
    right->addWidget(text7);
    right->addWidget(str7);
    right->addWidget(text3);
    right->addWidget(str3);
    right->addWidget(text4);
    right->addWidget(str4);
    right->addWidget(text5);
    right->addWidget(str5);
    right->addWidget(text6);
    right->addWidget(str6);
    right->addStretch(1);
    right->addWidget(button);



    Histdraw1 = new Histdraw();
    Histdraw2 = new Histdraw();
    Histdraw3 = new Histdraw();
    Histdraw4 = new Histdraw();
    Histdraw5 = new Histdraw();
    Histdraw6 = new Histdraw();
    pressed();

    QGridLayout *left = new QGridLayout;
    left->addWidget(Histdraw1, 0, 0);
    left->addWidget(Histdraw2, 0, 1);
    left->addWidget(Histdraw3, 0, 2);
    left->addWidget(Histdraw4, 1, 0);
    left->addWidget(Histdraw5, 1, 1);
    left->addWidget(Histdraw6, 1, 2);



    QWidget* rightW = new QWidget(centralW);
    QWidget* leftW = new QWidget(centralW);
    rightW->setLayout(right);
    rightW->setMinimumWidth(120);
    rightW->setMaximumWidth(120);

    leftW->setLayout(left);
    leftW->setMinimumWidth(600);
    centralL->addWidget(leftW);
    centralL->addWidget(rightW);
    centralW->setLayout(centralL);
    centralW->setMinimumHeight(400);
    setCentralWidget(centralW);

    connect(button, SIGNAL(pressed()), this, SLOT(pressed()));   


}
void HistChild::pressed() {
    gen.n = str1->text().toInt();
    orac.startm = str2->text().toDouble();
    gen.startp = str7->text().toDouble();
    gen.tan_mean = str3->text().toDouble();
    gen.tan_sigma = str4->text().toDouble();
    gen.noise_sigma = str5->text().toDouble();
    gen.geom_p = str6->text().toDouble();
    vector<double> ls1, ls2, ls3, ls4, ls5, ls6;
    int N = 1000;
    QProgressDialog* pd = new QProgressDialog("Operation in progress.", "Cancel", 0, N);
    pd->setWindowModality(Qt::WindowModal);
    pd->show();
    for (int i = 0; i < N; i++) {        
        pair<vector<double>, vector<double> > tmp;
        tmp = gen.gen_prices();
        prices1 = tmp.first;
        trend1 = tmp.second;
        tmp = gen.gen_prices();
        prices2 = tmp.first;
        trend2 = tmp.second;
        orac.prices = prices1;
        orac.optimize();


        pair<vector<double>, vector<int> > tmp2;
        tmp2 = orac.get_profit();
        profit1 = tmp2.first;
        orac.prices = prices2;
        tmp2 = orac.get_profit();
        profit2 = tmp2.first;
        ls1.push_back(orac.profit(profit1));
        ls2.push_back(orac.risk(profit1));
        ls3.push_back(orac.goodness(profit1));
        ls4.push_back(orac.profit(profit2));
        ls5.push_back(orac.risk(profit2));
        ls6.push_back(orac.goodness(profit2));
        pd->setValue(i + 1);
        if (pd->wasCanceled())
            break;
    }
    Histdraw1->change(ls1, "Base profit");
    Histdraw2->change(ls2, "Base risk");
    Histdraw3->change(ls3, "Base profit/risk");
    Histdraw4->change(ls4, "Test profit");
    Histdraw5->change(ls5, "Test risk");
    Histdraw6->change(ls6, "Test profit/risk");
}

