#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int T, N;
long long cnt = 0;
vector<int> A, A_extend;
vector<int> B, B_extend;

int main() {
    int num;

    cin >> T;

    // A 배열 입력 및 부배열 생성
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        A.push_back(num);
        A_extend.push_back(A[i]);
        int sum = A[i];
        for (int j = i - 1; j >= 0; j--) {
            sum += A[j];
            A_extend.push_back(sum);
        }
    }

    // B 배열 입력 및 부배열 생성
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        B.push_back(num);
        B_extend.push_back(B[i]);
        int sum = B[i];
        for (int j = i - 1; j >= 0; j--) {
            sum += B[j];
            B_extend.push_back(sum);
        }
    }

    // 배열 B_extend를 정렬합니다.
    sort(B_extend.begin(), B_extend.end());

    // A_extend의 각 합에 대해, T에서 그 합을 뺀 값이 B_extend에 있는지 확인하고, 그 갯수를 카운트합니다.

    for (int sum : A_extend) {
        int target = T - sum;
        auto lower = lower_bound(B_extend.begin(), B_extend.end(), target);
        auto upper = upper_bound(B_extend.begin(), B_extend.end(), target);
        cnt += (upper - lower);
    }

    // 결과 출력
    cout << cnt << endl;

    return 0;
}
