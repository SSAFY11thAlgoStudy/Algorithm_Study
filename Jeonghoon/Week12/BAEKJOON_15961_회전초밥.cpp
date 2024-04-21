#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>

using namespace std;

int N, D, K, C;
//��ü �ʹ� �Է�
int sushi[30001];
//�������� Ȯ���ϴ� dat
int eat[3001];
//�������
int result;

void input() {
	cin >> N >> D >> K >> C;

	for (int i = 0; i < N; i++) {
		cin >> sushi[i];
	}
}

void solve() {
	//������ �ڷ� �����ϰ� ������ ���� �ϹǷ� queue ���
	queue<int> q;
	//���� ���� ī��Ʈ
	int t_cnt = 0;

	//queue �ʱ� ������ ���� K�� �԰� queue�� ����
	for (int i = 0; i < K; i++) {
		q.push(sushi[i]);
		//���� �ø���
		t_cnt++;
		//�������� �ø���
		eat[sushi[i]]++;

		//�����̶� ���ٸ� �� �������� �����ָ� �ǹǷ� --
		if (sushi[i] == C) {
			t_cnt--;
			continue;
		}

		//�̹� ���� �������� --;
		if (eat[sushi[i]] > 1) {
			t_cnt--;
		}
	}

	//�񱳸� ���� max_cnt
	int max_cnt = t_cnt;

	for (int i = K; i < N + K - 1; i++) {
		//�� �տ��� ����
		int t = q.front();
		q.pop();
		//���� �� --
		eat[t]--;

		//���� �ߺ��ؼ� ������ �ƴ϶�� ���� ī��Ʈ --
		if (eat[t] == 0) {
			t_cnt--;
		}

		//�����̶� ������� �̸� ī��Ʈ�� ����� ������ ++
		if (t == C && eat[C] == 0) {
			t_cnt++;
		}

		q.push(sushi[i % N]);
		t_cnt++;
		//�ߺ��̸� --
		if (eat[sushi[i % N]] != 0) {
			t_cnt--;
		}

		//�����̶� ���� ó�� �Դ´ٸ� --;
		if (sushi[i % N] == C && eat[C] == 0) {
			t_cnt--;
		}

		eat[sushi[i % N]]++;

		if (t_cnt > max_cnt) {
			max_cnt = t_cnt;
		}
	}
	//���� ���� ������ + ���� 1����
	result = max_cnt + 1;
}

int main() {

	//freopen("sample.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	input();
	solve();

	cout << result;

	return 0;
}