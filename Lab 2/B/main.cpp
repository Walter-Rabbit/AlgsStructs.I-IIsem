#include <fstream>
#include <string>

using namespace std;

void merge(pair <string, string> A[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    pair <string, string> L[n1 + 2], R[n2 + 2];

    for (int i = 1; i <= n1; i++) {
        L[i] = A[left + i - 1];
    }
    for (int i = 1; i <= n2; i++) {
        R[i] = A[middle + i];
    }

    L[n1 + 1].first = "zzzzzzzzzzzzzz";
    R[n2 + 1].first = "zzzzzzzzzzzzzz";

    for (int i = 1, j = 1, k = left; k <= right; k++) {
        if (L[i].first <= R[j].first) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
    }
}

void sort(pair <string, string> A[], int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;
        sort(A, left, middle);
        sort(A, middle + 1, right);
        merge(A, left, middle, right);
    }
}

int main() {
    int n;
    ifstream fin("race.in");
    ofstream fout("race.out");

    fin >> n;
    pair <string, string> A[n + 1];


    fin >> A[1].first >> A[1].second;
    int country = 1;
    for (int i = 2; i <= n; i++) {
        fin >> A[i].first >> A[i].second;
        if (A[i].first != A[i - 1].first) {
            country++;
        }
    }

    sort(A, 1, n);


    fout << "=== " << A[1].first << " ===\n";
    fout << A[1].second << "\n";
    for (int i = 1, j = 2; i <= country; i++) {
        while (j <= n && A[j - 1].first == A[j].first) {
            fout << A[j].second << "\n";
            j++;
        }
        if(j <= n) {
            fout << "=== " << A[j].first << " ===\n";
            fout << A[j].second << "\n";
            j++;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
