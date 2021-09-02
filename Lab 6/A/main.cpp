#include <fstream>
#include <vector>

using namespace std;

struct set {
private:
    vector<int> list[50000];

    static int hash(int x) {
        return (x + 1000000000) % 50000;
    }

public:
    void insert(int x) {
        int index = hash(x);
        bool fl = false;
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i] == x) {
                fl = true;
                break;
            }
        }
        if (!fl) {
            list[index].push_back(x);
        }
    }

    void extract(int x) {
        int index = hash(x);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i] == x) {
                list[index].erase(list[index].begin() + i);
                break;
            }
        }
    }

    string exists(int x) {
        int index = hash(x);
        bool fl = false;
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i] == x) {
                fl = true;
                break;
            }
        }
        if (fl) {
            return "true\n";
        }
        else {
            return "false\n";
        }
    }
};

int main() {
    ifstream fin("set.in");
    ofstream fout("set.out");

    string command;
    int x;
    set a;
    while (fin >> command) {
        fin >> x;

        if (command[0] == 'i') {
            a.insert(x);
        }

        if (command[0] == 'd') {
            a.extract(x);
        }

        if (command[0] == 'e') {
            fout << a.exists(x);
        }
    }

    fin.close();
    fout.close();
    return 0;
}