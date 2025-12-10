#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    unsigned long long int start;
    unsigned long long int end;
    
    Range(unsigned long long int s, unsigned long long int e) : start(s), end(e) {}
};

void mergeRanges(vector<Range>& ranges) {
    sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        return a.start < b.start;
    });

    vector<Range> merged;
    
    for (const auto& range : ranges) {
        if (merged.empty() || merged.back().end < range.start) {
            merged.push_back(range);
        } else {
            merged.back().end = max(merged.back().end, range.end);
        }
    }
    
    ranges = merged;
}

int main(int ac, char **av) {
    vector<Range> freshRanges;
    vector<unsigned long long int> availableIds;
    string s;
    fstream fs(av[1]);
    
    while (getline(fs, s)) {
        if (s.find("-") != string::npos) {
            unsigned long long int id, val;
            stringstream ss(s);
            ss >> id;
            s = s.substr(s.find("-") + 1);
            stringstream nss(s);
            nss >> val;
            freshRanges.push_back(Range(id, val));
        } else {
            unsigned long long int val;
            stringstream ss(s);
            ss >> val;
            availableIds.push_back(val);
        }
    }
    mergeRanges(freshRanges);
    int sum = 0;
    for (auto id : availableIds) {
        for (auto& range : freshRanges) {
            if (id >= range.start && id <= range.end) {
                sum++;
                break;
            }
        }
    }
    cout << sum << endl;
    return 0;
}
