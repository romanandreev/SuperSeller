#include "oracle.h"

Oracle::Oracle()
{
}

double Oracle::goodness(const vector<double>& ls) {
    return profit(ls) / risk(ls);
}
double Oracle::profit(const vector<double>& ls) {
    double prof = ls[ls.size() - 1] - ls[0];
    return prof;
}
double Oracle::risk(const vector<double>& ls) {
    double risk = 1;
    for (int i = 0; i < (int)ls.size(); i++) {
        risk += max(0., ls[0] + (ls[ls.size() - 1] - ls[0]) * i / (ls.size() - 1) - ls[i]);
    }
    return risk;
}

pair<vector<double>, vector<int> > Oracle::get_profit() {
    int len = params.first;
    double c = params.second;
    int n = (int)prices.size() - 1;

    vector<double> profit;
    vector<int> buy;
    vector<double> sum;
    vector<double> sum2;
    sum.push_back(0);
    sum2.push_back(0);
    for (int i = 0; i < n; i++) {
        double diff = prices[i + 1] - prices[i];
        sum.push_back(sum[i] + diff);
        assert(sum2[i] >= 0);
        sum2.push_back(sum2[i] + diff * diff);
    }
    {
        bool has = false;
        for (int i = 0; i <= n; i++) {
            if (i == n) {
                buy.push_back(has ? -1 : 0);
                continue;
            }
            if (i - len + 1 < 0) {
                buy.push_back(0);
                continue;
            }
            double mean = (sum[i] - sum[i - len + 1]) / (len - 1);
            double s2 = max(0., (sum2[i] - sum2[i - len + 1]) / (len - 1) - mean * mean);
            if (!has && 0 < mean - c * sqrt(s2 / (len - 1))) {
                buy.push_back(1);
                has = true;
                continue;
            }
            if (has && mean - c * sqrt(s2 / (len - 1)) < 0) {
                buy.push_back(-1);
                has = false;
                continue;
            }
            buy.push_back(0);
        }
        assert((int)buy.size() == n + 1);
    }
    {
        double share = 0;
        double money = startm;
        bool has = false;
        for (int i = 0; i <= n; i++) {
            if (buy[i] == 1) {
                assert(!has);
                has = true;
                double buymon = min(100., money);
                share = buymon / prices[i];
                money -= buymon;
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
    return make_pair(profit, buy);
}

void Oracle::optimize() {
    int n = (int)prices.size() - 1;
    int bestlen = 2;
    double bestc = 0;
    double bestgood = 0;
    for (int len = 2; len <= n / 10; len++) {
        for (double c = 0; c <= 3; c += 0.2) {
            params = make_pair(len, c);
            double curgood = goodness(get_profit().first);
            if (curgood > bestgood) {
                bestgood = curgood;
                bestlen = len;
                bestc = c;
            }
            //break;
        }
        //break;
    }
    params = make_pair(bestlen, bestc);
}
