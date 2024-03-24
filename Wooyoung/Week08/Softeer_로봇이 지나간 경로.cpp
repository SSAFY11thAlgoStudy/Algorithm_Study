#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<climits>
using namespace std;

#define MAX INT_MAX
int h, w, cnt_sharp;
// 동, 북, 서, 남 순서

// A, LA, RA(LLLA)
// L은 왼쪽으로 방향을 튼다.
// 동 -> 북 (0 -> 1) (+1)
// 북 -> 서 (1 -> 2) (+1)
// 서 -> 남 (2 -> 3) (+1)
// 남 -> 동 (3 -> 0) (+1 / 4)
// -> +1 후 모듈연산


int dy[4] = { 0,-1,0,1 };
int dx[4] = { 1,0,-1,0 };
int cur_size = MAX;
int start_dir;
char ans_dir;
int start_y, start_x;
int ans_y, ans_x;
bool visited[27][27];
char map[27][27];
vector<char>save;
vector<char>ans;

// L : 바라보는 방향 기준 왼쪽 90도 회전
// R : 바라보는 방향 기준 오른쪽 90도 회전
// A : 바라보는 방향 기준 앞으로 2칸 전진
// 모든 경우 다 해보고 전부 방문했을 때 현재 명령어 개수 비교해서
// 더 작은 명령어로 정답 갱신


vector<pair<int, int>>pos;

bool isValid(int y, int x) {
	return y >= 1 && x >= 1 && y <= h && x <= w && !visited[y][x] && map[y][x] == '#';
}

void simul(int y, int x, int dir, int cnt_sharp_visit) {

	// 이미 현재 경로가 더 길면 더이상 탐색x 
	if (save.size() >= cur_size)return;

	// 모든 #지점 방문 시
	if (cnt_sharp == cnt_sharp_visit) {

		cur_size = save.size();
		ans = save;

		if (start_dir == 0) {
			ans_dir = '>';
		}
		else if (start_dir == 1) {
			ans_dir = '^';
		}
		else if (start_dir == 2) {
			ans_dir = '<';
		}
		else {
			ans_dir = 'v';
		}
		ans_y = start_y;
		ans_x = start_x;

		return;
	}

	// A - LA - RA  순서로 재귀 (중복 허용)

	for (int i = 0; i < 4; i++) {

		int next_dir = (dir + i) % 4;
		int next_y = y + dy[next_dir];
		int next_x = x + dx[next_dir];
		if (isValid(next_y, next_x) && isValid(next_y + dy[next_dir], next_x + dx[next_dir])) {
			string c;
			if (i == 0) {
				c = "A";
			}
			else if (i == 1) {
				c = "LA";
			}
			else if (i == 2) {
				continue;
			}
			else if (i == 3) {
				c = "RA";
			}
			for (int j = 0; j < c.length(); j++) {
				save.push_back(c[j]);
			}
			visited[next_y][next_x] = true;
			visited[next_y + dy[next_dir]][next_x + dx[next_dir]] = true;
			simul(next_y + dy[next_dir], next_x + dx[next_dir], next_dir, cnt_sharp_visit + 2);
			for (int j = 0; j < c.length(); j++) {
				save.pop_back();
			}
			visited[next_y][next_x] = false;
			visited[next_y + dy[next_dir]][next_x + dx[next_dir]] = false;

		}
	}

	return;
}

int main() {

	cin >> h >> w;
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			char a;
			cin >> a;
			if (a == '#') {
				pos.push_back({ i,j });
				cnt_sharp++;
				map[i][j] = '#';
			}
		}
	}

	for (int i = 0; i < pos.size(); i++) {
		for (int j = 0; j < 4; j++) {
			int cnt_s = 0;
			start_dir = j;
			start_y = pos[i].first;
			start_x = pos[i].second;

			for (int k = 0; k < 4; k++) {
				int ny = start_y + dy[k];
				int nx = start_x + dx[k];
				if (!isValid(ny, nx))continue;
				if (map[ny][nx] == '#')cnt_s++;
			}

			if (cnt_s != 1)break;
			visited[pos[i].first][pos[i].second] = true;
			simul(pos[i].first, pos[i].second, j, 1);
			visited[pos[i].first][pos[i].second] = false;
		}
	}


	cout << ans_y << " " << ans_x << "\n";
	cout << ans_dir << "\n";

	for (auto p : ans) {
		cout << p;
	}

	return 0;
}