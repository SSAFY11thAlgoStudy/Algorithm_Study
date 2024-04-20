#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

// 젤다의 전설게임
// 화폐 : 루피
// 그러나 도둑루피가 있는데 이것은 루피가 감소
// N * N 동굴의 제일 왼쪽 위에 있습니다
// 링크가 주인공(녹색 옷)
// 젤다가 잡혀있는 공주
// 근데 게임 제목에 젤다가 나왔대
// 사람들이 착각 -> 정신병? 왜?

// 암튼 링크는 맨 오른쪽 아래까지 이동해야한다
// 칸마다 도둑루피가 존재
// 해당 도둑루피 크기만큼 소지금을 잃는다
// 잃는 금액을 최소로 하여 동굴 건너편으로 이동해야 한다
// 한번에 상하좌우 한칸씩 이동
// 잃는 최소 금액?

// 다익스트라 : 사용해서 최소 비용을 dist맵에 저장한다

struct Edge
{
	int y;
	int x;
	int cost;
	// 도둑루피가 적은순서대로 정렬
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

	// dist 맵 초기화
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
			// dist맵에 저장되어 있는 값보다 크면 갱신할 필요가 없음
			if (dist[next.y][next.x] <= nextcost)continue;

			pq.push({ next.y, next.x ,nextcost });
			dist[next.y][next.x] = nextcost;
		}
	}
	// 맨 오른쪽 아래에 있는 값을 반환한다
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