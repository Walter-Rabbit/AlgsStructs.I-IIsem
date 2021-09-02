#include <fstream>

using namespace std;

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

void maxHeapify(int a[], int i, int n) {
    int l = left(i);
    int r = right(i);
    int largest;

    if (l <= n && a[l] > a[i]) {
        largest = l;
    }
    else {
        largest = i;
    }

    if (r <= n && a[r] > a[largest]) {
        largest = r;
    }

    if (largest != i) {
        swap(a[i], a[largest]);
        maxHeapify(a, largest, n);
    }
}

void buildMaxHeap(int a[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        maxHeapify(a, i, n);
    }
}

void heapSort(int a[], int n) {
    buildMaxHeap(a, n);
    for (int i = n; i >= 2; i--) {
        swap(a[1], a[i]);
        n--;
        maxHeapify(a, 1, n);
    }
}

int main() {
    ifstream fin("sort.in");
    ofstream fout("sort.out");

    int n;
    fin >> n;
    int heap[n + 1];
    for (int i = 1; i <= n; i++) {
        fin >> heap[i];
    }

    heapSort(heap, n);

    for (int i = 1; i <= n; i++) {
        fout << heap[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
