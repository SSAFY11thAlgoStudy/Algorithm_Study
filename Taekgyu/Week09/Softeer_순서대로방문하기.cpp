#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
using namespace std;
struct Pos
{
	int y;
	int x;
};
deque<Pos>pv;

int n;
int m;
int MAP[4][4];
int visited[4][4];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int endY = -1;
int endX = -1;
int ansCnt;

void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> MAP[i][j];
			// 장애물이면 미리 방문 처리해버리자
			if (MAP[i][j] == 1) {
				visited[i][j] = 1;
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		int y, x = 0;
		cin >> y >> x;
		pv.push_back({ y - 1,x - 1 });
	}
	// 도착지 설정
	endY = pv[m - 1].y;
	endX = pv[m - 1].x;
}

void func(int y, int x) {

	// 종료조건
	// 디큐의 사이즈가 0이다 => 경유지를 다 들린상태 이며
	// 종착지일때 종료한다

	if (pv.size() == 0 && y == endY && x == endX) {
		ansCnt++;
		return;
	}

	int nowy = y;
	int nowx = x;
	for (int d = 0; d < 4; d++)
	{
		int ny = nowy + dy[d];
		int nx = nowx + dx[d];

		if (ny >= n || nx >= n || ny < 0 || nx < 0) continue;
		if (MAP[ny][nx] == 1) continue;
		if (visited[ny][nx] == 1) continue;
		int pvY = pv[0].y;
		int pvX = pv[0].x;

		// 해당 칸이 순서에 맞는 경유지인 경우
		// 순서대로 조건을 만족하면 앞의 요소 삭제
		if (ny == pv[0].y && nx == pv[0].x) {
			pv.pop_front();
		}
		// 방문 체크
		visited[ny][nx] = 1;
		func(ny, nx);
		// 방문 체크 해제
		visited[ny][nx] = 0;

		// 전에 없앴던 경유지인경우 다시 추가
		if (ny == pvY && nx == pvX) {
			pv.push_front({ ny,nx });
		}
	}
}

int main() {

	input();
	// 출발지에서 재귀 돌린다.
	// 출발지 y, x 변수 설정
	int sy = pv[0].y;
	int sx = pv[0].x;
	// 출발지 방문체크
	visited[sy][sx] = 1;
	// 출발지 값 제거
	pv.pop_front();
	func(sy, sx);

	// 재귀 종료후 답 출력
	cout << ansCnt;
	return 0;
}