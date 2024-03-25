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

// ���� ��� �ʿ� ����
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
	// ���ο� ��ǥ�� ������ �������Ƿ� �ʱ�ȭ
	order.clear();
	memset(visited, 0, sizeof(visited));
	int nowy = y;
	int nowx = x;
	visited[y][x] = 1;
	// vCnt�� #�� ������ ���� ���� ����
	int vCnt = 1;
	// �ʱ� ���� ����
	frDir = dir;
	while (true) {

		// # �� ��� �湮�ߴٸ� ����
		if (vCnt == routeCnt) {
			break;
		}
		// ���� #�� ��� �湮���� �ʾҴµ� ������ ���
		if (noWay == 4) {
			// ����� �ѹ��� ���������Ƿ�
			// ���͸� �ʱ�ȭ ��Ű�鼭 flag ���� ����
			order.clear();
			noWay = 0;
			break;
		}
		noWay = 0;
		for (int d = 0; d < 4; d++)
		{
			nowDir = d;
			// ��ĭ ������ ���� ��ǥ
			int ny = nowy + dy[d];
			int nx = nowx + dx[d];
			// ��ĭ ������ ���� ��ǥ
			int hy = nowy + dy[d] / 2;
			int hx = nowx + dx[d] / 2;
			// ���� ����� ��������
			if (ny >= H || nx >= W || ny < 0 || nx < 0) {
				noWay++;
				continue;
			}
			// �̹� ���� ���� ��������
			if (visited[hy][hx] == 1 || visited[ny][nx] == 1) {
				noWay++;
				continue;
			}
			// ����� ���������� �Ȱ��� ���̸� ��������
			if (MAP[hy][hx] == '.' || MAP[ny][nx] == '.') {
				noWay++;
				continue;
			}

			// �� ����� ���Ͽ� ������ �߰�
			if (frDir != nowDir) {
				//���������� Ʋ���� ��
				if ((frDir + 1) % 4 == nowDir) {
					order.push_back('R');
				}
				//�������� Ʋ���� ��
				else {
					order.push_back('L');
				}
				//���� ������ ������ ����
				frDir = nowDir;
			}
			// ����ġ�⸦ ����ϸ� ������ ���� ����
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

	// bfs�� Ǯ��
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (MAP[i][j] == '#') {
				for (int d = 0; d < 4; d++)
				{
					int ny = i + dy[d];
					int nx = j + dx[d];
					// �κ��� ���� �� �ִ� ��ġ�� ������ ��� bfs ����
					if (MAP[ny][nx] == '#')
						func(i, j, d);

					// #�� �� ����ߴٸ�
					if (order.size() != 0) {
						// ���ͻ���� ���� ���ؼ� �۴ٸ� ����
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
	// ��� �κ�
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