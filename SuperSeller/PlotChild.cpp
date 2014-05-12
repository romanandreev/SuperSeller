#include "plotchild.h"


PlotChild::PlotChild()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(350, 450);
    static int num = 0;
    num++;
    setWindowTitle("Plot " + QString::number(num));

    QWidget *centralW = new QWidget(this);
    QHBoxLayout *centralL = new QHBoxLayout;
    QVBoxLayout *left = new QVBoxLayout;
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

    text8 = new QLabel("<b>Best len = ?</b>");
    text9 = new QLabel("<b>Best c = ?</b>");


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
    right->addWidget(text8);
    right->addWidget(text9);
    right->addStretch(1);
    right->addWidget(button);



    plotdraw1 = new Plotdraw();
    plotdraw2 = new Plotdraw();
    pressed();

    left->addWidget(plotdraw1);
    left->addWidget(plotdraw2);


    QWidget* rightW = new QWidget(centralW);
    QWidget* leftW = new QWidget(centralW);
    rightW->setLayout(right);
    rightW->setMinimumWidth(120);
    rightW->setMaximumWidth(120);

    leftW->setLayout(left);
    leftW->setMinimumWidth(200);
    centralL->addWidget(leftW);
    centralL->addWidget(rightW);
    centralW->setLayout(centralL);
    centralW->setMinimumHeight(400);
    setCentralWidget(centralW);

    connect(button, SIGNAL(pressed()), this, SLOT(pressed()));   


}
void PlotChild::pressed() {
    gen.n = str1->text().toInt();
    orac.startm = str2->text().toDouble();
    gen.startp = str7->text().toDouble();
    gen.tan_mean = str3->text().toDouble();
    gen.tan_sigma = str4->text().toDouble();
    gen.noise_sigma = str5->text().toDouble();
    gen.geom_p = str6->text().toDouble();
    pair<vector<double>, vector<double> > tmp;
    tmp = gen.gen_prices();
    prices1 = tmp.first;
    trend1 = tmp.second;
    tmp = gen.gen_prices();
    prices2 = tmp.first;
    trend2 = tmp.second;
    orac.prices = prices1;
    orac.optimize();

    //cerr<<params.first<<" "<<params.second<<endl;
    text8->setText("<b>Best len = </b>" + QString::number(orac.params.first));
    text9->setText("<b>Best c = </b>" + QString::number(orac.params.second));

    pair<vector<double>, vector<int> > tmp2;
    tmp2 = orac.get_profit();
    profit1 = tmp2.first;
    buysell1 = tmp2.second;
    orac.prices = prices2;
    tmp2 = orac.get_profit();
    profit2 = tmp2.first;
    buysell2 = tmp2.second;
    plotdraw1->change(prices1, profit1, trend1, buysell1);
    plotdraw2->change(prices2, profit2, trend2, buysell2);
}

