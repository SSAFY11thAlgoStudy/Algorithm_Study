#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<vector>
#include<limits.h>
#include<algorithm>
#include<cstring>
#define MAX INT_MAX

using namespace std;

// 최대 depth = n-1 (연산자 수)
int t, n, min_ans, max_ans;

vector<int>nums;

// +, -, *, /
int opers[4];

int path_opers[13];

void init() {
    min_ans = MAX;
    max_ans = -1 * MAX;
    nums.clear();
    memset(opers, 0, sizeof(opers));
    memset(path_opers, 0, sizeof(path_opers));
}

void input() {

    cin >> n;
    int num, oper;
    for (int i = 0; i < 4; i++) {
        cin >> oper;
        opers[i] = oper;
    }

    for (int i = 0; i < n; i++) {
        cin >> num;
        nums.push_back(num);
    }

}

int getSum() {
    int sum = nums[0];
    for (int i = 0; i < n - 1; i++) {
        int now_oper = path_opers[i];
        //cout << sum << " ";
        if (now_oper == 0) {
            sum += nums[i + 1];
        }
        else if (now_oper == 1) {
            sum -= nums[i + 1];
        }
        else if (now_oper == 2) {
            sum *= nums[i + 1];
        }
        else {
            sum /= nums[i + 1];
        }

    }
    return sum;
}

void combOpers(int depth) {

    if (depth == n - 1) {

        // 합 구하기 
        int sum = getSum();
        max_ans = max(max_ans, sum);
        min_ans = min(min_ans, sum);
        //cout << sum << "\n";
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (opers[i] > 0) {
            opers[i] -= 1;
            path_opers[depth] = i;
            combOpers(depth + 1);
            opers[i] += 1;
        }
    }

}


int main() {
    //freopen("input.txt", "r", stdin);
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        init();
        input();
        combOpers(0);
        cout << "#" << tc << " " << max_ans - min_ans << "\n";
    }

    return 0;
}