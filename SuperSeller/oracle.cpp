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

pair<vector<double>, vector<double> > Oracle::gen_prices() {
    static default_random_engine eng(239);
    geometric_distribution<> geom(geom_p);
    normal_distribution<> tan_norm(tan_mean, tan_sigma);
    normal_distribution<> noise_norm(0, noise_sigma);
    vector<double> prices;
    vector<double> trend;

    trend.push_back(startp);
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

    for (int i = 0; i <= n; i++) {
        prices[i] = max(prices[i], 1.);
    }

    return make_pair(prices, trend);
}
pair<vector<double>, vector<int> > Oracle::get_profit(vector<double>& prices, pair<int, double> params) {
    int len = params.first;
    double c = params.second;

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

pair<int, double> Oracle::optimize(vector<double>& prices) {
    int bestlen = 2;
    double bestc = 0;
    double bestgood = 0;
    for (int len = 2; len <= n / 10; len++) {
        for (double c = 0; c <= 3; c += 0.02) {
            double curgood = goodness(get_profit(prices, make_pair(len, c)).first);
            if (curgood > bestgood) {
                bestgood = curgood;
                bestlen = len;
                bestc = c;
            }
            //break;
        }
        //break;
    }
    return make_pair(bestlen, bestc);
}
