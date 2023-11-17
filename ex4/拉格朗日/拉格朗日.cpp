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

int mod_sub(int x, int y, int mod) {
	int result = x - y;
	while (result < 0) {
		result += mod;
	}
	return result % mod;
}

int mod_mult(int x, int y, int mod) {
	while (x < 0 || y < 0) {
		x += mod;
		y += mod;
	}
	x %= mod;
	y %= mod;
	int sum = 0;
	while (x != 0) {
		if (x & 1) {
			sum += y;
			sum %= mod;
		}
		y *= 2;
		x /= 2;
	}
	return sum;
}

int main() {
	int p = 0, m = 0, * y, ** a, ** z, ** A;
	int i = 0, j = 0, t = 0;
	cin >> p >> m;
	y = new int[m + 3];
	a = new int* [m + 3];
	z = new int* [m + 3];
	A = new int* [m + 2];
	for (i = 1; i <= m + 1; i++) {
		a[i] = new int[m + 2];
	}
	for (i = 1; i <= m + 1; i++) {
		cin >> y[i];
	}
	for (i = 1; i <= m + 1; i++) {
		for (j = 0; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	for (i = 1; i <= m + 1; i++) {
		z[i] = new int[m + 2];
	}
	for (i = 1; i <= m + 1; i++) {
		z[i][0] = 1;
		for (j = 1; j <= m; j++) {
			z[i][j] = 0;
		}
	}
	for (i = 1; i <= m + 1; i++) {
		int c = 0;
		for (t = 1; t <= m + 1; t++) {
			int k = mod_sub(y[i], y[t], p);
			k = mod_pow(k, p - 2, p);//k=1/k mod p
			int q = mod_mult(-y[t], k, p);
			if (t != i) {
				for (j = c; j >= 0; j--) {
					z[i][j + 1] = mod_mult(z[i][j], k, p) + mod_mult(z[i][j + 1], q, p);
					z[i][j + 1] %= p;
				}
				z[i][0] = mod_mult(z[i][0], q, p);
				c++;
			}
		}

	}	
	for (i = 0; i <= m; i++) {
		A[i] = new int[m + 2];
	}
	for (i = 0; i <= m; i++) {
		for (j = 0; j <= m; j++) {
			A[i][j] = 0;
		}
	}
	for (j = 1; j <= m + 1; j++) {
		for (i = 0; i <= m; i++) {
			for (t = 0; t <= m; t++) {
				A[i][t] += mod_mult(a[j][i], z[j][t], p);
				A[i][t] %= p;
			}
		}
	}
	for (i = 0; i <= m; i++) {
		for (j = 0; j <= m; j++) {
			cout << A[i][j] << " ";
			if (j == m) {
				cout << endl;
			}
		}
	}
	delete[] y;
	for (i = 0; i <= m + 2; i++) {
		delete[] a[i];
		delete[] z[i];
	}
	delete[] a;
	delete[] z;

	for (i = 0; i <= m + 1; i++) {
		delete[] A[i];
	}
	delete[] A;
	return 0;
}