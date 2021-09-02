#include <fstream>

using namespace std;

struct stack {
    int stack[1000000];
    int size = 0;

    int pop() {
        size--;
        return stack[size + 1];
    }

    void push(int x) {
        size++;
        stack[size] = x;
    }
};

int main() {
    ifstream fin("stack.in");
    ofstream fout("stack.out");

    stack a;
    int m;
    fin >> m;
    for (int i = 0; i < m; i++) {
        char command;
        int x;
        fin >> command;
        if (command == '-') {
            fout << a.pop() << "\n";
            continue;
        }
        if (command == '+') {
            fin >> x;
            a.push(x);
            continue;
        }
    }

    fin.close();
    fout.close();
    return 0;
}
