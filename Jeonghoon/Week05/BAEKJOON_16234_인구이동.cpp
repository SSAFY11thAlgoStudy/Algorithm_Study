#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<cmath>
#include<unordered_map>
#include<cstring>

using namespace std;

struct Node {
	int y, x;
};

//연합국의 수와 총 인구수 저장
struct Uni {
	int num;
	int s_pop;
};

int N, L, R;
int map[101][101];
//연합 표시용 배열
int vis[101][101];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
//연합수 확인
int v_cnt;

//연합국의 수와 총 인구수 저장
unordered_map<int, Uni> un;

void input() {
	cin >> N >> L >> R;

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> map[i][j];
		}
	}
}

void init() {
	un.clear();
	v_cnt = 1;
	memset(vis, 0, sizeof(vis));
}

void bfs(int sp_y, int sp_x) {
	queue<Node> q;
	q.push({ sp_y, sp_x });

	//시작지점 연합표시
	vis[sp_y][sp_x] = v_cnt;

	//연합국 수 늘려주고 인구수 더함
	un[v_cnt].num++;
	un[v_cnt].s_pop += map[sp_y][sp_x];

	while (!q.empty()){
		Node now = q.front();
		q.pop();

		for (int i = 0; i < 4; i++){
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			//벽 체크
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;

			//연합이 있는지 확인
			if (vis[ny][nx] != 0) continue;

			//두 국가의 인구수 차이 구하기
			int gap = abs(map[now.y][now.x] - map[ny][nx]);

			if ( gap >= L && gap <= R ){
				//연합인거 표시하기
				vis[ny][nx] = v_cnt;

				//연합국 수 늘려주고 인구수도 더함
				un[v_cnt].num++;
				un[v_cnt].s_pop += map[ny][nx];

				q.push({ ny,nx });
			}
		}
	}
	//다음 연합에 쓸 표식 ++
	v_cnt++;
}

void find_sp() {

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			//연합없는 시작지점 찾아서 스타뜨
			if (vis[i][j] == 0) {
				bfs(i, j);
			}
		}
	}
}

//연합으로 이주 ㄱㄱ
void imigrate() {
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){

			if (vis[i][j] != 0) {
				int uni_num = vis[i][j];
				map[i][j] = un[uni_num].s_pop / un[uni_num].num;
			}
		}
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	input();
	int cnt = 0;

	while (1) {
		//vis을 0으로 초기화해서 
		//연합을 표시하기 위해 1부터 사용
		//초기화를 -1로 하고 0으로 시작했으면
		//종료조건에 +1 안해도 됨
		v_cnt = 1;

		init();

		//시작지점 찾기 + bfs
		find_sp();

		//종료 조건 연합수를 1부터 시작했기 때문에
		//bfs후 연합의 카운트가 N*N+1이면
		//연합이 없는 것이므로 출력하고 종료
		if (v_cnt == (N * N + 1)) {
			cout << cnt;
			break;
		}

		//이주하는 함수
		imigrate();

		//일수 체크
		cnt++;
	}

	return 0;
}