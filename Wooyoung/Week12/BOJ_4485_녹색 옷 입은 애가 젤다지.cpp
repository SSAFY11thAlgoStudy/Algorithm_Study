#include<iostream>
#include<cstring>
#include<climits>
#include<queue>
#include<vector>
#define MAX INT_MAX
using namespace std;

int n;
int map[125][125];
int dist[125][125];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int goal_y, goal_x;
// n이 125라 그냥 BFS, DFS로 [n-1][n-1]까지 도착했을 때 잃은 금액을 매번 최소값으로 갱신하는 것도 하나의 방법일듯?

struct Info {
	int y, x, money;
};

struct Cmp {
	bool operator()(Info a, Info b) {
		return a.money > b.money;
	}
};

void input() {

	for (int i = 0; i < 125; i++) {
		for (int j = 0; j < 125; j++) {
			map[i][j] = 0;
			dist[i][j] = MAX;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	goal_y = n - 1;
	goal_x = n - 1;

}

bool isValid(int y, int x) {
	return y >= 0 && x >= 0 && y <= n - 1 && x <= n - 1;
}

void dijkstra() {
	priority_queue<Info, vector<Info>, Cmp>pq;
	pq.push({ 0,0,map[0][0] });
	dist[0][0] = map[0][0];
	while (!pq.empty()) {
		Info now = pq.top();
		pq.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (!isValid(ny, nx))continue;
			int nm = now.money + map[ny][nx];
			if (dist[ny][nx] <= nm)continue;
			dist[ny][nx] = nm;
			pq.push({ ny,nx,nm });

		}
	}

}

int main() {
	int tc = 1;
	while (1) {
		cin >> n;
		if (n == 0) {
			break;
		}
		else {
			input();
			dijkstra();
			cout << "Problem " << tc++ << ": " << dist[goal_y][goal_x] << "\n";
		}
	}
	return 0;
}