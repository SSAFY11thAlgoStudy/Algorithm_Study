#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<cmath>

using namespace std;

int H, K, R;
//말단의 업무, 오른쪽 직원이 올린 업무, 왼쪽직원이 올린 업무
queue<int> work[2049], work_r[2049], work_l[2049];
//말단 직원 수
int node;
int result;

void input() {
	cin >> H >> K >> R;

	node = pow(2, H);

	//말단 직원에게 업무 입력
	for (int i = node; i < node * 2; i++) {
		for (int j = 0; j < K; j++) {
			int temp;
			cin >> temp;
			work[i].push(temp);
		}
	}
}

void solve() {
	//날짜
	for (int i = 1; i <= R; i++) {

		//직원 한명씩 업무 확인

		for (int j = 1; j < node * 2; j++) {

			//큐가 비어있으면 넘어가기
			if (work[j].empty() && work_r[j].empty() && work_l[j].empty()) continue;

			//말단 직원이라면 업무 하나씩 처리
			if (j >= node) {
				//왼쪽 직원 이라면
				if (j % 2 == 0) {
					//왼쪽에 넣기
					work_l[j / 2].push(work[j].front());
					work[j].pop();
				}
				//오른쪽 직원이라면
				else {
					//오른쪽에 넣기
					work_r[j / 2].push(work[j].front());
					work[j].pop();
				}
			}
			//말단 직원이 아니라면
			else {
				//사장이라면 결과값 더하기
				if (j == 1) {
					if (i % 2 == 1) {
						result += work_l[1].front();
						work_l[1].pop();
					}
					else {
						result += work_r[1].front();
						work_r[1].pop();
					}
				}
				//사장이 아니라면 홀수 일 일때
				else if (i % 2 == 1) {
					//왼쪽 직원이라면
					if (j % 2 == 0) {
						work_l[j / 2].push(work_l[j].front());
						work_l[j].pop();
					}
					else {
						work_r[j / 2].push(work_l[j].front());
						work_l[j].pop();
					}
				}
				//짝수 일 일때
				else if (i % 2 == 0) {
					//왼쪽직원이라면
					if (j % 2 == 0) {
						work_l[j / 2].push(work_r[j].front());
						work_r[j].pop();
					}
					else {
						work_r[j / 2].push(work_r[j].front());
						work_r[j].pop();
					}
				}
			}
		}

	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	solve();

	cout << result;

	return 0;
}