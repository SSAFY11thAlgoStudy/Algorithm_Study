#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<long long> v;
int N;
long long result[3];

// 입력을 받는 함수
void input() {
    int num;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        v.push_back(num);
    }
    sort(v.begin(), v.end());
}

// 세 용액을 선택하여 합이 0에 가장 가까운 경우를 찾는 함수
void solve() {
    //최대값이
    long long mid = 3000000001; // 최소 차이를 저장할 변수
    for (int i = 0; i < N - 2; i++) {
        int left = i + 1; // 왼쪽 포인터
        int right = N - 1; // 오른쪽 포인터
        while (left < right) {
            long long sum = v[i] + v[left] + v[right]; // 세 용액의 합
            if (abs(sum) < mid) {
                mid = abs(sum);
                result[0] = v[i];
                result[1] = v[left];
                result[2] = v[right];
            }
            if (sum < 0) { // 합이 0보다 작으면 왼쪽 포인터를 오른쪽으로 이동
                left++;
            }
            else { // 합이 0보다 크면 오른쪽 포인터를 왼쪽으로 이동
                right--;
            }
        }
    }
}

int main() {
    input();
    solve();
    for (int a : result) {
        cout << a << " ";
    }
    return 0;
}
