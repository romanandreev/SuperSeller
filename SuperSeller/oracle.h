#ifndef ORACLE_H
#define ORACLE_H
#include <vector>
#include <random>
#include <assert.h>
#include <iostream>

using namespace std;

class Oracle
{
public:
    Oracle();
    int n = 100;
    double startm = 200;
    double startp = 1000;
    double noise_sigma = 10;
    double tan_mean = 2;
    double tan_sigma = 3;
    double geom_p = 0.05;

    double goodness(const vector<double>&);
    double profit(const vector<double>&);
    double risk(const vector<double>&);

    pair<vector<double>, vector<double> > gen_prices();
    pair<vector<double>, vector<int> > get_profit(vector<double>&, pair<int, double>);
    pair<int, double> optimize(vector<double>& prices);
};

#endif // ORACLE_H
