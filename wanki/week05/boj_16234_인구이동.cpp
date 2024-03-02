#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

int N, L, R;
int map[50][50];
int dy[] = { 0,0,1,-1 }, dx[] = { 1,-1,0,0 };
int visit[50][50] = { 0 };

struct  point
{
	int y;
	int x;
};

//입력
void input() {
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> map[i][j];
		}
	}
}


// 연합을 확인하여 합치는 함수
int solve(point st) {
	queue<point>q;
	vector<point>v;
	int sum = 0; //sum을 통해 지나온 국가의 인구수를 더하면서 진행
	q.push(st);
	visit[st.y][st.x] = 1;
	while (!q.empty()) {
		point now = q.front();
		q.pop();
		v.push_back({ now.y, now.x });//최소한 자기자신은 자기자신과 연합을 한다.
		sum += map[now.y][now.x]; 
		for (int i = 0; i < 4; i++)
		{
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			// now와 next간의 인구 차이를 구함
			int checkvalid = abs(map[ny][nx] - map[now.y][now.x]);
			//범위 확인
			if (ny < 0 || nx < 0 || ny >= N || nx >= N)continue;
			// 방문한 곳인지 확인
			if (visit[ny][nx] != 0)continue;
			// 두 나라의 인구 차이가 L명 이상, R명 이하라면
			if (checkvalid < L || checkvalid > R) continue;
			visit[ny][nx] = 1;
			q.push({ ny, nx });

		}
	}
	//연합이된 지역의 개수
	int sizes = v.size();

	// 연합이 자기자신만 있다면 0을 리턴
	if (sizes <= 1) return 0;

	//vector에 저장된 국가에 연합의 평균 값을 넣어줌
	for (point p : v) {
		map[p.y][p.x] = sum / sizes;
	}

	return 1;
}

//중간 확인을 위한 함수
void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//위치를 전부확인하면서 연합이 가능한지 확인
int func() {
	//visit을 통해 연합을 통해 이미 연결된 곳이라면 
	// 계산 하지 않도록 함
	memset(visit, 0, sizeof(visit));
	//flag를 통해 연합이 됬는지 확인
	int flag = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visit[i][j] == 1)continue;
			if (solve({ i, j })) flag = 1;
		}
	}
	return flag;
}


int main() {
	input();
	int cnt = 0;

	//연합이 안될때 까지 확인
	while (func()) {
		//print();
		cnt++;
	}
	cout << cnt;
	return 0;
}