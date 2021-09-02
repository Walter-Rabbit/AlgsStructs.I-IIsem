#include <fstream>
 
using namespace std;
 
struct queue {
    long long queue[1000000];
 
    int tail = 1, head = 1;
 
    void enqueue(long long x) {
        queue[tail] = x;
        tail++;
    }
 
    long long dequeue() {
        long long x = queue[head];
        head++;
        return x;
    }
};
 
int main() {
    ifstream fin("queue.in");
    ofstream fout("queue.out");
 
    int n;
    fin >> n;
    queue a;
    for (int i = 0; i < n; i++) {
        char command;
        long long x;
        fin >> command;
        if (command == '+') {
            fin >> x;
            a.enqueue(x);
            continue;
        }
        if (command == '-') {
            fout << a.dequeue() << "\n";
            continue;
        }
    }
 
    fin.close();
    fout.close();
    return 0;
}
