#include<iostream>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int n;
int map[126][126];
int ans[126][126];
int t = 0;
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };

void bfs(int y, int x) {
	queue<pair<int, int>> q;
	q.push({ y,x });

	while (!q.empty()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int k = 0; k < 4; k++) {
			int ny = y + dy[k];
			int nx = x + dx[k];

			//������ �����ϰ�
			if (ny < n && ny >= 0 && nx < n && nx >= 0) {
				//���� ans[ny][nx]�� �ִ� ������ ���� ���ؼ� ���� ���� �� ũ��
				if (ans[ny][nx] > ans[y][x] + map[ny][nx]) {
					ans[ny][nx] = ans[y][x] + map[ny][nx]; // ���� ������ ans�� ä���ֱ�
					q.push({ ny,nx });
				}
			}
		}
	}
}

int main() {
	while (true) {
		//while���̹Ƿ� �׻� �ʱ�ȭ
		memset(map, 0, sizeof(map));
		cin >> n;
		if (n == 0) break;
		//�ʰ� ans ���� ū������ �ޱ�
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
				ans[i][j] = 1e9;
			}
		}
		//������ (0,0)�̹Ƿ� �ּҰ� �񱳸� ���� ans[0][0]�� map[0][0]�־��ֱ�
		ans[0][0] = map[0][0];
		bfs(0, 0); //(0,0)���� ����
		t++;
		cout << "Problem " << t << ": " << ans[n - 1][n - 1] << '\n';
	}
	return 0;
}