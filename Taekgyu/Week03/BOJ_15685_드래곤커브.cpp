#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
#include<queue>

using namespace std;

int N;
int x, y, d, g;
int MAP[110][110];
int cnt;
int ansCnt;

// 방향 인덱스에 맞게 방향 배열 설정
int dy[4] = { 0,-1,0,1 };
int dx[4] = { 1,0,-1,0 };

// 디큐를 활용하여 방향변수 저장
deque<int>Aq;

// 초기화 코드
void init() {
	memset(MAP, 0, sizeof(MAP));
	ansCnt = 0;
	cnt = 0;
	Aq.clear();
}

// 드래곤 커브를 그리자!
void DragonCurve() {
	// 처음 시작점 찍기
	MAP[y][x] = 1;

	// Aq라는 디큐에 방향변수 저장
	Aq.push_back(d);

	// 드래곤 커브 규칙을 활용하여 세대만큼 디큐 갱신
	// 방향변수 0으로 시작
	// 0세대 0
	// 1세대 0 -> 1
	// 2세대 0 1 -> 2 1
	// 3세대 0 1 2 1 -> 2 3 2 1
	// 알 수 있는 규칙 : 전 세대의 디큐에서 마지막 부터 추출 후 +1을 해서 추가해라~~~

	for (int i = 0; i < g; i++)
	{
		deque<int>copyQ(Aq);
		// 전 세대의 방향변수들 복사
		int qsize = copyQ.size();
		for (int j = 0; j < qsize; j++)
		{
			int qBack = copyQ.back();
			copyQ.pop_back();
			// 뒤에서부터 하나씩 빼서 +1 후 추가
			Aq.push_back((qBack + 1) % 4);
		}
	}

	// 저장된 방향 디큐에 맞게 맵에 그리자~
	int qsize = Aq.size();
	for (int i = 0; i < qsize; i++)
	{
		int dir = Aq.front();
		Aq.pop_front();
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		MAP[ny][nx] = 1;
		y = ny;
		x = nx;
	}
}

// 드래곤 커브 다 그린후 정사각형 개수 판단
int squareCheck() {

	// 좌표에 맞게 그렸기 때문에
	// 2*2 크기의 정사각형 마다 계산
	// 예 : (0,0)의 배열값이 1이면 (0,0)꼭짓점으로 드래곤 커브가 지나간다.
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			cnt = MAP[i][j] + MAP[i + 1][j] + MAP[i][j + 1] + MAP[i + 1][j + 1];
			if (cnt == 4) {
				ansCnt++;
				cnt = 0;
			}
		}
		cnt = 0;
	}
	return ansCnt;
}

int main()
{
	init();
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		cin >> x >> y >> d >> g;
		DragonCurve();
	}
	int Ans = squareCheck();
	cout << Ans;
	return 0;
}