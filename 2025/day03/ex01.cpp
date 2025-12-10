#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

void    setFirst(string s, char* m, int* idx) {
    *m = s[0], *idx = 1;
    for (int i = 0; i < s.size() - 1; i ++) {
        if (*m < s[i]) {
            *m = s[i];
            *idx = i + 1;
        }
    }
}

void    setSecond(string s, char* m, int* idx) {
    *m = s[*idx];
    for (int i = *idx; i < s.size(); i ++) {
        if (*m < s[i]) {
            *m = s[i];
            *idx = i;
        }
    }
}

int main(int ac, char **av) {
    int     sum = 0;
    string  s;
    fstream fs(av[1]);
    while (getline(fs, s)) {
        int maxidx, val;
        char max, sec;
        string  ns;
        setFirst(s, &max, &maxidx);
        setSecond(s, &sec, &maxidx);
        ns += max, ns += sec;
        cout << ns << endl;
        stringstream    ss(ns); ss >> val;
        sum += val;
    }
    cout << sum << endl;
}
