#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

int H, W;
char MAP[25][25];
int visited[25][25];
vector<char>order;
int frDir;
int routeCnt;
int noWay;
int nowDir;
int dy[4] = { -2,0,2,0 };
int dx[4] = { 0,2,0,-2 };

// 정답 출력 필요 변수
int Size = 21e8;
int ansy;
int ansx;
int ansdir;
string ansStr;

void input() {
	cin >> H >> W;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> MAP[i][j];
			if (MAP[i][j] == '#') {
				routeCnt++;
			}
		}
	}
}

void func(int y, int x, int dir) {
	// 새로운 좌표와 방향이 들어왔으므로 초기화
	order.clear();
	memset(visited, 0, sizeof(visited));
	int nowy = y;
	int nowx = x;
	visited[y][x] = 1;
	// vCnt는 #이 적혀진 길을 가면 증가
	int vCnt = 1;
	// 초기 방향 저장
	frDir = dir;
	while (true) {

		// # 을 모두 방문했다면 종료
		if (vCnt == routeCnt) {
			break;
		}
		// 아직 #을 모두 방문하지 않았는데 못가는 경우
		if (noWay == 4) {
			// 사수가 한번은 움직였으므로
			// 벡터를 초기화 시키면서 flag 역할 수행
			order.clear();
			noWay = 0;
			break;
		}
		noWay = 0;
		for (int d = 0; d < 4; d++)
		{
			nowDir = d;
			// 두칸 움직인 다음 좌표
			int ny = nowy + dy[d];
			int nx = nowx + dx[d];
			// 한칸 움직인 다음 좌표
			int hy = nowy + dy[d] / 2;
			int hx = nowx + dx[d] / 2;
			// 맵을 벗어나면 가지마라
			if (ny >= H || nx >= W || ny < 0 || nx < 0) {
				noWay++;
				continue;
			}
			// 이미 갔던 곳은 가지마라
			if (visited[hy][hx] == 1 || visited[ny][nx] == 1) {
				noWay++;
				continue;
			}
			// 사수가 조종했을때 안갔던 곳이면 가지마라
			if (MAP[hy][hx] == '.' || MAP[ny][nx] == '.') {
				noWay++;
				continue;
			}

			// 전 방향과 비교하여 오더에 추가
			if (frDir != nowDir) {
				//오른쪽으로 틀었을 때
				if ((frDir + 1) % 4 == nowDir) {
					order.push_back('R');
				}
				//왼쪽으로 틀었을 때
				else {
					order.push_back('L');
				}
				//현재 상태의 방향을 저장
				frDir = nowDir;
			}
			// 가지치기를 통과하면 무조건 직진 수행
			order.push_back('A');
			visited[ny][nx] = 1;
			visited[hy][hx] = 1;
			vCnt += 2;
			nowy = ny;
			nowx = nx;
		}
	}
}

int main() {
	//freopen("sample_input.txt", "r", stdin);
	input();

	// bfs로 풀자
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (MAP[i][j] == '#') {
				for (int d = 0; d < 4; d++)
				{
					int ny = i + dy[d];
					int nx = j + dx[d];
					// 로봇을 놓을 수 있는 위치와 방향을 골라 bfs 들어가자
					if (MAP[ny][nx] == '#')
						func(i, j, d);

					// #을 다 통과했다면
					if (order.size() != 0) {
						// 벡터사이즈가 전과 비교해서 작다면 저장
						if (order.size() < Size) {
							Size = order.size();
							ansy = i;
							ansx = j;
							ansdir = d;
							ansStr = "";
							for (int k = 0; k < order.size(); k++)
							{
								ansStr += order[k];
							}
						}
					}
				}
			}
		}
	}
	// 출력 부분
	cout << ansy + 1 << " " << ansx + 1 << endl;;
	if (ansdir == 0) {
		cout << '^';
	}
	else if (ansdir == 1) {
		cout << '>';
	}
	else if (ansdir == 2) {
		cout << 'v';
	}
	else {
		cout << '<';
	}
	cout << endl << ansStr;

	return 0;
}