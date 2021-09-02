#include <fstream>

using namespace std;

int main() {
    ifstream in("smallsort.in");
    ofstream out("smallsort.out");

    int n;
    in >> n;
    int array[n];
    for (int i = 0; i < n; i++) {
        in >> array[i];
    }
    for (int j = 1; j < n; j++) {
        int key = array[j];
        int i = j - 1;
        while (array[i] > key && i >= 0) {
            array[i + 1] = array[i];
            i--;
        }
        array[i + 1] = key;
    }

    for (int i = 0; i < n; i++) {
        out << array[i] << " ";
    }

    in.close();
    out.close();
}
