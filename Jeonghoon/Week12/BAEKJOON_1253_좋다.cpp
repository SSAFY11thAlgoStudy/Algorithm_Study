#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

int N;
//��ü ���� �����ϴ� �迭
long long num[2001];
int cnt;

void input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> num[i];
	}
	//������������ ����
	sort(num, num + N);
}

void solve() {
	//�ε��� 0������ Ÿ�� ���ڷ� ����, ���� �� �ִ��� Ȯ��
	for (int i = 0; i < N; i++) {
		//0������ ����ؼ� 
		for (int j = 0; j < N; j++) {
			//���� ���� ����ϸ� �ȵǹǷ� continue
			if (i == j) continue;
			// ���������� ���� flag
			int flag = 0;
			// Ÿ�� ���ڿ��� 2���� �� �� �ϳ��� ��
			// Ÿ�� �� = A + B => Ÿ�� �� - A = B �̹Ƿ�
			long long temp = num[i] - num[j];

			// �̺�Ž������ B ã��
			int sp = 0;
			int ep = N;

			while (sp < ep) {
				int mid = (sp + ep) / 2;

				//temp - num[mid] > 0 �̸� num[mid]�� Ŀ���� �ϹǷ�
				if (temp - num[mid] > 0) {
					sp = mid + 1;
				}
				//temp - num[mid] > 0 �̸� num[mid]�� �۾����� �ϹǷ�
				else if (temp - num[mid] < 0) {
					ep = mid;
				}
				//temp - num[mid] = 0 �� ��,
				else {
					//A�� ���ų� B�� ������ �ȵǹǷ� mid�� �ٲ㼭 �ٽ� ����
					if (j == mid || i == mid) {
						sp = mid + 1;
					}
					//���ܿ� �Ȱɸ��� ��� flag �ٲٰ� cnt++
					else {
						cnt++;
						flag = 1;
						break;
					}
				}
			}

			if (flag == 1) {
				break;
			}
		}
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	if (N > 2) {
		solve();
	}
	cout << cnt;

	return 0;
}