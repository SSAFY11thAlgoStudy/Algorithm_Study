#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

int n, cnt, totalBsum;
int map[30][30];
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };
struct Info {
	int y, x, score;
};
vector<Info>groupPos[900];
bool visited[30][30];

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
}

void init() {
	cnt = 0;
	for (int i = 0; i < 900; i++) {
		groupPos[i].clear();
	}
	memset(visited, false, sizeof(visited));
}

bool isValid(int y, int x, int score) {
	return y >= 1 && x >= 1 && y <= n && x <= n && map[y][x] == score;
}

// 1. BFS�� ���� �� �׷��� �����ϱ�
void grouping(int y, int x, int score, int cnt) {
	queue<Info>q;
	q.push({ y,x,map[y][x] });
	visited[y][x] = true;
	while (!q.empty()) {
		Info now = q.front();
		groupPos[cnt].push_back({ now.y,now.x,score });
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			// ��� Ȥ�� ���� ���ھ �ƴϸ� ���� x
			if (!isValid(ny, nx, score))continue;
			// �̹� �湮�� ������ ���� x
			if (visited[ny][nx])continue;
			visited[ny][nx] = true;
			q.push({ ny,nx,score });
		}
	}

}

int calNear(int a, int b) {
	// a�׷�, b�׷�
	int a_score = groupPos[a][0].score;
	int b_score = groupPos[b][0].score;
	// ���� ���� ���� ����ؼ�, b�� ��ǥ�� ����
	bool bPos[30][30] = { false, };
	for (int i = 0; i < groupPos[b].size(); i++) {
		Info now = groupPos[b][i];
		bPos[now.y][now.x] = true;
	}
	int cnt = 0;
	for (int i = 0; i < groupPos[a].size(); i++) {
		Info now = groupPos[a][i];
		for (int j = 0; j < 4; j++) {
			int ny = now.y + dy[j];
			int nx = now.x + dx[j];
			if (!isValid(ny, nx, b_score))continue;
			if (!bPos[ny][nx])continue;
			cnt++;
		}
	}
	return cnt;
}

void calScore() {
	// ��ȭ�ο� ���� 0���� ū �͸� �ɷ����� ����
	// �׷� a,b�� ���� �´�� �ִ� ���� ���� ���ؾ���
	// ���� nC2 ������ ���� ��� ��������
	int thisTurnBsum = 0;
	for (int i = 1; i < cnt; i++) {
		for (int j = i + 1; j <= cnt; j++) {
			// (�׷� a�� ���� ĭ�� �� + �׷� b�� ���� ĭ�� ��)
			int cnt_score = groupPos[i].size() + groupPos[j].size();
			// �׷� a�� �̷�� �ִ� ���� ��
			int score_aGroup = groupPos[i][0].score;
			// �׷� b�� �̷�� �ִ� ���� ��
			int score_bGroup = groupPos[j][0].score;
			// ���߿� ����� �� (�� �׷��� ���ڰ� �ٸ��� ���ʿ� �´��� ���� ���� ����?!)
			if (score_aGroup == score_bGroup)continue;
			// �׷� a�� b�� ���� �´�� �ִ� ���� ��
			// �׷� a�� �� ĭ�� 4���⿡ �׷� b�� ���� ���� �Ǵ�
			int near_cnt = calNear(i, j);
			// 0���̸� ���� x
			if (near_cnt == 0)continue;
			//cout << i << " " << j << " ";
			//cout << near_cnt << " ";
			int nowBsum = (cnt_score) * (score_aGroup) * (score_bGroup) * (near_cnt);
			//cout << nowBsum << " ";
			thisTurnBsum += nowBsum;
		}
	}
	totalBsum += thisTurnBsum;
}

void rotMap() {
	// 1. ���߾� ���� �κ� ȸ�� (�ݽð�)
		// ��� ���� ���ʿ��� ���������� ��� ���� ���ʺ��� �Ʒ��� ����
		// ��� ���� ������ �Ʒ��� ��� ���� �����ʺ��� �������� ����
	int copyMap[30][30] = { 0, };
	int center = (n / 2) + 1;
	for (int i = 1; i <= n; i++) {
		copyMap[center][i] = map[i][center];
		copyMap[i][center] = map[center][n + 1 - i];
	}
	// 2. ���� ���� 4���� ���簢�� (�ð�)
	// ī�� �� ���簢���� ���ϴ� ���ڸ� (sy,sx)���� sy����, sx���ҷ� ����
	// ���� �� ���簢���� ���� ���� (i,j)���� j����, i������ �����Ͽ� ī��
	// �»��
	int sx = center - 1;
	for (int i = 1; i <= center - 1; i++) {
		int sy = center - 1;
		for (int j = center - 1; j >= 1; j--) {
			copyMap[sy][sx] = map[i][j];
			sy--;
		}
		sx--;
	}
	// ����
	sx = n;
	for (int i = 1; i <= center - 1; i++) {
		int sy = center - 1;
		for (int j = n; j >= center + 1; j--) {
			copyMap[sy][sx] = map[i][j];
			sy--;
		}
		sx--;
	}
	// ���ϴ�
	sx = center - 1;
	for (int i = center + 1; i <= n; i++) {
		int sy = n;
		for (int j = center - 1; j >= 1; j--) {
			copyMap[sy][sx] = map[i][j];
			sy--;
		}
		sx--;
	}
	// ���ϴ�
	sx = n;
	for (int i = center + 1; i <= n; i++) {
		int sy = n;
		for (int j = n; j >= center + 1; j--) {
			copyMap[sy][sx] = map[i][j];
			sy--;
		}
		sx--;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = copyMap[i][j];
		}
	}

}

void func() {
	init();
	// 1. BFS�� ���� �� �׷��� �����ϱ�
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j]) {
				cnt++;
				grouping(i, j, map[i][j], cnt);
			}
		}
	}
	// 2. ���� ���� ���ϱ�
	calScore();

	// 3. ȸ��
	rotMap();
}

int main() {
	input();
	for (int i = 0; i <= 3; i++) {
		func();
	}
	cout << totalBsum;
	return 0;
}