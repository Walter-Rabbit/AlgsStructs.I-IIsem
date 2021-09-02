#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct map {
private:

    struct elm {
        string key, x;
        string prev = "0", next = "0";

        elm(const string& l1, const string& l2, const string& l3, const string& l4) {
            key = l1;
            x = l2;
            prev = l3;
            next = l4;
        }
    };

    string prevKey = "0";

    vector<elm> list[50000];

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
            if (list[index][i].key == key) {
                fl = i;
                break;
            }
        }
        if (fl == -1) {
            elm temp(key, x, prevKey, "0");
            list[index].push_back(temp);

            if (prevKey != "0") {
                int newIndex = hash(prevKey);
                for (int i = 0; i < list[newIndex].size(); i++) {
                    if (list[newIndex][i].key == prevKey) {
                        list[newIndex][i].next = key;
                        break;
                    }
                }
            }
            prevKey = key;
        }
        else {
            list[index][fl].key = key;
            list[index][fl].x = x;
        }
    }

    void erase(const string& key) {
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {

                int newIndex = hash(list[index][i].prev);
                for (int j = 0; j < list[newIndex].size(); j++) {
                    if (list[newIndex][j].key == list[index][i].prev) {
                        list[newIndex][j].next = list[index][i].next;
                    }
                }

                newIndex = hash(list[index][i].next);
                for (int j = 0; j < list[newIndex].size(); j++) {
                    if (list[newIndex][j].key == list[index][i].next) {
                        list[newIndex][j].prev = list[index][i].prev;
                    }
                }

                if (list[index][i].key == prevKey) {
                    prevKey = list[index][i].prev;
                }
                list[index].erase(list[index].begin() + i);
                break;
            }
        }
    }

    string get(const string &key) {
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {
                return list[index][i].x;
            }
        }
        return "none";
    }

    string prev(const string &key) {
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {
                if (list[index][i].prev == "0") {
                    return "none";
                }
                return get(list[index][i].prev);
            }
        }
        return "none";
    }

    string next(const string &key) {
        int index = hash(key);
        for (int i = 0; i < list[index].size(); i++) {
            if (list[index][i].key == key) {
                if (list[index][i].next == "0") {
                    return "none";
                }
                return get(list[index][i].next);
            }
        }
        return "none";
    }
};

int main() {
    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");

    vector <vector<bool>> a;

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
            fin >> key;
            a.erase(key);
            continue;
        }
        if (command == "get") {
            fin >> key;
            fout << a.get(key) << "\n";
            continue;
        }
        if (command == "prev") {
            fin >> key;
            fout << a.prev(key) << "\n";
            continue;
        }
        if (command == "next") {
            fin >> key;
            fout << a.next(key) << "\n";
            continue;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
