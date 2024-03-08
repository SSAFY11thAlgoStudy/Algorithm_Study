#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<string>

using namespace std;

int N, K;
string s;
set<int, greater<int>> sets;
int n;

void input() {
    cin >> N >> K;
    cin >> s;
}

void solve() {
    n = N / 4; // n 값 초기화
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            int a = stoi(s.substr(i * n, n), nullptr, 16); // stoi 함수 수정
            sets.insert(a);
        }
        s.push_back(s[0]);
        s.erase(0, 1);
    }
}

int main() {
    //freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        int cnt = 0;
        s.clear();
        sets.clear(); // sets 초기화 추가
        input();
        solve();

        for (auto i : sets)
        {
            if (cnt == K - 1) { cout << "#" << tc << " " << i << '\n'; }
            cnt++;
        }
    }

    return 0;
}
