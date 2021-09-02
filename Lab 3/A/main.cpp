#include <fstream>

using namespace std;

int main() {
	ifstream fin("isheap.in");
	ofstream fout("isheap.out");
	
	int n;
	fin >> n;
	int a[n + 1];
	for (int i = 1; i <= n; i++) {
		fin >> a[i];
	}
	
	bool fl = true;
	for (int i = 1; i <= n; i++) {
		if (2 * i <= n && a[i] > a[2 * i]) {
			fl = false;
			break;
		}
		if(2 * i + 1 <= n && a[i] > a[2 * i + 1]) {
			fl = false;
			break;
		}
	}
	
	fl ? fout << "YES" : fout << "NO";
	
	fin.close();
	fout.close();
	return 0;
}
