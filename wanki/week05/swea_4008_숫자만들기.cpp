#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;

int N; // 3 ≤ N ≤ 12
int maxi = -21e8, mini = 21e8; // 초기값 수정
char sign_S[4] = { '+', '-','*','/' };
int num[12];
int signCount[4]; // 각 연산자의 사용 횟수
vector<char> path;

void input() {
    cin >> N;
    // 연산자 저장
    for (int i = 0; i < 4; i++) {
        cin >> signCount[i];
    }
    // 숫자 저장
    for (int i = 0; i < N; i++) {
        cin >> num[i];
    }
}

void backtracking(int node, int sum) {
    int sum_s = sum;
    if (node == N) {
        // 최댓값 및 최솟값 갱신
        if (maxi < sum) {
            maxi = sum;
        }
        if (mini > sum) {
            mini = sum;
        }
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (signCount[i] > 0) { // 사용 가능한 연산자인지 확인
            signCount[i]--; // 해당 연산자 사용
            if (sign_S[i] == '+') { // 연산자가 '+'일 경우
                sum += num[node];
            }
            else if (sign_S[i] == '-') { // 연산자가 '-'일 경우
                sum -= num[node];
            }
            else if (sign_S[i] == '*') { // 연산자가 '*'일 경우
                sum *= num[node];
            }
            else if (sign_S[i] == '/') { // 연산자가 '/'일 경우
                sum /= num[node];
            }

            path.push_back(sign_S[i]); // 경로에 연산자 추가
            backtracking(node + 1, sum); // 다음 노드로 이동
            path.pop_back(); // 백트래킹
            signCount[i]++; // 연산자 사용 횟수 복구
            sum = sum_s; // 결과값 복구
        }
    }

}

int main() {
    freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        maxi = -21e8, mini = 21e8; // 초기값 수정
        input();
        int sum = num[0];
        backtracking(1, sum);
        cout << "#" << tc << " " << maxi - mini << endl;
    }
}
