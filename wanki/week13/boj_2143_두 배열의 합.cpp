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

    // A �迭 �Է� �� �ι迭 ����
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

    // B �迭 �Է� �� �ι迭 ����
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

    // �迭 B_extend�� �����մϴ�.
    sort(B_extend.begin(), B_extend.end());

    // A_extend�� �� �տ� ����, T���� �� ���� �� ���� B_extend�� �ִ��� Ȯ���ϰ�, �� ������ ī��Ʈ�մϴ�.

    for (int sum : A_extend) {
        int target = T - sum;
        auto lower = lower_bound(B_extend.begin(), B_extend.end(), target);
        auto upper = upper_bound(B_extend.begin(), B_extend.end(), target);
        cnt += (upper - lower);
    }

    // ��� ���
    cout << cnt << endl;

    return 0;
}
