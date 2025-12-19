#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

vector<Point> poly;
set<pair<long long,long long>> red;

// Ray casting (point dans polygone orthogonal)
bool inside(long double px, long double py) {
    bool in = false;
    int n = poly.size();
    for (int i = 0, j = n - 1; i < n; j = i++) {
        long double xi = poly[i].x, yi = poly[i].y;
        long double xj = poly[j].x, yj = poly[j].y;

        bool intersect =
            ((yi > py) != (yj > py)) &&
            (px < (xj - xi) * (py - yi) / (yj - yi) + xi);
        if (intersect)
            in = !in;
    }
    return in;
}

int main(int ac, char **av) {
    if (ac < 2) return 1;

    ifstream fs(av[1]);
    string s;

    // Lire les points rouges
    while (getline(fs, s)) {
        long long x = stoll(s.substr(0, s.find(',')));
        long long y = stoll(s.substr(s.find(',') + 1));
        poly.push_back({x, y});
        red.insert({x, y});
    }

    int n = poly.size();

    // Collecte des coordonnées
    vector<long long> xs, ys;
    for (auto &p : poly) {
        xs.push_back(p.x);
        ys.push_back(p.y);
    }

    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    int W = xs.size();
    int H = ys.size();

    // Grille de validité
    vector<vector<bool>> ok(W-1, vector<bool>(H-1, false));

    for (int i = 0; i < W-1; i++) {
        for (int j = 0; j < H-1; j++) {
            long double cx = (xs[i] + xs[i+1]) / 2.0;
            long double cy = (ys[j] + ys[j+1]) / 2.0;
            if (inside(cx, cy))
                ok[i][j] = true;
        }
    }

    long long best = 0;

    // Rectangle maximal
    for (int i1 = 0; i1 < W-1; i1++) {
        vector<int> height(H-1, 0);

        for (int i2 = i1; i2 < W-1; i2++) {
            for (int j = 0; j < H-1; j++) {
                if (ok[i2][j])
                    height[j]++;
                else
                    height[j] = 0;
            }

            // Histogramme
            stack<int> st;
            for (int j = 0; j <= H-1; j++) {
                int h = (j == H-1 ? 0 : height[j]);
                while (!st.empty() && height[st.top()] >= h) {
                    int top = st.top(); st.pop();
                    int width = st.empty() ? j : j - st.top() - 1;

                    long long xmin = xs[i1];
                    long long xmax = xs[i2+1];
                    long long ymin = ys[top];
                    long long ymax = ys[top + width];

                    // Coins doivent être rouges
                    if (red.count({xmin, ymin}) &&
                        red.count({xmax, ymax})) {
                        long long area = (xmax - xmin) * (ymax - ymin);
                        best = max(best, area);
                    }
                }
                st.push(j);
            }
        }
    }

    cout << best << endl;
}
