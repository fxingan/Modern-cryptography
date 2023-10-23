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

int find(int x, int y, int mod) {
	if (y == 1) {
		return 0;
	}
	int a = 1;
	int result = x % mod;
	while (result != y) {
		result = (result * x) % mod;
		a++;// 如果 a 增长到 mod 仍未找到 y，那么 y 不可能是 x^a % mod
		if (a == mod) {
			return -1; // 表示没有找到
		}
	}
	return a;
}

int verify(int g, int q, int p, int m, int x, int y) {
	int z1 = mod_pow(q, x, p);
	int z2 = mod_pow(x, y, p);
	int z = mod_pow(g, m, p);
	if (z1 * z2 % p == z) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}

int main() {
	int p, g, q, m, x, y;
	cout << "Please input:" << endl;
	cin >> p >> g >> q >> m >> x >> y;
	int a = find(g, q, p);
	int r = find(g, x, p);
	cout << "Output:" << endl;
	verify(g, q, p, m, x, y);
	cout << a << endl << r;
	return 0;
}