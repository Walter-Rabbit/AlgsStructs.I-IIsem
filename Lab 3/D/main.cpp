#include <fstream>

using namespace std;

ifstream fin("priorityqueue.in");
ofstream fout("priorityqueue.out");

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

void minHeapify(int a[], int i, int n) {
    int l = left(i);
    int r = right(i);
    int smallest;

    if (l <= n && a[l] < a[i]) {
        smallest = l;
    }
    else {
        smallest = i;
    }

    if (r <= n && a[r] < a[smallest]) {
        smallest = r;
    }

    if (smallest != i) {
        swap(a[i], a[smallest]);
        minHeapify(a, smallest, n);
    }
}

void heapExractMin(int a[], int &n) {
    if (n < 1) {
        fout << "*\n";
        return;
    }
    int min = a[1];
    a[1] = a[n];
    n--;
    minHeapify(a, 1, n);
    fout << min << "\n";
    return;
}

void heapDecreaseKey(int a[], int i, int key) {
    a[i] = key;
    while (i > 1 && a[parent(i)] > a[i]) {
        swap(a[i], a[parent(i)]);
        i = parent(i);
    }
}

void minHeapInsert(int a[], int key, int &n) {
    n++;
    a[n] = INT_MAX;
    heapDecreaseKey(a, n, key);
}

int main() {
    int archive[100000], heap[100000];
    string command;
    int x, y, n = 0, count = 0;

    while (fin >> command) {
        if (command == "push") {
            fin >> x;
            minHeapInsert(heap, x, n);
        }

        else if (command == "extract-min") {
            x = -1;
            heapExractMin(heap, n);
        }

        else if (command == "decrease-key") {
            fin >> x >> y;
            int i;
            for (i = 1; i <= n; i++) {
                if (archive[x] == heap[i]) {
                    break;
                }
            }
            heapDecreaseKey(heap, i, y);
            archive[x] = y;
        }

        count++;
        archive[count] = x;
    }

    fin.close();
    fout.close();
    return 0;
}
