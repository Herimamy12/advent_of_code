#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

void    set(string s, char* m, int* idx, int first, int deb) {
    if (first == s.size()) {
        first --;
    }
    *m = s[first], *idx = first;
    for (int i = first; i < s.size() - deb; i ++) {
        if (*m < s[i]) {
            *m = s[i];
            *idx = i;
        }
    }
}

int main(int ac, char **av) {
    unsigned long long int     sum = 0;
    string  s;
    fstream fs(av[1]);
    while (getline(fs, s)) {
        string  ns;
        unsigned long long int val;
        int maxidx, first = 0, n = 11;
        for (int i = 0; i <= n; i ++) {
            char max;
            set(s, &max, &maxidx, first, n - i);
            ns += max;
            first = maxidx + 1;
        }
        // cout << ns << endl;
        stringstream    ss(ns); ss >> val;
        sum += val;
    }
    cout << sum << endl;
}
