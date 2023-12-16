#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

// 生成 CNF 合取式
set<pair<int, int>>generateCNF(const vector<set<int>>& gamma_0) {
    set<pair<int, int>> combinations;

    for (const auto& subset : gamma_0) {
        for (int a : subset) {
            for (int b : subset) {
                if (a < b && subset.count(a) && subset.count(b)) {
                    combinations.insert({ a, b });
                }
            }
        }
    }
    set<pair<int, int>> toBeRemoved;
    for (const auto& pair : combinations) {
        int first = pair.first;
        int second = pair.second;
        int found = 0;
        for (const auto& subset : gamma_0) {
            bool foundFirst = false;
            bool foundSecond = false;
            if (subset.find(first) != subset.end()) {
                foundFirst = true;
            }
            if (subset.find(second) != subset.end()) {
                foundSecond = true;
            }
            // 发现该数对
            if (foundFirst && foundSecond) {
                found++;
            }
        }
        if (found!=1) {
            toBeRemoved.insert(pair);
        }
    }
    for (const auto& pair : toBeRemoved) {
        combinations.erase(pair);
    }    
    return combinations;
}

// 生成分发规则
void generateDisRule(const set<pair<int, int>>& CNF, const int n) {
    vector<set<int>> x(n);
    int k = 0;
    for (const auto& pair : CNF) {
        int first = pair.first;
        int second = pair.second;
        x[first - 1].insert(k + 1);
        x[second - 1].insert(k + 1);
        k++;
    }
    for (const auto& subset : x) {
        for (const auto& participant : subset) {
            cout << participant << " ";
            k++;
        }
        if (k != n - 1) {
            cout << endl;
        }
    }
    cout << "#";
}

int main() {
    int n, x;
    cin >> n >> x;

    vector<set<int>> alpha(x);

    // 读取授权子集
    int i = 0;
    while (true) {
        int participant;
        cin >> participant;
        alpha[i].insert(participant);
        if (cin.get() == '\n') {
            i++;
        }
        if (i == x) {
            break;
        }
    }
    // 基于 alpha 生成 gamma_0
    vector<int> len_c(x, 1); // 初始化 len_c 全为 1

    for (int i = 0; i < x; i++) {
        for (int m = 0; m < x; m++) {
            if (i != m && includes(alpha[m].begin(), alpha[m].end(), alpha[i].begin(), alpha[i].end())) {
                len_c[m] = 0;
            }
        }
    }
    vector<set<int>> gamma_0;

    for (int i = 0; i < x; i++) {
        if (len_c[i] != 0) {
            gamma_0.push_back(alpha[i]);
        }
    }
    int j = 0;
    // 输出 gamma_0 中的内容
    for (const auto& subset : gamma_0) {
        for (const auto& participant : subset) {
            cout << participant << " ";
            j++;
        }
        if (j != x - 1) {
            cout << endl;
        }
    }
    cout << "#" << endl;  
    set<pair<int, int>>CNF = generateCNF(gamma_0);
    for (const auto& pair : CNF) {
        cout << pair.first << " " << pair.second << endl;
    }
    cout << "#" << endl;
    generateDisRule(CNF, n);

    return 0;
}