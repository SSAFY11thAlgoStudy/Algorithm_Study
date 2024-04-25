#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

// 5*5에서 3*3 격자를 선택하여 격자 회전 ㄱㄱ
// 선택된 격자는 시계방향으로 90도 180도 270도 중 하나의 각도만큼 회전
// 선택된 격자는 항상 회전을 진행

// 회전 목표
// 가능한 회전의 방법 중 유물 1차 획득 가치를 최대화하고,
// 그러한 방법이 여러가지인 경우
// 회전한 각도가 가장 작은 방법을 선택
// 그러한 경우도 여러가지면
// 회전 중심 좌표의 열이 가장 작은 구간,
// 열이 같다면 행이 가장 작은 구간을 선택
// 3*3 맵이 좌상단으로 가는 것이 목표

// 유물 획득
// 상하좌우로 인접한 같은 종류의 유물 조각
// 이 조각들이 3개 이상 연결된 경우
// 유물의 가치는 모인 조각의 개수

// 유물이 맵에서 사라짐
// 새롭게 생겨나는 조각에 대한 정보를 통해 맵 갱신
// 열이 작은순서
// 열이 같다면 행이 큰 순서대로 맵에 갱신

// 유물 연쇄 획득
// 새로운 유물 조각이 생겨난 이후에도 조각들이 3개이상 연결될 수 있다
// 그럼 다시 유물 획득 진행
// 3개이상 연결되지 않을경우에는 연쇄 끝
// 여기까지 1턴
struct Pos
{
	int y;
	int x;
};

// 어떤 정사각형을 돌릴지 판단하는 구조체
struct Desquare {
	int stY;
	int stX;
	int dir;
	int Relic;

	bool operator<(Desquare Right) const {
		if (Relic > Right.Relic)return true;
		if (Relic < Right.Relic)return false;

		if (dir < Right.dir)return true;
		if (dir > Right.dir)return false;

		if (stX < Right.stX)return true;
		if (stX > Right.stX)return false;

		if (stY < Right.stY)return true;
		if (stY > Right.stY)return false;
		return false;
	}
};

// 맵에 빈 공간에 유물을 채워넣을 순서 소트
bool compare(Pos left, Pos right) {
	if (left.x < right.x)return true;
	if (left.x > right.x)return false;

	if (left.y > right.y)return true;
	if (left.y < right.y)return false;
	return false;
}
vector<Desquare>ds;
vector<int>part;

int K, M;
int MAP[5][5];
int COPY[5][5];
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int Max;
int decY;
int decX;
int decDir;

int RelicValue;

void input() {
	cin >> K >> M;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < M; i++)
	{
		int Num;
		cin >> Num;
		part.push_back(Num);
	}
}

int getfrRelic() {
	// 정사각형을 선택할때 맵 전체의 유물 가치를 구하는 함수
	// 연쇄 작용 X
	// 이 함수는 단지 처음에 정사각형 정할때만 사용
	int visited[5][5] = { 0, };
	int MaxNum = 1;
	int totalRelic = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (visited[i][j] != 0)continue;
			queue<Pos>q;
			q.push({ i,j });
			visited[i][j] = 1;
			MaxNum = 1;
			while (!q.empty()) {
				Pos now = q.front();
				q.pop();
				for (int d = 0; d < 4; d++)
				{
					int ny = now.y + dy[d];
					int nx = now.x + dx[d];
					if (ny >= 5 || nx >= 5 || ny < 0 || nx < 0)continue;
					// 상하좌우에 지금 위치와 다른 유물이라면 플필 진행 X
					if (COPY[now.y][now.x] != COPY[ny][nx])continue;
					if (visited[ny][nx] != 0)continue;
					visited[ny][nx] = visited[now.y][now.x] + 1;
					MaxNum++;
					q.push({ ny,nx });
				}
			}
			// 특정 유물이 3개 이상 모여있다면 점수에 추가하라
			if (MaxNum >= 3) {
				totalRelic += MaxNum;
			}
		}
	}

	return totalRelic;
}

void turn(int stY, int stX, int dir) {
	// 5*5맵에서 3*3맵을 고르자
	// 총 9개의 정사각형을 고를수 있으며
	// 3가지의 턴 조건이 있음
	// 총 27번의 케이스 비교 진행
	// 중심축과 회전각도를 구해서 리턴해버리자

	// 시작점으로 시작하는 정사각형 복사
	memset(COPY, 0, sizeof(COPY));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			COPY[i][j] = MAP[i][j];
		}
	}

	int cpMAP[3][3] = { 0, };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cpMAP[i][j] = MAP[i + stY][j + stX];
		}
	}

	int turnMAP[3][3] = { 0, };
	// 90도 회전
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 90도 돌때
			if (dir == 0) {
				turnMAP[i][j] = cpMAP[2 - j][i];
			}
			// 180도 돌때
			else if (dir == 1) {
				turnMAP[i][j] = cpMAP[2 - i][2 - j];
			}
			// 270도 돌때
			else {
				turnMAP[i][j] = cpMAP[j][abs(2 - i)];
			}
		}
	}

	// 돌렸던 맵을 원래 맵에 넣자
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			COPY[i + stY][j + stX] = turnMAP[i][j];
		}
	}

	// 1차 획득 점수 계산
	int a = getfrRelic();
	// 점수가 3 이상인것만 추가
	// 27가지 케이스가 모두 3을 넘지 않는다면 ds 벡터의 크기는 0
	// 이러한 점을 main에서 flag역할로 사용
	if (a >= 3) {
		ds.push_back({ stY, stX, dir, a });
	}
}

void funcRelic(int stY, int stX, int dir) {
	// 본 함수 
	// 연쇄작용
	// 이젠 직접 MAP을 수정하면됨
	// 위의 함수에서는 COPY를 수정

	int cpMAP[3][3] = { 0, };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cpMAP[i][j] = MAP[i + stY][j + stX];
		}
	}

	int turnMAP[3][3] = { 0, };
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 90도 돌때
			if (dir == 0) {
				turnMAP[i][j] = cpMAP[2 - j][i];
			}
			// 180도 돌때
			else if (dir == 1) {
				turnMAP[i][j] = cpMAP[2 - i][2 - j];
			}
			// 270도 돌때
			else {
				turnMAP[i][j] = cpMAP[j][abs(2 - i)];
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			MAP[i + stY][j + stX] = turnMAP[i][j];
		}
	}

	while (true) {

		int visited[5][5] = { 0, };
		int MaxNum = 1;
		int totalRelic = 0;
		// 유물이 3개 이상인 케이스에만 위치 저장 벡터
		vector<Pos>getRelic;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (visited[i][j] != 0)continue;
				// 플필 돌면서 들렸던 위치 저장 queue
				queue<Pos>eR;
				queue<Pos>q;
				q.push({ i,j });
				eR.push({ i,j });
				visited[i][j] = 1;
				MaxNum = 1;
				while (!q.empty()) {
					Pos now = q.front();
					q.pop();
					for (int d = 0; d < 4; d++)
					{
						int ny = now.y + dy[d];
						int nx = now.x + dx[d];
						if (ny >= 5 || nx >= 5 || ny < 0 || nx < 0)continue;
						if (MAP[now.y][now.x] != MAP[ny][nx])continue;
						if (visited[ny][nx] != 0)continue;
						visited[ny][nx] = visited[now.y][now.x] + 1;
						MaxNum++;
						q.push({ ny,nx });
						eR.push({ ny,nx });
					}
				}
				// 유물이 3개 이상 있다면
				if (MaxNum >= 3) {
					// 점수 추가
					totalRelic += MaxNum;
					while (!eR.empty()) {
						Pos ps = eR.front();
						eR.pop();
						getRelic.push_back(ps);
					}
				}
			}
		}

		// 3개이상의 유물이 발견되지 않았다면 종료
		if (totalRelic == 0) {
			break;
		}
		// getRelic안에 담긴 위치들을 정렬한다.
		// 그럼 대기하고 있는 유물을 넣는 순서대로 정렬된다
		sort(getRelic.begin(), getRelic.end(), compare);
		for (int i = 0; i < getRelic.size(); i++)
		{
			// part벡터에서 앞에서 부터 맵으로 채운다
			MAP[getRelic[i].y][getRelic[i].x] = part[0];
			// 채우고 난 이후에는 part 첫번째 제거
			part.erase(part.begin(), part.begin() + 1);
		}
		// 총 점수 추가
		RelicValue += totalRelic;
	}
}


int main() {

	input();
	// k턴 반복
	for (int k = 0; k < K; k++)
	{
		// (2,2)부터 탐색하여 (0,0)까지 탐색
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 2; j >= 0; j--)
			{
				for (int d = 2; d >= 0; d--)
				{
					turn(i, j, d);
				}
			}
		}
		// ds가 없다면 지울수 있는 유물이 없다
		// 끝내라
		if (ds.size() == 0) {
			// 아무것도 출력하지 않는다
			cout << " ";
			break;
		}
		// 가장 회전각도가 적으며 유물 점수가 가장 큰 케이스를 뽑자
		sort(ds.begin(), ds.end());

		// 벡터의 가장 앞에 있는 구조체가
		// 정사각형의 시작점, 방향이다
		decY = ds[0].stY;
		decX = ds[0].stX;
		decDir = ds[0].dir;
		// 변수 저장하고 벡터 초기화
		ds.clear();

		// 이제 연쇄작용 함수로 본격적으로 들어가보자잇
		funcRelic(decY, decX, decDir);
		cout << RelicValue << " ";
		RelicValue = 0;
	}

	return 0;
}