#include <fstream>

using namespace std;

int binarySearchFirst(int a[], int x, int n) {
    int left = -1;
    int right = n;
    int middle;
    while (right > left + 1) {
        middle = (left + right) / 2;
        if (a[middle] < x) {
            left = middle;
        }
        else {
            right = middle;
        }
    }
    if (a[right] == x) {
        return right + 1;
    }
    else {
        return -1;
    }
}

int binarySearchLast(int a[], int x, int n) {
    int left = -1;
    int right = n;
    int middle;
    while (right > left + 1) {
        middle = (left + right) / 2;
        if (a[middle] <= x) {
            left = middle;
        }
        else {
            right = middle;
        }
    }
    if (a[left] == x) {
        return left + 1;
    }
    else {
        return -1;
    }
}

int main() {
    ifstream fin("binsearch.in");
    ofstream fout("binsearch.out");

    int n;
    fin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    int m;
    fin >> m;
    for (int i = 0; i < m; i++) {
        int x;
        fin >> x;
        fout << binarySearchFirst(a, x, n) << " " << binarySearchLast(a, x, n) << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
