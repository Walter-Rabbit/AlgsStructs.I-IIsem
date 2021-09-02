#include <fstream>

using namespace std;

long long counter = 0;

void merge(int A[], int left, int middle, int  right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1 + 2], R[n2 + 2];

    for (int i = 1; i <= n1; i++) {
        L[i] = A[left + i - 1];
    }
    for (int i = 1; i <= n2; i++) {
        R[i] = A[middle + i];
    }

    L[n1 + 1] = INT_MAX;
    R[n2 + 1] = INT_MAX;

    for (int i = 1, j = 1, k = left; k <= right; k++) {
        if(L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            counter += n1 - i + 1;
            A[k] = R[j];
            j++;
        }
    }
}

void merge_sort(int A[], int left, int right) {
    if(left < right) {
        int middle = (left + right) / 2;
        merge_sort(A, left, middle);
        merge_sort(A, middle + 1, right);
        merge(A, left, middle, right);
    }
}

int main() {
    ifstream fin("inversions.in");
    ofstream fout("inversions.out");
    int n;
    fin >> n;
    int A[n + 1];
    for (int i = 1; i <= n; i++) {
        fin >> A[i];
    }

    merge_sort(A, 1, n);

    fout << counter;

    fin.close();
    fout.close();
    return 0;
}