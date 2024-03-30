#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

struct Node {
	int y, x;
};

int map[5][5]; // 지도 배열
int visited[5][5]; // 지도 배열
vector<Node> goals; // 목적지 벡터
int n, m;
int result = 0;

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

void Input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	int tmpx, tmpy;

	for (int i = 0; i < m; i++) {
		cin >> tmpy >> tmpx;
		goals.push_back({ tmpy - 1, tmpx - 1 });
	}
}

void Solve(int idx, int y, int x)
{
	// 목적지에 도착했을 경우 
	if (goals[idx].y == y && goals[idx].x == x)
	{
		if (idx == m - 1) {
			result++; // 개수 증가 
			return;
		}

		Solve(idx + 1, y, x);
	}

	for (int i = 0; i < 4; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		// 범위 초과했으면 패스 
		if (ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
		// 방문했거나 벽이라면 패스 
		if (visited[ny][nx] == 1 || map[ny][nx] == 1) continue;

		visited[ny][nx] = 1; // 방문 
		Solve(idx, ny, nx);
		visited[ny][nx] = 0; // 방문 해제
	}


}

int main() {

	//freopen("sample.txt", "r", stdin);
	Input();

	int y = goals[0].y;
	int x = goals[0].x;
	visited[y][x] = 1;

	Solve(1, y, x);

	cout << result;

	return 0;
}