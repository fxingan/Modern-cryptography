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

int main() {
	int g, q, v, r1, y1, r2, y2;
	cin >> g >> q >> v >> r1 >> y1 >> r2 >> y2;
	int p = 2 * q + 1;
	int temp1 = mod_pow(g, y1, p);
	int temp2 = mod_pow(v, r1, p);
	int k = find(g, (temp1 * temp2) % p, p);
	while ((y1 - k) % r1 != 0) {
		y1 += q;
	}
	int a = (y1 - k) / r1;
	cout << a;
	return 0;
}