#include <fstream>

using namespace std;

int main() {
    ifstream in("sortland.in");
    ofstream out("sortland.out");

    int n;
    in >> n;
    pair <double, int> array[n];
    for (int i = 1; i <= n; i++) {
        in >> array[i].first;
        array[i].second = i;
    }

    for (int j = 2; j <= n; j++) {
        pair <double, int> key = array[j];
        int i = j - 1;
        while (array[i].first > key.first && i > 0) {
            array[i + 1] = array[i];
            i--;
        }
        array[i + 1] = key;
    }

    out << array[1].second << " " << array[n / 2 + 1].second << " " << array[n].second;

    in.close();
    out.close();
}
