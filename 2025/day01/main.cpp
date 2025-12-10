#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
int main(int ac, char **av){
    int b = 50, mdp = 0, max = 0;
    fstream    fs(av[1]);
    string  s;
    while (getline(fs, s)) {
        int v;
        char    id = s[0];
        s.erase(0, 1);
        stringstream    ss;
        ss << s; ss >> v;

        if (v > max) {
            max = v;
        }

        mdp += v / 100;
        v %= 100;

        if (id == 'L') {
            if (b && b - v < 0) {
                mdp ++;
            }
            b -= v;
        } else if (id == 'R') {
            if (/*b && */b + v > 100) {
                mdp ++;
            }
            b += v;
        }

        if (b < 0) {
            b = 100 + b;
        } if (b > 99) {
            b -= 100;
        }

        if (!b) {
            mdp ++;
        }
    }
    cout << mdp << endl;
    return 0;
}