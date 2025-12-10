#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

int main(int argc, char **argv) {
    ifstream fs(argv[1]);
    vector<string> lines;
    string line;
    size_t max_len = 0;

    while (getline(fs, line)) {
        lines.push_back(line);
        if (line.length() > max_len) max_len = line.length();
    }

    while (!lines.empty() && lines.back().empty()) {
        lines.pop_back();
    }

    if (lines.empty()) return 0;

    for (auto &l : lines) {
        l.resize(max_len, ' ');
    }

    long long grand_total = 0;
    int rows = lines.size();
    int cols = max_len;
    
    vector<bool> is_separator(cols, false);
    for (int c = 0; c < cols; ++c) {
        bool all_space = true;
        for (int r = 0; r < rows; ++r) {
            if (lines[r][c] != ' ') {
                all_space = false;
                break;
            }
        }
        if (all_space) is_separator[c] = true;
    }

    for (int c = 0; c < cols; ) {
        if (is_separator[c]) {
            c++;
            continue;
        }
        
        int start_col = c;
        while (c < cols && !is_separator[c]) {
            c++;
        }
        int end_col = c;

        vector<long long> numbers;
        char op = ' ';
        
        for (int k = start_col; k < end_col; ++k) {
            char bottom_char = lines[rows - 1][k];
            if (bottom_char == '+' || bottom_char == '*') {
                op = bottom_char;
            }
            
            string num_str = "";
            for (int r = 0; r < rows - 1; ++r) {
                if (isdigit(lines[r][k])) {
                    num_str += lines[r][k];
                }
            }
            if (!num_str.empty()) {
                numbers.push_back(stoll(num_str));
            }
        }
        
        if (numbers.empty()) continue;
        
        long long result = 0;
        if (op == '+') {
            result = 0;
            for (long long n : numbers) result += n;
        } else if (op == '*') {
            result = 1;
            for (long long n : numbers) result *= n;
        } else {
             if (numbers.size() > 0) {
                 for (long long n : numbers) result += n;
             }
        }
        grand_total += result;
    }
    
    cout << grand_total << endl;
    
    return 0;
}
