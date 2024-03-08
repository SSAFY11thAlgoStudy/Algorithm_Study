#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;

int N; // 3 �� N �� 12
int maxi = -21e8, mini = 21e8; // �ʱⰪ ����
char sign_S[4] = { '+', '-','*','/' };
int num[12];
int signCount[4]; // �� �������� ��� Ƚ��
vector<char> path;

void input() {
    cin >> N;
    // ������ ����
    for (int i = 0; i < 4; i++) {
        cin >> signCount[i];
    }
    // ���� ����
    for (int i = 0; i < N; i++) {
        cin >> num[i];
    }
}

void backtracking(int node, int sum) {
    int sum_s = sum;
    if (node == N) {
        // �ִ� �� �ּڰ� ����
        if (maxi < sum) {
            maxi = sum;
        }
        if (mini > sum) {
            mini = sum;
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (signCount[i] > 0) { // ��� ������ ���������� Ȯ��
            signCount[i]--; // �ش� ������ ���
            if (sign_S[i] == '+') { // �����ڰ� '+'�� ���
                sum += num[node];
            }
            else if (sign_S[i] == '-') { // �����ڰ� '-'�� ���
                sum -= num[node];
            }
            else if (sign_S[i] == '*') { // �����ڰ� '*'�� ���
                sum *= num[node];
            }
            else if (sign_S[i] == '/') { // �����ڰ� '/'�� ���
                sum /= num[node];
            }

            path.push_back(sign_S[i]); // ��ο� ������ �߰�
            backtracking(node + 1, sum); // ���� ���� �̵�
            path.pop_back(); // ��Ʈ��ŷ
            signCount[i]++; // ������ ��� Ƚ�� ����
            sum = sum_s; // ����� ����
        }
    }

}

int main() {
    freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        maxi = -21e8, mini = 21e8; // �ʱⰪ ����
        input();
        int sum = num[0];
        backtracking(1, sum);
        cout << "#" << tc << " " << maxi - mini << endl;
    }
}
