#include <fstream>
#include <string>

using namespace std;

struct queue {
private:
    unsigned short q[100100] = {0};

    int tail = 1, head = 1;

public:
    void push(unsigned short x) {
        q[tail] = x;
        tail++;
    }

    unsigned short get() {
        unsigned short x = q[head];
        head++;
        return x;
    }
};

struct tree {
private:
    struct elm {
        string key;
        int left, right, index;
    };

    int size = 0;
    int begining = 1;
    elm tree[101] = {{"", 0, 0, 0}};

public:
    void insert(string x, int id) {
        tree[0] = {"", 0, 0, 0};

        int index = begining;
        if (size == 0) {
            size++;
            tree[size].right = 0;
            tree[size].left = 0;
            tree[size].key = x;
            tree[size].index = id;
            return;
        }
        while (true) {
            int indexOfRight = tree[index].right;
            int indexOfLeft = tree[index].left;
            if (tree[index].key < x) {
                if (indexOfRight == 0) {
                    size++;
                    tree[index].right = size;
                    tree[size].key = x;
                    tree[size].index = id;
                    break;
                }
                index = indexOfRight;
            }
            else if (tree[index].key > x) {
                if (indexOfLeft == 0) {
                    size++;
                    tree[index].left = size;
                    tree[size].key = x;
                    tree[size].index = id;
                    break;
                }
                index = indexOfLeft;
            }
            else if (tree[index].key == x) {
                break;
            }
        }
    }

    int find(string x) {
        tree[0] = {"", 0, 0, 0};
        int index = begining;
        while (true) {
            if (index == 0 || size == 0) {
                return 0;
            }
            else if (tree[index].key == x) {
                return tree[index].index;
            }
            else if (tree[index].key < x) {
                index = tree[index].right;
            }
            else if (tree[index].key > x) {
                index = tree[index].left;
            }
        }
    }

};

class quack {
private:
    int reg[26] = {0};
    queue data;
    tree labels;

public:
    int sizeOfComands = 0;
    string comands[100100];

    void push(unsigned short x) {
        data.push(x);
    }

    int getReg(char c) {
        return reg[c - 'a'];
    }

    int get() {
        return data.get();
    }

    void plus() {
        unsigned short x = data.get();
        unsigned short y = data.get();
        data.push(x + y);
    }

    void minus() {
        unsigned short x = data.get();
        unsigned short y = data.get();
        data.push(x - y);
    }

    void multi() {
        unsigned short x = data.get();
        unsigned short y = data.get();
        data.push(x * y);
    }

    void divide() {
        unsigned short x = data.get();
        unsigned short y = data.get();
        if (y == 0) {
            data.push(0);
        }
        else {
            data.push(x / y);
        }
    }

    void mod() {
        unsigned short x = data.get();
        unsigned short y = data.get();
        if (y == 0) {
            data.push(0);
        }
        else {
            data.push(x % y);
        }
    }

    void toReg(char c) {
        unsigned short x = data.get();
        reg[c - 'a'] = x;
    }

    void fromReg(char c) {
        unsigned short x = reg[c - 'a'];
        data.push(x);
    }

    char ascii() {
        return (char) (data.get() % 256);
    }

    char asciiReg(char c) {
        return (char) (reg[c - 'a'] % 256);
    }

    void pushLabel(const string& st, int i) {
        string copy = "";
        for (int j = 1; j < st.length(); j++) {
            copy += st[j];
        }
        labels.insert(copy, i);
    }

    int findLabel(const string& st) {
        string copy = "";
        for (int j = 1; j < st.length(); j++) {
            copy += st[j];
        }
        return labels.find(copy);
    }

    int findLabelZero(const string& st) {
        if (reg[st[1] - 'a']  == 0) {
            string copy = "";
            for (int j = 2; j < st.length(); j++) {
                copy += st[j];
            }
            return labels.find(copy);
        }
        else {
            return 0;
        }
    }

    int findLabelEqual(const string& st) {
        if (reg[st[1] - 'a']  == reg[st[2] - 'a']) {
            string copy = "";
            for (int j = 3; j < st.length(); j++) {
                copy += st[j];
            }
            return labels.find(copy);
        }
        else {
            return 0;
        }
    }

    int findLabelGreat(const string& st) {
        if (reg[st[1] - 'a']  > reg[st[2] - 'a']) {
            string copy = "";
            for (int j = 3; j < st.length(); j++) {
                copy += st[j];
            }
            return labels.find(copy);
        }
        else {
            return 0;
        }
    }
};

int main() {
    ifstream fin("quack.in");
    ofstream fout("quack.out");

    string input;
    quack a;

    while (fin >> input && input != "Q") {
        a.sizeOfComands++;
        a.comands[a.sizeOfComands] = input;
        if (input[0] == ':') {
            a.pushLabel(input, a.sizeOfComands);
            continue;
        }
    }

    for (int i = 1; i <= a.sizeOfComands; i++) {
        char c0 = a.comands[i][0], c1 = '-';
        if (a.comands[i].length() > 1) {
            c1 = a.comands[i][1];
        }

        if (c0 >= '0' && c0 <= '9' || c0 == '-' && c1 != '-') {
            a.push(stoi(a.comands[i]));
            continue;
        }

        if (c0 == '+') {
            a.plus();
            continue;
        }

        if (c0 == '-') {
            a.minus();
            continue;
        }

        if (c0 == '*') {
            a.multi();
            continue;
        }

        if (c0 == '/') {
            a.divide();
            continue;
        }

        if (c0 == '%') {
            a.mod();
            continue;
        }

        if (c0 == '>') {
            a.toReg(c1);
            continue;
        }

        if (c0 == '<') {
            a.fromReg(c1);
            continue;
        }

        if (c0 == 'P' && c1 == '-') {
            fout << a.get() << "\n";
            continue;
        }

        if (c0 == 'P' && c1 != '-') {
            fout << a.getReg(c1) << "\n";
            continue;
        }

        if (c0 == 'C' && c1 == '-') {
            fout << a.ascii();
            continue;
        }

        if (c0 == 'C' && c1 != '-') {
            fout << a.asciiReg(c1);
            continue;
        }

        if (c0 == ':') {
            continue;
        }

        if (c0 == 'J') {
            i = a.findLabel(a.comands[i]);
            continue;
        }

        if (c0 == 'Z') {
            int j = a.findLabelZero(a.comands[i]);
            if (j != 0) {
                i = j;
            }
            continue;
        }

        if (c0 == 'E') {
            int j = a.findLabelEqual(a.comands[i]);
            if (j != 0) {
                i = j;
            }
            continue;
        }

        if (c0 == 'G') {
            int j = a.findLabelGreat(a.comands[i]);
            if (j != 0) {
                i = j;
            }
            continue;
        }

        if (c0 == 'Q') {
            break;
        }
    }

    fin.close();
    fout.close();
    return 0;
}