#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

int countAdjacent(vector<string> v, int x, int y) {
    int c = 0;

    if (x && v[y][x - 1] == '@') {
        c ++;
    } if (x < v[y].size() - 1 && v[y][x + 1] == '@') {
        c ++;
    } if (y && v[y - 1][x] == '@') {
        c ++;
    } if (x && y && v[y - 1][x - 1] == '@') {
        c ++;
    } if (y && x < v[y].size() && v[y - 1][x + 1] == '@') {
        c ++;
    } if (y < v.size() - 1 && v[y + 1][x] == '@') {
        c ++;
    } if (x && y < v.size() - 1 && v[y + 1][x - 1] == '@') {
        c ++;
    } if (x < v[y].size() - 1 && y < v.size() - 1 && v[y + 1][x + 1] == '@') {
        c ++;
    }
    return c;
}

int countAcess(vector<string>& v) {
    int sum = 0;
    vector<string>  copy = v;
    for (size_t y = 0; y < v.size(); y ++) {
        string& s = v[y];
        for (size_t x = 0; x < s.size(); x ++) {
            if (s[x] == '@' && countAdjacent(copy, x, y) < 4) {
                s[x] = 'x';
                sum ++;
            }
        }
    }
    return sum;
}

int    replace_x(vector<string>& v) {
    int del = 0;
    for (size_t i = 0; i < v.size(); i ++) {
        string& s = v[i];
        for (size_t j = 0; j < s.size(); j ++) {
            if (s[j] == 'x') {
                s[j] = '.';
                del ++;
            }
        }
    }
    return del;
}

int main(int ac, char **av) {
    int sum = 0, res = 0;
    string  s;
    fstream fs(av[1]);
    vector<string>  vec;
    while(getline(fs, s)) {
        vec.push_back(s);
    }
    while(res = countAcess(vec)) {
        // cout << res << endl;
        sum += replace_x(vec);
        // replace_x(vec);
    }
    // sum = countAcess(vec);
    // replace_x(vec);
    // for (size_t i = 0; i < vec.size(); i ++) {
    //     cout << vec[i] << endl;
    // }
    cout << sum << endl;
}
