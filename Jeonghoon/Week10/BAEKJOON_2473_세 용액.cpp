#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;
vector<long long int> med;

long long int n_left, n_mid, n_right;
long long int result = 4100000000;

void solve() {

    for (int i = 0; i < med.size() - 2; i++) {
        int ind_l = i + 1;
        int ind_r = med.size() - 1;

        while (ind_l < ind_r) {

            long long int sum = med[i] + med[ind_l] + med[ind_r];

            if (abs(sum) < abs(result)) {
                result = sum;
                n_left = med[i];
                n_mid = med[ind_l];
                n_right = med[ind_r];
                if (sum == 0) {
                    return;
                }
            }

            if (sum < 0) {
                ind_l++;
            }
            else {
                ind_r--;
            }

        }
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    cin >> N;

    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        med.push_back(temp);
    }

    sort(med.begin(), med.end());

    solve();

    cout << n_left << " " << n_mid << " " << n_right;

    return 0;
}