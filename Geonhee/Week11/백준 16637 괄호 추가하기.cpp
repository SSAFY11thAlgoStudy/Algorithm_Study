#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;
string s;
vector<int> num;
vector<char> oper_str;
int res = -987654321;
// 연산을 처리하기 위한 함수
int oper(char a, int b, int c) {
    if (a == '+') return b + c;
    if (a == '-') return b - c;
    if (a == '*') return b * c;
}

void go(int cnt, int x) {
    //모든 숫자를 다 계산 했으면
    if (cnt == num.size() - 1) {
        // 최대 값 비교
        res = max(res, x);
        return;
    }
    // 인덱스 +1 해주고 현재 값과 다음 값 계산
    go(cnt + 1, oper(oper_str[cnt], x, num[cnt + 1]));
    // 3개 숫자 중 뒤에 두개를 먼저 연산하는 경우를 처리 하는 경우
    // +2했을 때 전체 숫자 개수 범위보다 작거나 같아야함
    if (cnt + 2 <= num.size() - 1) {
        // 3개중 뒤에 2개 숫자를 먼저 계산 하고
        int temp = oper(oper_str[cnt + 1], num[cnt + 1], num[cnt + 2]);
        // 인덱스 +2 해주고 연산 이어가기
        go(cnt + 2, oper(oper_str[cnt], x, temp));
    }
    return;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> s;
    // 숫자와 연산기호 따로 나눠서 받아주기
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) num.push_back(s[i] - '0');
        else oper_str.push_back(s[i]);
    }
    //초기 값 기초로 탐색
    go(0, num[0]);
    cout << res << '\n';
    return 0;
}