#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<string>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

string ins;
int N, K;
map<string, int> str;
vector<int> num;

void init() {
    num.clear();
    ins.clear();
    str = {};
}

void solve() {
    int len = N / 4;

    for (int i = 0; i < 4; i++) {
        string temp = ins.substr(len * i, len);
        str[temp] = 1;
    }
}

void rotate() {
    int len = N;
    string temp = ins + ins;
    ins = temp.substr(len - 1, len);
}

void trans() {
    for (auto temp : str) {
        int len = N / 4;
        int deci = 0;
        int sum = 0;

        for (int i = 0; i < len; i++) {
            if (temp.first[i] >= 'A') {
                deci = temp.first[i] - 'A' + 10;
            }
            else {
                deci = temp.first[i] - '0';
            }

            for (int j = i; j < len - 1; j++) {
                deci = deci * 16;
            }
            sum += deci;
        }
        num.push_back(sum);
    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++) {

        init();
        cin >> N >> K;
        cin >> ins;

        for (int i = 0; i < N / 4; i++) {
            solve();
            rotate();
        }
        trans();

        int ind = num.size();
        int result = num[ind - K];
        cout << "#" << tc << " " << result << '\n';
    }

    return 0;
}