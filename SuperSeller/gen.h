#ifndef GEN_H
#define GEN_H
#include <vector>
#include <random>
#include <assert.h>
#include <iostream>

using namespace std;

class Gen
{
public:
    Gen();
    int n = 100;    
    double startp = 1000;
    double noise_sigma = 10;
    double tan_mean = 2;
    double tan_sigma = 3;
    double geom_p = 0.05;

    pair<vector<double>, vector<double> > gen_prices();    
};

#endif // GEN_H
