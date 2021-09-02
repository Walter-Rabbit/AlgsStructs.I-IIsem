#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void LCS(const string& x, string y, vector<int>& lastStr) {

    vector<vector<int>> two_str(2, vector<int>(y.length() + 1));

    for (int j = 0; j <= y.length(); j++) {
        two_str[1][j] = 0;
    }

    for (char i : x) {
        for (int j = 0; j <= y.length(); j++) {
            two_str[0][j] = two_str[1][j];
        }

        for (int j = 1; j <= y.length(); j++) {
            if (i == y[j - 1]) {
                two_str[1][j] = two_str[0][j - 1] + 1;
            }
            else {
                two_str[1][j] = max(two_str[1][j - 1], two_str[0][j]);
            }
        }
    }

    for (int j = 0; j <= y.length(); j++) {
        lastStr[j] = two_str[1][j];
    }
}

void two_string(string x, string y) {
    if (y.empty()) {
        return;
    }

    if (x.length() == 1) {
        if (find(y.begin(), y.end(), x[0]) != y.end()) {
            cout << x;
        }
        return;
    }

    int middle = (int) x.length() / 2;

    vector<int> first_str(y.length() + 1);
    vector<int> second_str(y.length() + 1);

    LCS(x.substr(0, middle), y, first_str);

    string x2 = x, y2 = y;
    reverse(x2.begin(), x2.end());
    reverse(y2.begin(), y2.end());
    LCS(x2.substr(0, x.length() - middle), y2, second_str);

    int max = second_str[0];
    int index_max = 0;

    for (int j = 0; j <= y.length(); j++) {
        if (first_str[j] + second_str[y.length() - j] > max) {
            max = first_str[j] + second_str[y.length() - j];
            index_max = j;
        }
    }

    if (first_str[y.length()] > max) {
        index_max = y.length();
    }

    if (middle == 0) {
        middle++;
    }

    two_string(x.substr(0, middle), y.substr(0, index_max));
    two_string(x.substr(middle, x.length()), y.substr(index_max, y.length()));
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    two_string(s1, s2);
    return 0;
}