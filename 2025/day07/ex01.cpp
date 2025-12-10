#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class SplitedBeam {
    private:
        int             _sNumbers, _lSize;
        vector<string>  _vec;

        void    _draw();
        void    _showTree();
        void    _drawFirstLine();
        void    _drawSplitedLine(string& l, int lastRef);
        void    _drawLineContinue(string& l, int lastRef);

    public:
        SplitedBeam(vector<string>& vec);
        ~SplitedBeam();

        int getSplitedNumbers() const;
};

SplitedBeam::SplitedBeam(vector<string>& vec) : _sNumbers(0), _lSize(0), _vec(vec) {
    _lSize = _vec[0].size();
    _drawFirstLine();
    _draw();
    // _showTree();
}

SplitedBeam::~SplitedBeam() {}

int SplitedBeam::getSplitedNumbers() const {
    return _sNumbers;
}

void    SplitedBeam::_showTree() {
    for (size_t i = 0; i < _vec.size(); i ++) {
        cout << _vec[i] << endl;
    }
}

void    SplitedBeam::_draw() {
    for (size_t i = 2; i < _vec.size(); i ++) {
        string& l = _vec[i];
        _drawLineContinue(l, i - 1);
        _drawSplitedLine(l, i - 1);
    }
}

void    SplitedBeam::_drawLineContinue(string& l, int lastRef) {
    for (int i = 0; i < _lSize; i ++) {
        if (_vec[lastRef][i] == '|' && l[i] != '^') {
            l[i] = '|';
        }
    }
}

void    SplitedBeam::_drawSplitedLine(string& l, int lastRef) {
    for (int i = 0; i < _lSize; i ++) {
        if (l[i] == '^' && _vec[lastRef][i] == '|') {
            if (i) {
                l[i - 1] = '|';
            }
            if (i < _lSize - 1) {
                l[i + 1] = '|';
            }
            _sNumbers ++;
        }
    }
}

void    SplitedBeam::_drawFirstLine() {
    string& l = _vec[0];
    for (int i = 0; i < _lSize; i ++) {
        if (l[i] == 'S') {
            _vec[1][i] = '|';
            break ;
        }
    }
}

/********************************************** */

int main(int ac, char **av) {
    string  s;
    fstream fs(av[1]);

    vector<string>  vec;
    while(getline(fs, s)) {
        vec.push_back(s);
    }
    SplitedBeam sb(vec);
    cout << sb.getSplitedNumbers() << endl;
}
