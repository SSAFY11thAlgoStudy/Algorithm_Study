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

			//범위를 만족하고
			if (ny < n && ny >= 0 && nx < n && nx >= 0) {
				//현재 ans[ny][nx]에 있는 값보다 다음 더해서 들어올 값이 더 크면
				if (ans[ny][nx] > ans[y][x] + map[ny][nx]) {
					ans[ny][nx] = ans[y][x] + map[ny][nx]; // 작은 값으로 ans맵 채워주기
					q.push({ ny,nx });
				}
			}
		}
	}
}

int main() {
	while (true) {
		//while문이므로 항상 초기화
		memset(map, 0, sizeof(map));
		cin >> n;
		if (n == 0) break;
		//맵과 ans 가장 큰값으로 받기
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
				ans[i][j] = 1e9;
			}
		}
		//시작점 (0,0)이므로 최소값 비교를 위해 ans[0][0]에 map[0][0]넣어주기
		ans[0][0] = map[0][0];
		bfs(0, 0); //(0,0)부터 시작
		t++;
		cout << "Problem " << t << ": " << ans[n - 1][n - 1] << '\n';
	}
	return 0;
}