#include <fstream>

using namespace std;

int main() {
	ifstream in("aplusb.in");
	ofstream out("aplusb.out");
	
	int a, b;
	in >> a >> b;
	out << a + b;
	
	in.close();
	out.close();
	return 0;
}
