#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

double A;
int n;

double buildUp(double A, double x) {
    double C = 2 * x - A + 2;
    return C;
}

double binarySearch(double left, double right) {
    double middle;
    while (right - left > 0.000001) {
        middle = (left + right) / 2.0;
        int fl = 0;
	    double C;
	    double x1 = A, x2 = middle;
		cout << x1 << " " << x2 << " ";
	    for (int i = 2; i < n; i++) {
	        C = buildUp(x1, x2);
	        if (C < 0) {
	        	fl = 2;
	        	break;
			}
			if (C == 0) {
                fl++;
            }
            cout << C << " ";
			x1 = x2;
			x2 = C;
	    }
		cout << "\n";
        if (fl <= 1 ) {
            right = middle;
        }
        else {
            left = middle;
        }
    }
    return right;
}


int main() {
    ifstream fin("garland.in");
    ofstream fout("garland.out");
    cout.precision(8);

    cin >> n >> A;    
	double x = binarySearch(0, A);
    double B, x1 = A, x2 = x;
    for (int i = 2; i < n; i++) {
        B = buildUp(x1, x2);
        x1 = x2;
        x2 = B;
    }
    B = round(B * 100.0) / 100.0;
    cout << B;
    
    fin.close();
    fout.close();
    return 0;
}
//692 532.81
