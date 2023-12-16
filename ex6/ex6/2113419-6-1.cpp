#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 生成从nums中选取n个元素的组合
void gen_combinations(vector<int>& nums, int m, int n, vector<int>& group, vector<vector<int>>& res) {
    if (n == 0) {
        res.push_back(group);
        return;
    }
    for (int i = m; i <= nums.size() - n; ++i) {
        group.push_back(nums[i]);
        gen_combinations(nums, i + 1, n - 1, group, res);
        group.pop_back();
    }
}

// 根据alpha判断resi是否为有效证据
int isProof(vector<int>& resi, vector<vector<int>>& alpha) {
    vector<vector<int>> resicopy = {
        {resi[0], resi[1]},
        {resi[1], resi[2]},
        {resi[0], resi[2], resi[3]},
        {resi[0], resi[2]},
        {resi[1]},
        {resi[0], resi[3]}
    };

    for (auto& vec : resicopy) {
        sort(vec.begin(), vec.end());
    }
    for (auto& temp : alpha) {
        sort(temp.begin(), temp.end());
    }
    int flagsum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < alpha.size(); j++) {
            if (includes(resicopy[i].begin(), resicopy[i].end(), alpha[j].begin(), alpha[j].end())) {
                flagsum++;
                break;
            }
        }
    }
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < alpha.size(); j++) {
            if (includes(resicopy[i].begin(), resicopy[i].end(), alpha[j].begin(), alpha[j].end())) {
                return 0;
            }
        }
    }
    return (flagsum == 3) ? 1 : 0;
}

int main() {
    int n, x;
    cin >> n >> x;

    vector<vector<int>> alpha(x);
    vector<vector<int>> res;
    vector<int> group;
    vector<int> nums;

    // 读取 alpha 的输入
    for (int i = 0; i < x; ++i) {
        int num;
        while (cin >> num) {
            alpha[i].push_back(num);
            if (cin.peek() == '\n') {
                cin.ignore();
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        nums.push_back(i + 1);
    }
    gen_combinations(nums, 0, n, group, res);

    // 检查每个组合和排列以确定是否为证据
    for (int i = 0; i < res.size(); i++) {
        if (isProof(res[i], alpha) == 1) {
            for (int j = 0; j < res[i].size(); j++) {
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
        while (next_permutation(res[i].begin(), res[i].end())) {
            if (isProof(res[i], alpha) == 1) {
                for (int j = 0; j < res[i].size(); j++) {
                    cout << res[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
    cout << "#" << endl;
    return 0;
}