#include<iostream>
using namespace std;

int mod_pow(int x, int e, int n) {
	int result = 1;
	while (e > 0) {
		if (e % 2 == 1) {
			result = (result * x) % n;
		}
		x = (x * x) % n;
		e = e / 2;
	}
	return result;
}

int main() {
	int g, q, a, k, r;
	cin >> g >> q >> a >> k >> r;
	int p = 2 * q + 1;
	int v = mod_pow(g, q - a, p);
	int message = mod_pow(g, k, p);
	int y = (k + a * r) % q;
	cout << v << " " << message << " " << y;
	return 0;
}