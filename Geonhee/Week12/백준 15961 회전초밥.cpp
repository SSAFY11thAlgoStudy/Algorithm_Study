#include <iostream>
#include <algorithm>
using namespace std;

int n, d, k, c;
int sushi[3000001];
int dat[3004];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> d >> k >> c;
    for (int i = 0; i < n; i++) {
        cin >> sushi[i];
    }
    int res = 0, cnt = 0;
    int st = 0;
    int en = k - 1;
    //처음 4개 넣고 최대값 비교해주기
    for (int i = 0; i < k; i++) {
        if (!dat[sushi[i]]) {
            cnt++;
        }
        dat[sushi[i]]++;
    }
    //쿠폰 확인
    if (!dat[c]) res = max(res, cnt + 1);
    else res = max(res, cnt);

    while (true) {
        //0~3 -> 1~4로 탐색해야하기 때문에
        //dat배열의 sushi[st]값 빼주기
        // % n은 n을 넘어가도 회전초밥이므로 n번째 초밥부터 k개까지 탐색 하기 위함
        // 가장 왼쪽 초밥 없애주기
        dat[sushi[st]]--;
        if (!dat[sushi[st % n]]) cnt--;
        st++;
        //가장 왼쪽 초밥이 마지막에 오면 끝
        if (st == n) break;

        //오른쪽으로 한칸씩 이동
        en++;
        //새로운 초밥이면 cnt++
        if (!dat[sushi[en % n]]) cnt++;
        dat[sushi[en % n]]++;

        if (!dat[c]) res = max(res, cnt + 1);
        else res = max(res, cnt);
    }
    cout << res;
    return 0;
}