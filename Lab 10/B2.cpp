#include <fstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct vertex {
    int x, y, numberInArray;
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
        a.push_back({0, 0, 0, 0, false});
    }
    a[n] = data;
    a[n].key = numeric_limits <double>::max();
    heapDecreaseKey(a, n, data.key);
}

double dist(vertex v1, vertex v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}


//Остовное дерево
int main() {
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");

    int n;
    fin >> n;

    vector <vertex> vertexes;
    vector <vertex> q;
    q.push_back({0, 0, 0, 0, false});

    for (int i = 0; i < n; ++i) {
        int x, y;
        fin >> x >> y;
        vertexes.push_back({x, y, i, numeric_limits <double>::max(), false});
    }

    //Prim
    int size = 0;
    vertexes[0].key = 0;
    for (int i = 0; i < vertexes.size(); ++i) {
        minHeapInsert(q, vertexes[i], size);
        vertexes[i].inQueue = true;
    }


    while (size != 0) {
        vertex u = heapExtractMin(q, size);
        vertexes[u.numberInArray].inQueue = false;
        for (int i = 1; i <= size; ++i) {
            int v2;
            double d;
            if (dist(vertexes[u.numberInArray], q[i]) < 0.00001) {
                continue;
            }
            else {
                v2 = q[i].numberInArray;
                d = dist(vertexes[u.numberInArray], q[i]);
            }
            if (vertexes[v2].inQueue && vertexes[v2].key > d) {
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