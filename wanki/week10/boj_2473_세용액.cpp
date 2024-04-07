#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<long long> v;
int N;
long long result[3];

// �Է��� �޴� �Լ�
void input() {
    int num;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        v.push_back(num);
    }
    sort(v.begin(), v.end());
}

// �� ����� �����Ͽ� ���� 0�� ���� ����� ��츦 ã�� �Լ�
void solve() {
    //�ִ밪��
    long long mid = 3000000001; // �ּ� ���̸� ������ ����
    for (int i = 0; i < N - 2; i++) {
        int left = i + 1; // ���� ������
        int right = N - 1; // ������ ������
        while (left < right) {
            long long sum = v[i] + v[left] + v[right]; // �� ����� ��
            if (abs(sum) < mid) {
                mid = abs(sum);
                result[0] = v[i];
                result[1] = v[left];
                result[2] = v[right];
            }
            if (sum < 0) { // ���� 0���� ������ ���� �����͸� ���������� �̵�
                left++;
            }
            else { // ���� 0���� ũ�� ������ �����͸� �������� �̵�
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
