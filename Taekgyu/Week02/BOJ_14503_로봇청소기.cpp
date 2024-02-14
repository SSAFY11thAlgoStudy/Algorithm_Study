#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

struct pos {
	int y;
	int x;
};

int N, M;
int r, c;
int d;
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int MAP[50][50];
int No;
int go;
int cnt;
int flag;

// 현재 바라보는 방향
int nowDir;
// 현재 위치
pos now = { 0 };
// 각도 수정 위치
pos Turn = { 0 };

void init() {
	memset(MAP, 0, sizeof(MAP));
	flag = 0;
}

void solution(pos st) {

	// 청소한 곳 8로 표시
	if (MAP[st.y][st.x] != 8) {
		MAP[st.y][st.x] = 8;
		//cout << "cnt증가";
		cnt++;
	}
	//네 방향에 청소할 곳이 있는지 확인하는 변수 No
	No = 0;
	for (int i = 0; i < 4; i++)
	{
		pos next = { 0 };
		next.y = st.y + dy[i];
		next.x = st.x + dx[i];

		// 청소를 했거나 벽이면 증가
		if (MAP[next.y][next.x] == 8 || MAP[next.y][next.x] == 1) {
			No++;
		}
	}
	// 청소되지 않은 빈칸이 없는 경우
	if (No == 4) {
		int SelectBack = 0;
		// 후진 방향 설정
		if (nowDir == 0)SelectBack = 2;
		if (nowDir == 1)SelectBack = 3;
		if (nowDir == 2)SelectBack = 0;
		if (nowDir == 3)SelectBack = 1;

		pos Back = { 0 };
		Back.y = st.y + dy[SelectBack];
		Back.x = st.x + dx[SelectBack];

		// 후진 했을 때 벽이면 끝내라~
		if (MAP[Back.y][Back.x] == 1) {
			flag = 1;
			return;
		}

		// 후진 했을 때 청소한곳이면 일단 가봐
		if (MAP[Back.y][Back.x] == 8) {
			now.y = Back.y;
			now.x = Back.x;
			solution(now);
		}
	}
	//청소되지 않은 빈칸이 있는 경우
	else {
		int TurnDir = nowDir;
		// 반시계 방향 0 -> 3 -> 2 -> 1
		// 따라서 0일때는 3으로 회전
		if (TurnDir == 0) {
			TurnDir = 3;
		}
		// 0이 아닐때는 -1
		else {
			TurnDir--;
		}
		TurnDir = TurnDir % 4;
		Turn.y = st.y + dy[TurnDir];
		Turn.x = st.x + dx[TurnDir];

		// 청소 안한 곳 찾을때까지 돌아라~
		while (true) {
			if (flag == 1) {
				return;
			}
			// 청소가 안된 곳이라면 가라~
			if (MAP[Turn.y][Turn.x] == 0) {
				now.y = Turn.y;
				now.x = Turn.x;
				nowDir = TurnDir;
				solution(now);
			}

			if (TurnDir == 0) {
				TurnDir = 3;
			}
			else {
				TurnDir--;
			}
			TurnDir = TurnDir % 4;
			nowDir = TurnDir;
			Turn.y = st.y + dy[TurnDir];
			Turn.x = st.x + dx[TurnDir];

		}
	}
}


int main()
{

	//freopen("sample_input.txt", "r", stdin);

	cin >> N >> M;
	cin >> r >> c >> d;

	init();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			// 0인 경우 청소 X
			// 1인 경우 벽
			cin >> MAP[i][j];
		}
	}
	// 현재 방향 변수
	nowDir = d;
	solution({ r,c });
	cout << cnt;
	return 0;
}

// 시뮬레이션 코딩
// 문제에서 하란대로 하면 풀린다.
// 반시계 방향대로 돌기위해서 방향배열 헷갈리지 말기