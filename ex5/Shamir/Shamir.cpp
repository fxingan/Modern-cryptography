#include<iostream>
#include <vector>
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

int mod_inv(int x, int y, int p) {
	y = mod_pow(y, p - 2, p); 
	int z = mod_mult(x, y, p); 
	return z;
}

bool solve(int t, int p, vector<vector<int>>& A, vector<int>& a) {
	for (int i = 1; i <= t; i++) {
		int m;
		for (m = i; m <= t; m++) {
			if (A[m][i] != 0) // 找到第 i 列不为零的元素
				break;
		}
		if (m <= t) {
			for (int j = i; j <= t + 1; j++) {
				swap(A[i][j], A[m][j]); // 交换第 i 行和第 k 行所有元素
			}
			double c;
			for (int j = i + 1; j <= t; j++) {
				c = mod_inv(p - A[j][i], A[i][i], p);
				for (m = i; m <= t + 1; m++) {
					A[j][m] += mod_mult(c, A[i][m], p); // 第 i 行 a 倍加到第 j 行
					A[j][m] %= p;
				}
			}
		}
		else {
			cout << "线性方程组无解" << endl;
			return false;
		}
	}
	for (int i = t; i >= 1; i--) {
		a[i] = A[i][t + 1];
		for (int j = t; j > i; j--) {
			a[i] = mod_sub(a[i], mod_mult(a[j], A[i][j], p), p);
		}
		a[i] = mod_inv(a[i], A[i][i], p);
	}
	return true;
}

int qiuy(vector<int> a, int x, int t, int p) {
	int y = a[1];
	for (int i = 2; i <= t; i++) {
		y += a[i] * mod_pow(x, i - 1, p);
		y %= p;
	}
	return y;
}

int main() {
	int t, w, p;
	cin >> t >> w >> p;
	vector<int> a(t + 2);
	vector<int> x(t + 3);
	vector<int> y(t + 3);
	for (int i = 1; i <= t; i++) {
		cin >> x[i] >> y[i];
	}
	cin >> x[t + 1];
	vector<vector<int>> A(t + 2, vector<int>(t + 3));
	for (int i = 1; i <= t; i++) {
		for (int j = 1; j <= t; j++) {
			A[i][j] = mod_pow(x[i], j - 1, p);
		}
		A[i][t + 1] = y[i];
	}
	vector<int> result(t + 1);
	if (!solve(t, p, A, result)) {
		return -1;
	}
	cout << result[1] << endl;
	int y_1 = qiuy(result, x[t + 1], t, p);
	cout << y_1 << endl;
	return 0;
}