#include <iostream>

using namespace std;

double sum(double x, double y) {
	__asm {
		fld x
		fmul st(0), st(0)
		fld y
		fmul st(0), st(0)
		fadd st(0), st(1)
		fsqrt
	}
}

int main() {
	cout << sum(3, 4) << endl;
	return 0;
}