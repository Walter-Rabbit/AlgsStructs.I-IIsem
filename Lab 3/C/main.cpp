#include <fstream>

using namespace std;

int main() {
    ifstream fin("radixsort.in");
    ofstream fout("radixsort.out");

    int n, k, m;
    fin >> n >> k >> m;
    int count[26] = {0};
    string a[1001], b[1001];

    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            count[a[j][k - i - 1] - 'a']++;
        }

        for (char c = 'b'; c <= 'z'; c++) {
            count[c - 'a'] += count[c - 'a' - 1];
        }

        for (int j = n - 1; j >= 0; j--) {
            int key = a[j][k - i - 1];
            int counter = count[key - 'a'] - 1;
            b[counter] = a[j];
            count[key - 'a']--;
        }

        for (int j = 0; j < n; j++) {
            a[j] = b[j];
        }

        for (char c = 'a'; c <= 'z'; c++) {
            count[c - 'a'] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        fout << a[i] << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}