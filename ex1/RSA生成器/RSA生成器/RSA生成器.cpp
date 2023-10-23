#include <iostream>
#include <vector>
using namespace std;

long long int mod_pow(long long int x, long long int e, long long int n) {
    long long int result = 1;
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
    long long int n, p, q, e, t = 0, i, j = 0;
    vector<long long int> s(1000); 
    vector<long long int> z(1000);  
    cin >> n >> p >> q >> e >> s[0] >> i;
    while (1) {
        s[j + 1] = mod_pow(s[j], e, n);
        if (j < i) {
            z[j] = s[j + 1] % 2;
        }
        if (t == 0) {
            for (int k = 0; k <= j; k++) {
                if (s[k] == s[j + 1]) {
                    t = j + 1 - k;
                    break;
                }
            }
        }
        if (t != 0 && j >= i) {
            break;
        }
        j++;
    }
    cout << t << endl;
    for (j = 0; j < i; j++) {
        cout << z[j];
    }
    return 0;
}