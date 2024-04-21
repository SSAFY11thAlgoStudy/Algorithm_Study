#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

// 5*5���� 3*3 ���ڸ� �����Ͽ� ���� ȸ�� ����
// ���õ� ���ڴ� �ð�������� 90�� 180�� 270�� �� �ϳ��� ������ŭ ȸ��
// ���õ� ���ڴ� �׻� ȸ���� ����

// ȸ�� ��ǥ
// ������ ȸ���� ��� �� ���� 1�� ȹ�� ��ġ�� �ִ�ȭ�ϰ�,
// �׷��� ����� ���������� ���
// ȸ���� ������ ���� ���� ����� ����
// �׷��� ��쵵 ����������
// ȸ�� �߽� ��ǥ�� ���� ���� ���� ����,
// ���� ���ٸ� ���� ���� ���� ������ ����
// 3*3 ���� �»������ ���� ���� ��ǥ

// ���� ȹ��
// �����¿�� ������ ���� ������ ���� ����
// �� �������� 3�� �̻� ����� ���
// ������ ��ġ�� ���� ������ ����

// ������ �ʿ��� �����
// ���Ӱ� ���ܳ��� ������ ���� ������ ���� �� ����
// ���� ��������
// ���� ���ٸ� ���� ū ������� �ʿ� ����

// ���� ���� ȹ��
// ���ο� ���� ������ ���ܳ� ���Ŀ��� �������� 3���̻� ����� �� �ִ�
// �׷� �ٽ� ���� ȹ�� ����
// 3���̻� ������� ������쿡�� ���� ��
// ������� 1��
struct Pos
{
	int y;
	int x;
};

// � ���簢���� ������ �Ǵ��ϴ� ����ü
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

// �ʿ� �� ������ ������ ä������ ���� ��Ʈ
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
	// ���簢���� �����Ҷ� �� ��ü�� ���� ��ġ�� ���ϴ� �Լ�
	// ���� �ۿ� X
	// �� �Լ��� ���� ó���� ���簢�� ���Ҷ��� ���
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
					// �����¿쿡 ���� ��ġ�� �ٸ� �����̶�� ���� ���� X
					if (COPY[now.y][now.x] != COPY[ny][nx])continue;
					if (visited[ny][nx] != 0)continue;
					visited[ny][nx] = visited[now.y][now.x] + 1;
					MaxNum++;
					q.push({ ny,nx });
				}
			}
			// Ư�� ������ 3�� �̻� ���ִٸ� ������ �߰��϶�
			if (MaxNum >= 3) {
				totalRelic += MaxNum;
			}
		}
	}

	return totalRelic;
}

void turn(int stY, int stX, int dir) {
	// 5*5�ʿ��� 3*3���� ����
	// �� 9���� ���簢���� ���� ������
	// 3������ �� ������ ����
	// �� 27���� ���̽� �� ����
	// �߽���� ȸ�������� ���ؼ� �����ع�����

	// ���������� �����ϴ� ���簢�� ����
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
	// 90�� ȸ��
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// 90�� ����
			if (dir == 0) {
				turnMAP[i][j] = cpMAP[2 - j][i];
			}
			// 180�� ����
			else if (dir == 1) {
				turnMAP[i][j] = cpMAP[2 - i][2 - j];
			}
			// 270�� ����
			else {
				turnMAP[i][j] = cpMAP[j][abs(2 - i)];
			}
		}
	}

	// ���ȴ� ���� ���� �ʿ� ����
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			COPY[i + stY][j + stX] = turnMAP[i][j];
		}
	}

	// 1�� ȹ�� ���� ���
	int a = getfrRelic();
	// ������ 3 �̻��ΰ͸� �߰�
	// 27���� ���̽��� ��� 3�� ���� �ʴ´ٸ� ds ������ ũ��� 0
	// �̷��� ���� main���� flag���ҷ� ���
	if (a >= 3) {
		ds.push_back({ stY, stX, dir, a });
	}
}

void funcRelic(int stY, int stX, int dir) {
	// �� �Լ� 
	// �����ۿ�
	// ���� ���� MAP�� �����ϸ��
	// ���� �Լ������� COPY�� ����

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
			// 90�� ����
			if (dir == 0) {
				turnMAP[i][j] = cpMAP[2 - j][i];
			}
			// 180�� ����
			else if (dir == 1) {
				turnMAP[i][j] = cpMAP[2 - i][2 - j];
			}
			// 270�� ����
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
		// ������ 3�� �̻��� ���̽����� ��ġ ���� ����
		vector<Pos>getRelic;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (visited[i][j] != 0)continue;
				// ���� ���鼭 ��ȴ� ��ġ ���� queue
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
				// ������ 3�� �̻� �ִٸ�
				if (MaxNum >= 3) {
					// ���� �߰�
					totalRelic += MaxNum;
					while (!eR.empty()) {
						Pos ps = eR.front();
						eR.pop();
						getRelic.push_back(ps);
					}
				}
			}
		}

		// 3���̻��� ������ �߰ߵ��� �ʾҴٸ� ����
		if (totalRelic == 0) {
			break;
		}
		// getRelic�ȿ� ��� ��ġ���� �����Ѵ�.
		// �׷� ����ϰ� �ִ� ������ �ִ� ������� ���ĵȴ�
		sort(getRelic.begin(), getRelic.end(), compare);
		for (int i = 0; i < getRelic.size(); i++)
		{
			// part���Ϳ��� �տ��� ���� ������ ä���
			MAP[getRelic[i].y][getRelic[i].x] = part[0];
			// ä��� �� ���Ŀ��� part ù��° ����
			part.erase(part.begin(), part.begin() + 1);
		}
		// �� ���� �߰�
		RelicValue += totalRelic;
	}
}


int main() {

	input();
	// k�� �ݺ�
	for (int k = 0; k < K; k++)
	{
		// (2,2)���� Ž���Ͽ� (0,0)���� Ž��
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
		// ds�� ���ٸ� ����� �ִ� ������ ����
		// ������
		if (ds.size() == 0) {
			// �ƹ��͵� ������� �ʴ´�
			cout << " ";
			break;
		}
		// ���� ȸ�������� ������ ���� ������ ���� ū ���̽��� ����
		sort(ds.begin(), ds.end());

		// ������ ���� �տ� �ִ� ����ü��
		// ���簢���� ������, �����̴�
		decY = ds[0].stY;
		decX = ds[0].stX;
		decDir = ds[0].dir;
		// ���� �����ϰ� ���� �ʱ�ȭ
		ds.clear();

		// ���� �����ۿ� �Լ��� ���������� ��������
		funcRelic(decY, decX, decDir);
		cout << RelicValue << " ";
		RelicValue = 0;
	}

	return 0;
}