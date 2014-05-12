#include "gen.h"

Gen::Gen()
{
}

pair<vector<double>, vector<double> > Gen::gen_prices() {
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
