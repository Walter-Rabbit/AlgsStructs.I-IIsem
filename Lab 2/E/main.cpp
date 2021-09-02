#include <fstream>
#include <iostream>

using namespace std;

void qsort_k(int A[], int left, int right, int k) {

    int i = left, j = right;
    int middle = (i + j) / 2;
    int key = A[middle];
    
    if (left == right) {
        return;
    }
    
    while (i <= j) {
        while (A[i] < key){
            i++;
        }
        while (A[j] > key){
            j--;
        }
        if (i <= j) {
            swap(A[i], A[j]);
            i++;
            j--;
        }
    }
    if (k >= i && k <= right) {
        qsort_k(A, i, right, k);
        return;
    }
    if (k <= j && k >= left){
        qsort_k(A, left, j, k);
        return;
    }
}

int main() {
    ifstream fin("kth.in");
    ofstream fout("kth.out");

    int n, k;
    fin >> n >> k;
    int a, b, c, a1, a2;
    fin >> a >> b >> c >> a1 >> a2;

    int A[n];
    A[0] = a1;
    A[1] = a2;
    for (int i = 2; i < n; i++) {
        A[i] = a * A[i - 2] + b * A[i - 1] + c;
    }
    
	qsort_k(A, 0, n - 1, k - 1);
	fout << A[k - 1] << "\n";

    fin.close();
    fout.close();
    return 0;
}
