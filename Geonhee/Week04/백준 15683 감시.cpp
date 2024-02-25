#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int map[8][8];
int dx[4] = { 0,1,0,-1 };// 방향 오른쪽, 위쪽, 왼쪽, 아래쪽
int dy[4] = { 1,0,-1,0 };
vector<pair<int, int>> arr;
int cnt = 0;
int res = 21e8;//사각 지대 최소 크기
void check(int x1, int y1, int d) {
	d %= 4; //방향 맞춰주기
	while (1) {
		int nx = x1 + dx[d];
		int ny = y1 + dy[d];
		x1 = nx;
		y1 = ny;
		if (nx >= n || nx < 0 || ny >= m || ny < 0) break;
		if (map[nx][ny] == 6) break;
		if (map[nx][ny] != 0) continue;
		map[nx][ny] = 7; //CCTV걸리는 곳 바꿔주기
	}
}

void dfs(int st) {
	if (cnt == st) { //cctv갯수만큼 돌았으면
		int temp = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 0) {
					temp++;
				}
			}
		}
		res = min(temp, res); // 최소값 찾아주기
		return;
	}
	int save[9][9];
	int x = arr[st].first;
	int y = arr[st].second;

	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				save[i][j] = map[i][j]; //원래 맵 저장
			}
		}
		if (map[x][y] == 1) { //1일때 오른쪽
			check(x, y, k);
		}
		else if (map[x][y] == 2) { //2일때 오른쪽 ,왼쪽 
			check(x, y, k);
			check(x, y, k + 2);
		}
		else if (map[x][y] == 3) {//3일때 오른쪽, 위쪽
			check(x, y, k);
			check(x, y, k + 3);
		}
		else if (map[x][y] == 4) { //4일때 오른쪽,왼쪽,위쪽
			check(x, y, k);
			check(x, y, k + 2);
			check(x, y, k + 3);
		}
		else if (map[x][y] == 5) {//5일때 오른쪽,왼쪽,위쪽,아래쪽
			check(x, y, k);
			check(x, y, k + 1);
			check(x, y, k + 2);
			check(x, y, k + 3);
		}
		dfs(st + 1); //돌았으면 다음CCTV찾아가기
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				map[i][j] = save[i][j]; //맵 다시 원래대로 만들어주기
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] != 0 && map[i][j] != 6) {
				arr.push_back({ i,j }); //CCTV 좌표 저장
				cnt++;
			}
		}
	}
	dfs(0);
	cout << res;
	return 0;
}