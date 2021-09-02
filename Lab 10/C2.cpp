#include <fstream>
#include <vector>
#include <limits>
#include <iostream>

using namespace std;

struct vertex {
    int numberInArray;
    double key;
    bool inQueue;
};

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

void minHeapify(vector <vertex> &a, int i, int n) {
    int l = left(i);
    int r = right(i);
    int smallest;

    if (l <= n && a[l].key < a[i].key) {
        smallest = l;
    }
    else {
        smallest = i;
    }

    if (r <= n && a[r].key < a[smallest].key) {
        smallest = r;
    }

    if (smallest != i) {
        swap(a[i], a[smallest]);
        minHeapify(a, smallest, n);
    }
}

vertex heapExtractMin(vector <vertex> &a, int &n) {
    vertex min = a[1];
    a[1] = a[n];
    n--;
    minHeapify(a, 1, n);
    return min;
}

void heapDecreaseKey(vector <vertex> &a, int i, double key) {
    a[i].key = key;
    while (i > 1 && a[parent(i)].key > a[i].key) {
        swap(a[i], a[parent(i)]);
        i = parent(i);
    }
}

void minHeapInsert(vector <vertex> &a, vertex data, int &n) {
    n++;
    if (n == a.size()) {
        a.push_back({0, 0, false});
    }
    a[n] = data;
    a[n].key = numeric_limits <double>::max();
    heapDecreaseKey(a, n, data.key);
}

//Не работает
int main() {
    ifstream fin("spantree3.in");
    ofstream fout("spantree3.out");

    int n, m;
    fin >> n >> m;

    vector <vertex> vertexes(n);
    int a[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = 0;
        }
    }
    vector <vertex> q;
    q.push_back({ 0, 0, false});

    for (int i = 0; i < n; ++i) {
        int x, y, z;
        fin >> x >> y >> z;
        a[x - 1][y - 1] = z;
        a[y - 1][x - 1] = z;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < n; ++i) {
        vertexes[i] = {i, numeric_limits <double>::max(), false};
    }

    //Prim
    int size = 0;
    vertexes[0].key = 0;
    for (int i = 0; i < vertexes.size(); ++i) {
        vertexes[i].inQueue = true;
        minHeapInsert(q, vertexes[i], size);
    }


    while (size != 0) {
        vertex u = heapExtractMin(q, size);
        vertexes[u.numberInArray].inQueue = false;
        for (int i = 2; i <= size; ++i) {
            int v2;
            int d;
            if (a[u.numberInArray][q[i].numberInArray] == 0) {
                continue;
            }
            else {
                v2 = q[i].numberInArray;
                d = a[u.numberInArray][q[i].numberInArray];
            }
            if (vertexes[v2].inQueue && q[i].key > d) {
                vertexes[v2].key = d;
                heapDecreaseKey(q, i, d);
            }
        }
    }

    double sum = 0;
    for (auto i : vertexes) {
        sum += i.key;
    }
    fout.precision(15);
    fout << sum;

    fin.close();
    fout.close();
}