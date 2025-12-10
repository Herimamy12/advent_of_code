#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

class QuantumBeam {
    private:
        vector<string> grid;
        int rows, cols;
        map<pair<int,int>, long long> memo;

        int nextSplitter(int row, int col) {
            for (int r = row; r < rows; r++) {
                if (grid[r][col] == '^') return r;
            }
            return -1;
        }

        long long countTimelines(int row, int col) {
            if (col < 0 || col >= cols) return 1;
            auto key = make_pair(row, col);
            if (memo.count(key)) return memo[key];

            int ns = nextSplitter(row, col);
            if (ns == -1) {
                memo[key] = 1;
                return 1;
            }

            long long left = countTimelines(ns+1, col-1);
            long long right = countTimelines(ns+1, col+1);
            memo[key] = left + right;
            return memo[key];
        }

    public:
        QuantumBeam(vector<string>& vec) : grid(vec) {
            rows = grid.size();
            cols = grid[0].size();
        }

        long long solve() {
            int startCol = -1;
            for (int c = 0; c < cols; c++) {
                if (grid[0][c] == 'S') {
                    startCol = c;
                    break;
                }
            }
            return countTimelines(1, startCol);
        }
};

int main(int ac, char **av) {
    string s;
    fstream fs(av[1]);
    vector<string> vec;
    while(getline(fs, s)) {
        vec.push_back(s);
    }
    QuantumBeam qb(vec);
    cout << qb.solve() << endl;
}
