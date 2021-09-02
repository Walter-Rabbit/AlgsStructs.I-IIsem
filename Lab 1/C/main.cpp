#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream in("turtle.in");
    ofstream out("turtle.out");

    int n, m;
    in >> n >> m;
    int field[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> field[i][j];
        }
    }

    int dp[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            if (i == n - 1) {
                if (j == 0) {
                    dp[n - 1][0] = field[n - 1][0];
                }
                else {
                    dp[i][j] = dp[i][j - 1] + field[i][j];
                }
            }

            if (i != n - 1) {
                if (j == 0) {
                    dp[i][j] = dp[i + 1][j] + field[i][j];
                }
                else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]) + field[i][j];
                }
            }
        }
    }

    out << dp[0][m - 1];

    in.close();
    out.close();
    return 0;
}
