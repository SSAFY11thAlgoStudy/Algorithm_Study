#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int N;
int map[126][126];
int cost[126][126];
int dy[] = { 0,0,-1,1 }, dx[] = { 1,-1,0,0 };


struct point {
	int y, x;
};

struct cmp {
	bool operator() (point a, point b) {
		return cost[a.y][a.x] > cost[b.y][b.x];
	}
};


void input() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
}

int solve() {
	priority_queue<point, vector<point>, cmp>pq;
	pq.push({ 0,0 });
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cost[i][j] = 21e8;
		}
	}
	cost[0][0] = map[0][0];

	while (!pq.empty()) {
		point now = pq.top();
		pq.pop();
		if (now.y == N - 1 && now.x == N - 1) {
			return cost[N - 1][N - 1];
		}

		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			int nextcost = cost[now.y][now.x] + map[ny][nx];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
			if (cost[ny][nx] <= nextcost) continue;
			cost[ny][nx] = nextcost;
			pq.push({ ny,nx });
		}
	}
	return 0;
}

int main() {
	int  i = 1;
	while (1) {

		cin >> N;
		if (N == 0) {
			return 0;
		}

		input();
		cout << "Problem " << i++ << ": " << solve() << endl;

	}
}