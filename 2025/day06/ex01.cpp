#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int ac, char **av) {
    double  sum = 0;
    string  s;
    fstream fs(av[1]);
    vector<char> op;
    vector<vector<int>> tab;


    while (getline(fs, s)) {
        vector<int> one;
        stringstream    ts(s);
        stringstream    ss(s);
        ts >> s;
        if (s.compare("+") && s.compare("*")) {
            int val;
            while (ss >> val) {
                one.push_back(val);
            }
            tab.push_back(one);
        } else {
            char    c;
            while (ss >> c) {
                op.push_back(c);
            }
        }
    }


    for (size_t i = 0; i < op.size(); i ++) {
        if (op[i] == '+') {
            double sumi = 0;
            for (size_t j = 0; j < tab.size(); j ++) {
                sumi += tab[j][i];
            }
            sum += sumi;
        } else {
            double muli = 1;
            for (size_t j = 0; j < tab.size(); j ++) {
                muli *= tab[j][i];
            }
            sum += muli;
        }
    }
    cout << fixed << setprecision(0) << sum << endl;
}
