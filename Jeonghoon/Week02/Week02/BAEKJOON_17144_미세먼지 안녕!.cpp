#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

int R, C, T;
int map[51][51];
//�п��� ����� ����迭
int dy[4] = { 0, -1, 0, 1 };
int dx[4] = { 1, 0, -1, 0 };
//�п��� ������ �� ���� ����
int visited[51][51];
//û���� ��ġ(y��ǥ) ����
int y[2];
int ans;

void input() {
	cin >> R >> C >> T;
	int num = 0;

	// �Է¹迭 �ޱ�
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
		}

		//�Է� �迭�߿� û���� ��ġ ã��
		if (map[i][0] == -1) {
			y[num] = i;
			num++;
		}
	}
}

void solve1() {
	// �п� ����
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			// �п� ������ ������ ��
			if (map[i][j] > 0) {
				// �п��� ���� ����
				int cnt = 0;

				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];

					// ���̰ų� ����û���Ⱑ ������ �п�X
					if (nx < 0 || nx >= C || ny < 0 || ny >= R || map[ny][nx] == -1) {
						continue;
					}

					//������ ����� �����ٰ� �̹��� �и��� ���� ����
					visited[ny][nx] += (map[i][j] / 5);
					cnt++;
				}
				//���ݱ��� ����� �� + �ʿ� ��ǲ���� �ִ� �� - �п��Ǽ� ���� ��
				visited[i][j] += map[i][j] - (map[i][j] / 5) * cnt;
			}
		}
	}

	//�ӽ÷� �����ص� ������ map���� �ű�� �ʱ�ȭ
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = visited[i][j];
			visited[i][j] = 0;
		}
	}
}

void solve2(int y) {

	// �� - �ݽð�
  //��
	for (int i = y - 1; i >= 1; i--) {
		map[i][0] = map[i - 1][0];
	}
	//������
	for (int i = 0; i < C - 1; i++) {
		map[0][i] = map[0][i + 1];
	}
	// �Ʒ�
	for (int i = 0; i < y; i++) {
		map[i][C - 1] = map[i + 1][C - 1];
	}
	// ����
	for (int i = C - 1; i >= 2; i--) {
		map[y][i] = map[y][i - 1];
	}

	// ��ȭ�� �ڸ��� 0
	map[y][1] = 0;
	//û���� �ڸ� �ٽ� -1�� �����
	map[y][0] = -1;
}

void solve3(int y) {
	// �Ʒ� - �ð�
  // �Ʒ���
	for (int i = y + 1; i < R - 1; i++) {
		map[i][0] = map[i + 1][0];
	}
	// ������
	for (int i = 0; i < C - 1; i++) {
		map[R - 1][i] = map[R - 1][i + 1];
	}
	// ����
	for (int i = R - 1; i > y; i--) {
		map[i][C - 1] = map[i - 1][C - 1];
	}
	// ����
	for (int i = C - 1; i >= 2; i--) {
		map[y][i] = map[y][i - 1];
	}

	// ��ȭ�� �ڸ��� 0
	map[y][1] = 0;
	//û���� �ڸ� �ٽ� 1�� �����
	map[y][0] = -1;
}

void sum() {
	// ��ü Ž���ؼ� ���� �̼����� ���ϱ�
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			ans += map[i][j];
		}
	}
}

int main() {
	freopen("sample.txt", "r", stdin);

	input();

	// �ʱ� �ð� 1��
	int tim = 1;

	// �Է¹��� T�ʱ��� �ݺ�
	while (tim <= T) {
		solve1();
		solve2(y[0]);
		solve3(y[1]);
		tim++;
	}

	sum();

	// û������ ��(-1)�� 2�� �����Ƿ� +2
	cout << ans + 2;

	return 0;
}