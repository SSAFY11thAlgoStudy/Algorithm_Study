#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

using namespace std;

queue<pair<int, int>>q;


int N, K;//보드의 크기, 사과의 개수
int MAP[120][120];// MAP선언
int y, x;//사과 좌표
int L;// 방향변환 횟수
int dirY;
int dirX = 1; //처음은 오른쪽으로 진행
int DAT[99999]; //cnt를 넣었으니까 크게 잡아줘
char dirDAT[99999];
int ny, nx; //다음 좌표
int cnt; //시간

void init() {
	// 전역변수 초기화
	memset(MAP, 0, sizeof(MAP));
	memset(DAT, 0, sizeof(DAT));
	memset(dirDAT, 0, sizeof(dirDAT));
	cnt = 0;
}

int func(int nowY, int nowX) {

	// 방향 설정
	if (DAT[cnt] != 0) {
		// 현재 오른쪽으로 진행할 때
		if (dirY == 0 && dirX == 1 && dirDAT[cnt] == 'D') {
			dirY = 1;
			dirX = 0;
		}
		else if (dirY == 0 && dirX == 1 && dirDAT[cnt] == 'L') {
			dirY = -1;
			dirX = 0;
		}
		// 현재 아래로 진행할 때
		else if (dirY == 1 && dirX == 0 && dirDAT[cnt] == 'D') {
			dirY = 0;
			dirX = -1;
		}
		else if (dirY == 1 && dirX == 0 && dirDAT[cnt] == 'L') {
			dirY = 0;
			dirX = 1;
		}
		// 현재 위로 진행할 때
		else if (dirY == -1 && dirX == 0 && dirDAT[cnt] == 'D') {
			dirY = 0;
			dirX = 1;
		}
		else if (dirY == -1 && dirX == 0 && dirDAT[cnt] == 'L') {
			dirY = 0;
			dirX = -1;
		}
		// 현재 왼쪽으로 진행할 때
		else if (dirY == 0 && dirX == -1 && dirDAT[cnt] == 'D') {
			dirY = -1;
			dirX = 0;
		}
		else if (dirY == 0 && dirX == -1 && dirDAT[cnt] == 'L') {
			dirY = 1;
			dirX = 0;
		}
	}
	cnt++;
	ny = nowY + dirY;
	nx = nowX + dirX;

	//맵 밖으로 나가면 종료
	if (ny >= N || nx >= N || ny < 0 || nx < 0) {
		return cnt;
	}
	else {
		//사과를 먹었을 경우
		if (MAP[ny][nx] == 2) {
			// 큐에 머리 위치 저장
			q.push({ ny,nx });
			// 뱀 흔적 남기기
			MAP[ny][nx] = 1;
		}
		//먹지 않았을 경우
		else {
			// 큐에 머리 위치 저장
			q.push({ ny,nx });
			// 자신의 몸에 닿았을 경우
			if (MAP[ny][nx] == 1) {
				return cnt;
			}
			// 뱀 흔적 남기기
			MAP[ny][nx] = 1;
			// 꼬리 자르기
			MAP[q.front().first][q.front().second] = 0;
			q.pop();
		}
		func(ny, nx);
		return cnt;
	}
}

int main()
{
	init();
	cin >> N >> K;
	for (int i = 0; i < K; i++)
	{
		cin >> y >> x;
		MAP[y - 1][x - 1] = 2;//사과 위치 2로 표현
	}
	cin >> L;
	for (int i = 0; i < L; i++)
	{
		int Num = 0;
		char C = 0;
		cin >> Num >> C;
		DAT[Num] = 1;
		dirDAT[Num] = C;
	}
	q.push({ 0,0 });//시작점 push
	func(0, 0);
	cout << cnt;
	return 0;
}