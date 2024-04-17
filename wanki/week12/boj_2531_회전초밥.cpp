#include <iostream>
#include <algorithm>
#include<vector>
using namespace std;
int table[3000000];
int rawFish[3001];
int N, d, k, c;
int result = 0, cnt = 0;

void input() {
    cin >> N >> d >> k >> c;
    for (int i = 0; i < N; i++) {
        cin >> table[i];
        //table.push_back(num);
    }
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    input();

    int left = 0, right = k - 1;
    for (int i = 0; i < k; i++) {
        rawFish[table[i]]++;
        if (rawFish[table[i]] == 1)
            cnt++;
    }
    rawFish[c]++;
    if (rawFish[c] == 1) cnt++;

    while (left < N) {
        result = max(result, cnt); // 비교
        if (rawFish[table[left]]-- == 1) cnt--; // 전 초밥의 번호를 확인해서 미중복 개수를 줄임
        left++;
        right = (right + 1) % N;
        if (rawFish[table[right]]++ == 0) cnt++; // 다음 초밥의 번호를 확인해서 미중복일 경우 개수를 늘림
    }
    cout << result;
    return 0;
}