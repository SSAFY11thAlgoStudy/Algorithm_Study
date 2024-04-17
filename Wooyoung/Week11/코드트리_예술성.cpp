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

// 1. BFS를 통해 각 그룹을 구분하기
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
			// 장외 혹은 동일 스코어가 아니면 진행 x
			if (!isValid(ny, nx, score))continue;
			// 이미 방문한 지점은 진행 x
			if (visited[ny][nx])continue;
			visited[ny][nx] = true;
			q.push({ ny,nx,score });
		}
	}

}

int calNear(int a, int b) {
	// a그룹, b그룹
	int a_score = groupPos[a][0].score;
	int b_score = groupPos[b][0].score;
	// 같은 수일 때를 고려해서, b의 좌표만 지정
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
	// 조화로움 값이 0보다 큰 것만 걸러내기 위해
	// 그룹 a,b가 서로 맞닿아 있는 변의 수를 구해야함
	// 따라서 nC2 조합을 통해 모두 따져야함
	int thisTurnBsum = 0;
	for (int i = 1; i < cnt; i++) {
		for (int j = i + 1; j <= cnt; j++) {
			// (그룹 a에 속한 칸의 수 + 그룹 b에 속한 칸의 수)
			int cnt_score = groupPos[i].size() + groupPos[j].size();
			// 그룹 a를 이루고 있는 숫자 값
			int score_aGroup = groupPos[i][0].score;
			// 그룹 b를 이루고 있는 숫자 값
			int score_bGroup = groupPos[j][0].score;
			// 나중에 고려할 것 (두 그룹의 숫자가 다르면 애초에 맞닿은 변의 수가 없다?!)
			if (score_aGroup == score_bGroup)continue;
			// 그룹 a와 b가 서로 맞닿아 있는 변의 수
			// 그룹 a의 각 칸의 4방향에 그룹 b의 숫자 개수 판단
			int near_cnt = calNear(i, j);
			// 0개이면 진행 x
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
	// 1. 정중앙 십자 부분 회전 (반시계)
		// 가운데 행은 왼쪽에서 오른쪽으로 가운데 열의 위쪽부터 아래로 저장
		// 가운데 열은 위에서 아래로 가운데 행의 오른쪽부터 왼쪽으로 저장
	int copyMap[30][30] = { 0, };
	int center = (n / 2) + 1;
	for (int i = 1; i <= n; i++) {
		copyMap[center][i] = map[i][center];
		copyMap[i][center] = map[center][n + 1 - i];
	}
	// 2. 십자 제외 4개의 정사각형 (시계)
	// 카피 맵 정사각형의 우하단 격자를 (sy,sx)부터 sy감소, sx감소로 진행
	// 원본 맵 정사각형의 우상단 격자 (i,j)부터 j감소, i증가로 진행하여 카피
	// 좌상단
	int sx = center - 1;
	for (int i = 1; i <= center - 1; i++) {
		int sy = center - 1;
		for (int j = center - 1; j >= 1; j--) {
			copyMap[sy][sx] = map[i][j];
			sy--;
		}
		sx--;
	}
	// 우상단
	sx = n;
	for (int i = 1; i <= center - 1; i++) {
		int sy = center - 1;
		for (int j = n; j >= center + 1; j--) {
			copyMap[sy][sx] = map[i][j];
			sy--;
		}
		sx--;
	}
	// 좌하단
	sx = center - 1;
	for (int i = center + 1; i <= n; i++) {
		int sy = n;
		for (int j = center - 1; j >= 1; j--) {
			copyMap[sy][sx] = map[i][j];
			sy--;
		}
		sx--;
	}
	// 우하단
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
	// 1. BFS를 통해 각 그룹을 구분하기
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j]) {
				cnt++;
				grouping(i, j, map[i][j], cnt);
			}
		}
	}
	// 2. 예술 점수 구하기
	calScore();

	// 3. 회전
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