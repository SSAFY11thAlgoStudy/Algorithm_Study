#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

// ������ ��������
// ȭ�� : ����
// �׷��� ���Ϸ��ǰ� �ִµ� �̰��� ���ǰ� ����
// N * N ������ ���� ���� ���� �ֽ��ϴ�
// ��ũ�� ���ΰ�(��� ��)
// ���ٰ� �����ִ� ����
// �ٵ� ���� ���� ���ٰ� ���Դ�
// ������� ���� -> ���ź�? ��?

// ��ư ��ũ�� �� ������ �Ʒ����� �̵��ؾ��Ѵ�
// ĭ���� ���Ϸ��ǰ� ����
// �ش� ���Ϸ��� ũ�⸸ŭ �������� �Ҵ´�
// �Ҵ� �ݾ��� �ּҷ� �Ͽ� ���� �ǳ������� �̵��ؾ� �Ѵ�
// �ѹ��� �����¿� ��ĭ�� �̵�
// �Ҵ� �ּ� �ݾ�?

// ���ͽ�Ʈ�� : ����ؼ� �ּ� ����� dist�ʿ� �����Ѵ�

struct Edge
{
	int y;
	int x;
	int cost;
	// ���Ϸ��ǰ� ����������� ����
	bool operator<(Edge right) const {
		if (cost < right.cost)return false;
		if (cost > right.cost)return true;
		return false;
	}
};

int N;
int MAP[125][125];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int ans;

void input() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
}

void init() {
	memset(MAP, 0, sizeof(MAP));
}

int dijkstra(int y, int x) {

	priority_queue<Edge>pq;
	int dist[125][125] = { 0, };

	// dist �� �ʱ�ȭ
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			dist[i][j] = 9999999;
		}
	}

	dist[0][0] = MAP[0][0];

	pq.push({ 0,0,MAP[0][0] });

	while (!pq.empty()) {

		Edge now = pq.top();
		pq.pop();

		for (int d = 0; d < 4; d++)
		{
			int ny = now.y + dy[d];
			int nx = now.x + dx[d];
			if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
			Edge next = { ny, nx, MAP[ny][nx] };
			int nextcost = next.cost + dist[now.y][now.x];
			// dist�ʿ� ����Ǿ� �ִ� ������ ũ�� ������ �ʿ䰡 ����
			if (dist[next.y][next.x] <= nextcost)continue;

			pq.push({ next.y, next.x ,nextcost });
			dist[next.y][next.x] = nextcost;
		}
	}
	// �� ������ �Ʒ��� �ִ� ���� ��ȯ�Ѵ�
	return dist[N - 1][N - 1];
}

int main() {
	int tc = 0;
	while (true) {
		cin >> N;
		if (N == 0) {
			break;
		}
		init();
		input();
		ans = dijkstra(0, 0);
		tc++;
		cout << "Problem " << tc << ":" << " " << ans << endl;
	}

	return 0;
}