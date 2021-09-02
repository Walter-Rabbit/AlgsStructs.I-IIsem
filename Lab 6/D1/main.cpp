#include <fstream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct map {
private:

    vector<list<pair<string, string>>> a[1000];

    static int hash(const string& x) {
        int h = 0;
        for (char i : x) {
            h += i;
        }
        if (x.length() > 1) {
            h *= x[1];
        }
        return h % 1000;
    }

public:
    void push(const string& key, const string& x) {
        int index = hash(key);
        int index2 = hash(x);
        if (a[index].empty()) {
            a[index].resize(1000);
        }
        for (const auto& i : a[index][index2]) {
            if (i.first == key && i.second == x) {
                return;
            }
        }
        a[index][index2].push_back({key, x});
    }

    void erase(const string& key, const string& x) {
        int index = hash(key);
        int index2 = hash(x);
        if (a[index].empty()) {
            return;
        }
        for (auto i = a[index][index2].begin(); i != a[index][index2].end(); ++i) {
            if (i->first == key && i->second == x) {
                a[index][index2].erase(i);
                return;
            }
        }
    }

    void eraseAll(const string& key) {
        int index = hash(key);
        if (a[index].empty()) {
            return;
        }
        for (int i = 0; i < 1000; ++i) {
            for (auto j = a[index][i].begin(); j != a[index][i].end(); ++j) {
                if (j->first == key) {
                    auto k = next(j, 1);
                    a[index][i].erase(j);
                    j = next(k, -1);
                }
            }
        }
    }

    string get(const string& key) {
        int index = hash(key);
        if (a[index].empty()) {
            return "0";
        }
        string ans;
        int k = 0;
        for (int i = 0; i < 1000; ++i) {
            for (auto j = a[index][i].begin(); j != a[index][i].end(); ++j) {
                if (j->first == key) {
                    k++;
                    ans += j->second + " ";
                }
            }
        }
        ans = to_string(k) + " " + ans;
        return ans;
    }

};

int main() {
    ifstream fin("multimap.in");
    ofstream fout("multimap.out");

    string command;
    string key, x;
    map a;
    while (fin >> command) {
        if (command == "put") {
            fin >> key >> x;
            a.push(key, x);
            continue;
        }
        if (command == "delete") {
            fin >> key >> x;
            a.erase(key, x);
            continue;
        }
        if (command == "deleteall") {
            fin >> key;
            a.eraseAll(key);
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
