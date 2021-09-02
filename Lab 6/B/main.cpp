#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct map {
private:
    vector<pair<string, string>> list[50000];

    static int hash(const string &x) {
        int h = 0;
        for (char i : x) {
            h += i;
        }
        if (x.length() > 1) {
            h *= x[1];
        }
        return h % 50000;
    }

public:
    void push(const string& key, const string& x) {
        int index = hash(key);
        int fl = -1;
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].first == key) {
                fl = i;
                break;
            }
        }
        if (fl == -1) {
            list[index].push_back({key, x});
        }
        else {
            list[index][fl] = {key, x};
        }
    }

    void erase(const string& key) {
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].first == key) {
                list[index].erase(list[index].begin() + i);
                break;
            }
        }
    }

    string get(const string &key) {
        int index = hash(key);
        bool fl = false;
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].first == key) {
                return list[index][i].second;
                break;
            }
        }
        return "none";
    }
};

int main() {
    ifstream fin("map.in");
    ofstream fout("map.out");

    string command, key, x;
    map a;
    while (fin >> command) {
        if (command == "put") {
            fin >> key >> x;
            a.push(key, x);
            continue;
        }
        if (command == "delete") {
            fin >> key;
            a.erase(key);
            continue;
        }
        if (command == "get") {
            fin >> key;
            fout << a.get(key) << "\n";
            continue;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
