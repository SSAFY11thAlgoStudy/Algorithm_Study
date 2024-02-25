#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int N;
int map[21][21];
int dy[] = { -1,0,0,1 }, dx[] = { 0, -1,1,0 }; // �� �� �� ȭ
int times = 0, cnt = 0;
int sizes = 2;
struct point {
	int y;
	int x;
	int dist = 0;
};
point baby_shark;

struct cmp {
	//�Ÿ��� ����� �ͺ���
	// ���� ���ٸ� ���ʿ��ִ� �ź��� �׸��� ����
	bool operator() (point a, point b) {
		if (a.dist == b.dist) {
			if (a.y == b.y) {
				return a.x > b.x;
			}
			return a.y > b.y;
		}
		return a.dist > b.dist;
	}
};

//������ ���´� 0, 1, 2, 3, 4, 5, 6, 9�� �̷���� �ִ�
//0: �� ĭ
//1, 2, 3, 4, 5, 6 : ĭ�� �ִ� ������� ũ��
//9 : �Ʊ� ����� ��ġ
void input() {
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 9) {
				baby_shark = { i,j };
				map[i][j] = 0;
			}
		}
	}
}

int bfs() {
	// ����� �� ū���� �������� ������ �Ÿ��� �����Ƿ� ������ ��
	priority_queue<point, vector<point>, cmp>pq;
	int visit[21][21] = { 0 };
	pq.push(baby_shark);

	while (!pq.empty()) {
		point now = pq.top();
		pq.pop();

		if (map[now.y][now.x] < sizes && map[now.y][now.x] != 0) {
			times += now.dist; // ����⸦ ���� �Ŀ� times �� ����
			baby_shark = { now.y, now.x }; // �Ʊ��� ��ġ ��ȯ
			cnt++; // �������� Ƚ��
			map[now.y][now.x] = 0; //���� ����� ������
			return 1;
		}
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			//���� ����
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
			//����� ������ �������
			if (visit[ny][nx] >= 1 || map[ny][nx] > sizes) continue;
			// �Ÿ�
			visit[ny][nx] = 1 + visit[now.y][now.x];
			pq.push({ ny,nx, visit[ny][nx] });
		}
	}
	return 0;
}



int main() {
	input();
	// ���� ����Ⱑ ������ ����
	while (bfs()) {
		//����⸦ ���� Ƚ���� ������� ���ٸ� size up
		if (cnt == sizes) {
			sizes++;
			//���̸� ���� Ƚ���ʱ�ȭ
			cnt = 0;
		}
	}
	cout << times;
	return 0;
}