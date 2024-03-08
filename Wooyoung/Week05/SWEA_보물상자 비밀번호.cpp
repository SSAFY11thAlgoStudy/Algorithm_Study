#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<iostream>
#include <set>
#include<vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
using namespace std;

int t, n, k;
int ans, cnt;

void init() {
    ans = 0;
    cnt = 1;
}

void func(deque<int>& dq) {
    // len = n
    // rot È½¼ö = (n / 4) - 1
    int each_len = n / 4;

    set<int, greater<>>nums;

    for (int i = 0; i < each_len; i++) {

        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += dq[j] * pow(16, each_len - 1 - (j % each_len));
            if ((j + 1) % (each_len) == 0) {
                nums.insert(sum);
                //cout << sum << "\n";
                sum = 0;
            }
        }

        dq.push_front(dq.back());
        dq.pop_back();

    }

    for (auto p : nums) {
        if (cnt == k) {
            ans = p;
            break;
        }
        cnt++;
    }

}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    cin >> t;
    for (int i = 1; i <= t; i++) {
        init();
        cin >> n >> k;
        string s;
        cin >> s;
        deque<int>dq;
        int s_len = s.length();
        for (int j = 0; j < s_len; j++) {
            if (s[j] >= '0' && s[j] <= '9') {
                dq.push_back(s[j] - '0');
            }
            else {
                dq.push_back(s[j] - 'A' + 10);
            }
        }
        func(dq);
        //sort(nums.begin(), nums.end());
        cout << "#" << i << " " << ans << "\n";
    }
    return 0;
}