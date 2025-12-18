#include <bits/stdc++.h>
using namespace std;

/* ---------- Union-Find ---------- */
struct UnionFind {
    vector<int> parent, sz;

    UnionFind(int n) : parent(n), sz(n, 1) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // déjà dans le même circuit

        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

/* ---------- Données ---------- */
struct Point {
    long long x, y, z;
};

struct Edge {
    int u, v;
    long long d2;
};

long long dist2(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
}

/* ---------- Programme principal ---------- */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " input.txt\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Erreur: impossible d'ouvrir le fichier\n";
        return 1;
    }

    vector<Point> pts;
    string line;

    // Lecture des points
    while (getline(fin, line)) {
        if (line.empty()) continue;
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        Point p;
        ss >> p.x >> p.y >> p.z;
        pts.push_back(p);
    }

    int n = pts.size();
    vector<Edge> edges;

    // Toutes les paires
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({i, j, dist2(pts[i], pts[j])});
        }
    }

    // Tri par distance croissante
    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) {
             return a.d2 < b.d2;
         });

    UnionFind uf(n);
    int connections = 0;

    // Connexion des 1000 paires les plus proches
    for (const auto& e : edges) {
        if (connections == 1000) break;
        if (uf.unite(e.u, e.v)) {
            connections++;
        }
    }

    // Comptage des tailles des circuits
    unordered_map<int, int> circuitSizes;
    for (int i = 0; i < n; i++) {
        circuitSizes[uf.find(i)]++;
    }

    vector<int> sizes;
    for (auto& [_, s] : circuitSizes)
        sizes.push_back(s);

    sort(sizes.begin(), sizes.end(), greater<int>());

    long long result = 1;
    for (int i = 0; i < 3; i++)
        result *= sizes[i];

    cout << result << endl;
    return 0;
}
