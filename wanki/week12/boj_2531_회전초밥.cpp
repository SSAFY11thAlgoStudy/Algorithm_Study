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
        result = max(result, cnt); // ��
        if (rawFish[table[left]]-- == 1) cnt--; // �� �ʹ��� ��ȣ�� Ȯ���ؼ� ���ߺ� ������ ����
        left++;
        right = (right + 1) % N;
        if (rawFish[table[right]]++ == 0) cnt++; // ���� �ʹ��� ��ȣ�� Ȯ���ؼ� ���ߺ��� ��� ������ �ø�
    }
    cout << result;
    return 0;
}