#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

long double mean_y(std::vector<std::pair<int, int>>& xy, int n) {
    long double mean = 0;
    for (int i = 0; i < n; ++i) {
        mean += xy[i].second;
    }
    return mean / n;
}

long double sq_y(std::vector<std::pair<int, int>>& xy, int n) {
    long double mean = 0;
    for (int i = 0; i < n; ++i) {
        mean += xy[i].second * xy[i].second;
    }
    return mean / n;

}

long double f(int x, long double a, long double b, long double t) {
    if (x < t) {
        return a;
    }
    return b;
}

long double get_loss(std::vector<std::pair<int, int>>& xy, long double a, long double b, long double t, int n) {
    long double loss = 0;
    for (int i = 0; i < n; ++i) {
        long double f_x = f(xy[i].first, a, b, t);
        loss += (f_x - xy[i].second) * ((f_x - xy[i].second));
    }
    return loss / n;
}

int main() {
    int n, x, y;
    std::cin >> n;
    std::vector<std::pair<int,int>> xy;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        xy.emplace_back(x, y);
    }
    std::sort(xy.begin(), xy.end(), [](auto &left, auto &right) {
        return left.first < right.first;
    });

    long double a;
    long double b;
    long double t;

    long double opta, optb, optt;
    long double minloss = 10000000000;
    long double loss;

    t = xy[0].first - 1;
    a = mean_y(xy, n);
    b = a;
    loss = get_loss(xy, a, b, t, n);
    if (loss < minloss) {
        opta = a;
        optb = b;
        optt = t;
        minloss = loss;
    }

    a = 0;
    b = mean_y(xy, n);
    long double asq = 0;
    long double bsq = sq_y(xy, n);
    long double loss1;
    for (int i = 0; i < n - 1; ++i) {

        asq *= i;
        asq += xy[i].second * xy[i].second;
        asq /= (i + 1);
        bsq *= (n - i);
        bsq -= xy[i].second * xy[i].second;
        bsq /= (n - i - 1);

        a *= i;
        a += xy[i].second;
        a /= (i + 1);
        b *= (n - i);
        b -= xy[i].second;
        b /= (n - i - 1);

        if (xy[i].first == xy[i + 1].first) {
            continue;
        }
        t = static_cast<long double>((xy[i].first + xy[i + 1].first)) / 2;
//        loss1 = get_loss(xy, a, b, t, n);
        loss = (((asq - a * a) * (i + 1)) + ((bsq - b * b) * (n - i - 1))) / n;
//        if (loss1 != loss) {
//            std::cout << i << " " << loss << " " << loss1 << " || " << xy[i].first << " " << xy[i].second << "\n";
//        }
        if (loss < minloss) {
            opta = a;
            optb = b;
            optt = t;
            minloss = loss;
        }
    }
    std::cout << opta << " " << optb << " " << optt;
}