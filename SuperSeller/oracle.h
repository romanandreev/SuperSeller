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
    double startm = 200;
    double goodness(const vector<double>&);
    double profit(const vector<double>&);
    double risk(const vector<double>&);
    pair<int, double> params;
    vector<double> prices;
    pair<vector<double>, vector<int> > get_profit();
    void optimize();
};

#endif // ORACLE_H
