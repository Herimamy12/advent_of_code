#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

unsigned long long int geta(string s) {
    unsigned long long int a;
    stringstream    ss(s);
    ss >> a;
    return a;
}

unsigned long long int getb(string s) {
    unsigned long long int b;
    stringstream    ss(s.substr(s.find("-") + 1));
    ss >> b;
    return b;
}

bool    twoid(string sa) {
    if (sa.size() < 2 || sa.size() % 2)
        return false;
    string  f, l;
    f = sa.substr(0, sa.size() / 2);
    l = sa.substr(sa.size() / 2);
    return !f.compare(l);
}

bool    threeid(string sa) {
    if (sa.size() < 3 || sa.size() % 3)
        return false;
    string  f, l, d;
    f = sa.substr(0, sa.size() / 3);
    l = sa.substr(sa.size() / 3, sa.size() / 3);
    d = sa.substr(sa.size() / 3 + sa.size() / 3);
    return (!f.compare(l) && !l.compare(d));
}

bool    fiveid(string sa) {
    if (sa.size() < 5 || sa.size() % 5)
        return false;
    string  f, l, d, k, i;
    f = sa.substr(0, sa.size() / 5);
    l = sa.substr(sa.size() / 5, sa.size() / 5);
    d = sa.substr((sa.size() / 5) * 2 , sa.size() / 5);
    k = sa.substr((sa.size() / 5) * 3 , sa.size() / 5);
    i = sa.substr((sa.size() / 5) * 4 , sa.size() / 5);
    return (!f.compare(l) && !l.compare(d) && !d.compare(k) && !k.compare(i));
}

bool    sevenid(string sa) {
    if (sa.size() < 7 || sa.size() % 7)
        return false;
    string  f, l, d, k, i, m, n;
    f = sa.substr(0, sa.size() / 7);
    l = sa.substr(sa.size() / 7, sa.size() / 7);
    d = sa.substr((sa.size() / 7) * 2 , sa.size() / 7);
    k = sa.substr((sa.size() / 7) * 3 , sa.size() / 7);
    i = sa.substr((sa.size() / 7) * 4 , sa.size() / 7);
    m = sa.substr((sa.size() / 7) * 5 , sa.size() / 7);
    n = sa.substr((sa.size() / 7) * 6 , sa.size() / 7);
    return (!f.compare(l) && !l.compare(d) && !d.compare(k) && !k.compare(i) && !i.compare(m) && !m.compare(n));
}

int main(int ac, char **av) {
    unsigned long long int sum = 0;
    string  s;
    fstream fs(av[1]);
    while (getline(fs, s, ',')) {
        unsigned long long int a, b;
        a = geta(s); b = getb(s);
        for (; a <= b; a ++) {
            string sa;
            stringstream ss;
            ss << a; ss >> sa;
            if (twoid(sa) || threeid(sa) || fiveid(sa) || sevenid(sa))
                sum += a;
        }
    }
    cout << sum << endl;
}