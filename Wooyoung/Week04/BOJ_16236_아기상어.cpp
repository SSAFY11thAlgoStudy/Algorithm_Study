#include <iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;


int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };
int map[21][21];
int n;


// 상어의 시작 크기 2
// 상어는 자신의 크기 보다 작은 물고기를 먹을 수 있다.
// 상어는 자신의 크기와 같으면 먹지는 않고 지나갈 수는 있다.
// 자신의 크기와 같은 물고기 수를 먹어야 크기가 1 증가한다.
// ex) 크기가 2일 때, 크기가 1이하인 물고기 2마리를 먹기
// ex) 크기가 3일 때, 크기가 2이하인 물고기 3마리를 먹기

// 그렇다면 물고기와 아기상어의 좌표를 저장하고
// 물고기의 크기가 작은 순서부터 정렬한 후
// 먹을 수 있는 물고기를 다 먹었을 때
// 1. 자신의 크기만큼 먹었다면 크기 + 1
// 2. 자신의 크기만큼 먹지 못했다면 엄마 호출하기
// 3. 현재 맵에 물고기가 없으면? 엄마 호출하기

// 먹을 수 있는 물고기가 1마리 ? -> 그 물고기 먹기
// 먹을 수 있는 물고기가 여러마리 ?
// -> 거리가 가장 가까운 물고기 먹기
// 만약 거리가 가장 가까운 물고기가 많다면? 가장 위, 그래도 많다면? 가장 왼쪽
// !! 이는 입력받을 때 인덱스가 제일 작은 물고기의 좌표와 동일하다

// 그렇다면 각 물고기와의 거리를 구하고 
// 거리가 가장 가까운 물고기가 1마리면 그 물고기를 먹고
// 거리가 가장 가까운 물고기가 여러마리라면 
// 입력 번호(인덱스)가 작은 순서부터 먹으면 된다! 


vector<pair<int, int>>fish[7];
int s_y, s_x, s_size = 2;
int cur_dis, cur_eaten;
struct Info {
	int y, x, dis;
};



bool compare(Info a, Info b) {
	// 거리순
	if (a.dis != b.dis) {
		return a.dis < b.dis;
	}
	// 거리가 같다면 좌표 순
	else {
		if (a.y != b.y) {
			return a.y < b.y;
		}
		else {
			return a.x < b.x;
		}
	}
}

bool isValid(int y, int x) {
	return y >= 0 && x >= 0 && y < n&& x < n;
}

// 현재 상어의 좌표, 크기 사용
bool func() {
	// 현재 먹을 수 있는 물고기 탐색

	// 상어의 위치 
	queue<pair<int, int>>q;
	q.push({ s_y,s_x });
	int temp[21][21] = { 0, };
	temp[s_y][s_x] = -1;
	vector<Info>order_fish;

	// 상어가 맵을 1회 탐색
	while (!q.empty()) {
		int cur_y = q.front().first;
		int cur_x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int next_y = cur_y + dy[i];
			int next_x = cur_x + dx[i];
			// 영역 밖이거나, 이미 지나간 길이거나, 현재 상어 크기보다 큰 공간이면 진행 x
			if (!isValid(next_y, next_x) ||
				temp[next_y][next_x] != 0 ||
				map[next_y][next_x] > s_size)continue;

			// 큐에 추가
			q.push({ next_y,next_x });

			// 지나온 길이 저장
			if (temp[cur_y][cur_x] == -1)temp[next_y][next_x] = 1;
			else temp[next_y][next_x] = temp[cur_y][cur_x] + 1;

			// 현재 상어가 먹을 수 있는 물고기면?
			if (map[next_y][next_x] < s_size && map[next_y][next_x]>0) {
				// 물고기의 좌표와 현재 지나온 길이를 저장
				order_fish.push_back({ next_y,next_x,temp[next_y][next_x] });
			}

		}
	}

	// 1회 탐색 후 먹을 수 있는 물고기에 대해
	// 거리가 가까운 순, 가장 위에있는 순, 가장 왼쪽에 있는 순으로 물고기 정렬
	sort(order_fish.begin(), order_fish.end(), compare);

	// 더이상 먹을 수 있는 물고기가 없으면 종료 -> 엄마 호출하기
	if (order_fish.empty())return false;

	// 먹을 수 있는 물고기가 있으면 가장 앞에 저장된 물고기 먹고 함수 종료
	// 함수 종료 전 
		// 현재 먹은 물고기 위치에 상어 추가
		// 상어 시작 위치 0으로 교체
		// 현재 먹은 물고기 수 + 1, 
		// 현재 먹은 물고기 수가 현재 크기와 같은지 확인
		// 현재 이동거리 추가
	else {
		int goal_y = order_fish[0].y;
		int goal_x = order_fish[0].x;
		int goal_dis = order_fish[0].dis;
		map[s_y][s_x] = 0;
		map[goal_y][goal_x] = 9;
		s_y = goal_y;
		s_x = goal_x;
		cur_dis += goal_dis;
		cur_eaten++;
		if (cur_eaten == s_size) {
			s_size++;
			cur_eaten = 0;
		}
		//cout << goal_y << " " << goal_x << " " << goal_dis << "\n";
		return true;
	}


}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			// 물고기 입력 시 크기 별로 좌표 저장
			if (map[i][j] >= 1 && map[i][j] <= 6) {
				fish[map[i][j]].push_back({ i,j });
			}
			// 상어 입력 시 좌표 저장
			else if (map[i][j] == 9) {
				s_y = i;
				s_x = j;
			}
		}
	}

	// 가능한 시도
	for (int i = 0; i < n * n; i++) {
		// 더이상 먹을 물고기가 없으면 종료
		if (!func())break;
	}

	cout << cur_dis;

	return 0;
}