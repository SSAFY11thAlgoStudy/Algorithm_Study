#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<cmath>

using namespace std;

int H, K, R;
//������ ����, ������ ������ �ø� ����, ���������� �ø� ����
queue<int> work[2049], work_r[2049], work_l[2049];
//���� ���� ��
int node;
int result;

void input() {
	cin >> H >> K >> R;

	node = pow(2, H);

	//���� �������� ���� �Է�
	for (int i = node; i < node * 2; i++) {
		for (int j = 0; j < K; j++) {
			int temp;
			cin >> temp;
			work[i].push(temp);
		}
	}
}

void solve() {
	//��¥
	for (int i = 1; i <= R; i++) {

		//���� �Ѹ� ���� Ȯ��

		for (int j = 1; j < node * 2; j++) {

			//ť�� ��������� �Ѿ��
			if (work[j].empty() && work_r[j].empty() && work_l[j].empty()) continue;

			//���� �����̶�� ���� �ϳ��� ó��
			if (j >= node) {
				//���� ���� �̶��
				if (j % 2 == 0) {
					//���ʿ� �ֱ�
					work_l[j / 2].push(work[j].front());
					work[j].pop();
				}
				//������ �����̶��
				else {
					//�����ʿ� �ֱ�
					work_r[j / 2].push(work[j].front());
					work[j].pop();
				}
			}
			//���� ������ �ƴ϶��
			else {
				//�����̶�� ����� ���ϱ�
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
				//������ �ƴ϶�� Ȧ�� �� �϶�
				else if (i % 2 == 1) {
					//���� �����̶��
					if (j % 2 == 0) {
						work_l[j / 2].push(work_l[j].front());
						work_l[j].pop();
					}
					else {
						work_r[j / 2].push(work_l[j].front());
						work_l[j].pop();
					}
				}
				//¦�� �� �϶�
				else if (i % 2 == 0) {
					//���������̶��
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