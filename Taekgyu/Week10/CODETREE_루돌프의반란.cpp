#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

struct Santa
{
	int Num;
	int y;
	int x;
	int dis;
	int Score;
	bool die;
	int down;

	bool operator<(Santa right) const {
		// �Ÿ��� ���� üũ
		if (dis < right.dis)return true;
		if (dis > right.dis)return false;

		// �Ÿ��� ���ٸ� �Ʒ��� �ִ��� üũ
		if (y > right.y)return true;
		if (y < right.y)return false;

		// ���� ���̶�� �����ʿ� �ִ��� üũ
		if (x > right.x)return true;
		if (x < right.x)return false;

		return false;
		// ��Ʈ��� 
		// ��������鼭 ���� �� �տ� �ִ� ��Ÿ�� ���� ����� �ȴ�.
	}
};

bool SeqOperater(Santa left, Santa right) {
	if (left.Num < right.Num)return true;
	if (left.Num > right.Num)return false;
	return false;
}

// ����ũ��
int N;
// ���� ����
int M;
// ��Ÿ��
int P;
// �絹���� ��
int C;
// ��Ÿ�� ��
int D;
// �� ����
int Turn;
int MAP[50][50];

// �絹���� ó�� ��ġ
int ruX;
int ruY;

// ��Ÿ���� ����
vector<Santa>Sv;

// ��Ÿ ���� ����
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

// ���� �Ǵ� �� ���⺤��
int findy[8] = { -1,-1,-1,0,1,1,1,0 };
int findx[8] = { -1,0,1,1,1,0,-1,-1 };

void input() {
	cin >> N >> M >> P >> C >> D;
	cin >> ruY >> ruX;
	ruY--;
	ruX--;
	for (int i = 1; i <= P; i++)
	{
		int Num, y, x = 0;
		cin >> Num >> y >> x;
		// ��Ÿ ���� �Է¹޴´�.
		Sv.push_back({ Num,y - 1,x - 1,99999,0, false, 0 });
	}
	// ��Ÿ ��ȣ ������� ���� ����
	sort(Sv.begin(), Sv.end(), SeqOperater);
}

void betEffet(int push, int dir) {
	// �ϴ� ��ȣ�ۿ��� ��Ÿ�� ��Ÿ ���̿��� �߻��Ѵ�.
	// push�� �з��� ��Ÿ �ε���
	// dir�� �и�����

	// push��° ��Ÿ�� �ش� �������� 1 �и���.
	Sv[push].y += findy[dir];
	Sv[push].x += findx[dir];

	// �зȴµ� �� ���̸� �׿���
	if (Sv[push].y >= N || Sv[push].x >= N || Sv[push].y < 0 || Sv[push].x < 0) {
		Sv[push].die = true;
	}

	// �и� ��ġ�� Ȥ�� �ٸ� ��Ÿ�� �� ��Ÿ�� �� �и���.
	// ����Լ� ���
	for (int i = 0; i < P; i++)
	{
		if (Sv[i].die)continue;
		if (i == push)continue;
		if (Sv[push].y == Sv[i].y && Sv[push].x == Sv[i].x) {
			betEffet(i, dir);
		}
	}
}

void Crash(int whoCrash, int Attack, int dir) {

	// �絹���� �ھ�����
	if (whoCrash == 1) {
		// �����Ѵ�
		// ���° �Ͽ� �����ϴ��� ���´�.
		// ���������� ������ Ǯ���� ���� �����Ѵ�.
		Sv[Attack].down = Turn + 2;
		// C��ŭ�� ������ ��´�.
		Sv[Attack].Score += C;
		// ���� �״�� ��Ÿ�� �з�����.
		for (int i = 0; i < C; i++)
		{
			Sv[Attack].y += findy[dir];
			Sv[Attack].x += findx[dir];
		}
		// �̵��� ��ġ�� �� ���̶�� �״´�.
		if (Sv[Attack].y >= N || Sv[Attack].x >= N || Sv[Attack].y < 0 || Sv[Attack].x < 0) {
			Sv[Attack].die = true;
		}
		// �̵��� ��ġ�� �ٸ� ��Ÿ�� ������~~~~
		// ��ȣ�ۿ��Ѵ�.
		for (int i = 0; i < P; i++)
		{
			if (i == Attack)continue;
			if (Sv[i].y == Sv[Attack].y && Sv[i].x == Sv[Attack].x) {
				betEffet(i, dir);
			}
		}
	}
	// ��Ÿ�� �ھ�����
	else {
		// �����Ѵ�
		// ���° �Ͽ� �����ϴ��� ���´�.
		// ���������� ������ Ǯ���� ���� �����Ѵ�.
		Sv[Attack].down = Turn + 2;
		// D��ŭ�� ������ ��´�.
		Sv[Attack].Score += D;
		// ���� ������ �ݴ�� �����Ѵ�.
		int reverseDir = (dir + 4) % 8;
		for (int i = 0; i < D - 1; i++)
		{
			Sv[Attack].y += findy[reverseDir];
			Sv[Attack].x += findx[reverseDir];
		}
		// �̵��� ��ġ�� �� ���̶�� �״´�.
		if (Sv[Attack].y >= N || Sv[Attack].x >= N || Sv[Attack].y < 0 || Sv[Attack].x < 0) {
			Sv[Attack].die = true;
		}
		// �̵��� ��ġ�� �ٸ� ��Ÿ�� ������~~~~
		// ��ȣ�ۿ��Ѵ�.
		for (int i = 0; i < P; i++)
		{
			if (i == Attack)continue;
			if (Sv[i].y == Sv[Attack].y && Sv[i].x == Sv[Attack].x) {
				betEffet(i, reverseDir);
			}
		}
	}
}

void moveDear() {

	int Savedir = 0;
	// ���� ����� ��Ÿ�� ���� �����δ�.
	// ���� �絹������ �Ÿ��� �� �����Ѵ�.
	// ���� ��Ÿ����� ������ ��Ÿ���״� ����.
	for (int i = 0; i < Sv.size(); i++)
	{
		if (Sv[i].die)continue;
		int Dis = (ruY - Sv[i].y) * (ruY - Sv[i].y) + (ruX - Sv[i].x) * (ruX - Sv[i].x);
		Sv[i].dis = Dis;
	}

	// ���� ����� �����ϱ� ���� sort
	sort(Sv.begin(), Sv.end());

	int targetY = 0;
	int targetX = 0;
	int Saveint = 0;

	// ���� ��� ���ϱ�
	for (int i = 0; i < P; i++)
	{
		if (Sv[i].die)continue;
		Saveint = i;
		targetY = Sv[i].y;
		targetX = Sv[i].x;
		break;
	}

	// ���⺤�� ���� ������ 0
	// y, x ���� �ϳ��� ���� �� �ִ� => �������� �̵�
	if (targetY == ruY || targetX == ruX) {
		if (targetX == ruX) {
			if (targetY < ruY) {
				Savedir = 1;
				ruY--;
			}
			else {
				Savedir = 5;
				ruY++;
			}
		}
		else if (targetY == ruY) {
			if (targetX < ruX) {
				Savedir = 7;
				ruX--;
			}
			else {
				Savedir = 3;
				ruX++;
			}
		}
	}
	// �ٸ��� => �밢������ �̵�
	else {
		// ��������� 1��и鿡 �ִ� (y�� �۰� x�� ũ��)
		if (targetY < ruY && targetX > ruX) {
			ruY--;
			ruX++;
			Savedir = 2;
		}
		// ��������� 2��и鿡 �ִ� (y�� ũ�� x�� ũ��)
		else if (targetY > ruY && targetX > ruX) {
			ruY++;
			ruX++;
			Savedir = 4;
		}
		// ��������� 3��и鿡 �ִ� (y�� ũ�� x�� �۴�)
		else if (targetY > ruY && targetX < ruX) {
			ruY++;
			ruX--;
			Savedir = 6;
		}
		// ��������� 4��и鿡 �ִ� (y�� �۰� x�� �۴�)
		else if (targetY < ruY && targetX < ruX) {
			ruY--;
			ruX--;
			Savedir = 0;
		}
	}

	// �̵��� ��ġ�� ������󿡰� �浹�ߴ��� �Ǵ�
	// �浹�ߴٸ�
	if (ruY == targetY && ruX == targetX) {
		// �絹���� ���� �ھҴٸ� => 1
		// ��Ÿ�� ���� �ھҴٸ� => 0
		// 1, 0�� �ǹ� �絹���� 0��°�� ��Ÿ�� �ھҴ�.
		Crash(1, Saveint, Savedir);
	}
}

void moveSanta() {

	// �ϴ� ��Ÿ�� �ʿ� �Ѹ���.
	memset(MAP, 0, sizeof(MAP));
	for (int i = 0; i < P; i++)
	{
		// ���� ��Ÿ�� continue;
		if (Sv[i].die)continue;
		MAP[Sv[i].y][Sv[i].x] = 1;
	}

	sort(Sv.begin(), Sv.end(), SeqOperater);
	// ��Ÿ����ŭ �ݺ�
	// 1������ P������ �ݺ�
	// �׷��� ~ �����ϰų� ���� ��Ÿ�� continue~

	for (int i = 0; i < P; i++)
	{
		// �������ִ� ��Ÿ�� continue;
		if (Sv[i].down > Turn)continue;
		// ���� ��Ÿ�� continue;
		if (Sv[i].die)continue;

		int Mindis = 21e8;
		// 4������ ���鼭 �絹�������� 4���� ������ ���� �Ÿ��� ���Ѵ�
		// ���� ���� ���� �Ÿ��� �����Ѵ�.
		// ���� ��ġ���� �Ÿ� ���
		int nowDis = (Sv[i].y - ruY) * (Sv[i].y - ruY) + (Sv[i].x - ruX) * (Sv[i].x - ruX);
		Mindis = nowDis;
		for (int d = 0; d < 4; d++)
		{
			int ny = Sv[i].y + dy[d];
			int nx = Sv[i].x + dx[d];
			if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
			if (MAP[ny][nx] == 1)continue;
			int resdis = (ruY - ny) * (ruY - ny) + (ruX - nx) * (ruX - nx);
			Mindis = min(Mindis, resdis);
		}
		// 4������ ���鼭 ���� ���� ���� �Ÿ��� ����Ѵ�.
		// ������ ��Ÿ�� �ְų� �� ���̸� ���� �ʴ´�.
		for (int d = 0; d < 4; d++)
		{
			int ny = Sv[i].y + dy[d];
			int nx = Sv[i].x + dx[d];
			if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
			// ��Ÿ�� �ִٸ� ��������
			if (MAP[ny][nx] == 1)continue;
			int resdis = (ruY - ny) * (ruY - ny) + (ruX - nx) * (ruX - nx);
			if (Mindis != resdis)continue;

			// ���� ����ġ�⸦ ����ߴٸ� �̵��ϰ� break;
			// ������ �� ��ġ�� �絹����� �浹�ϰ� ���� ��ġ ����
			if (ny == ruY && nx == ruX) {

				Crash(0, i, d * 2 + 1);
				// �� ����
				memset(MAP, 0, sizeof(MAP));
				for (int i = 0; i < P; i++)
				{
					if (Sv[i].die)continue;
					MAP[Sv[i].y][Sv[i].x] = 1;
				}
			}
			// �絹�� �Ⱥ΋H���� �� ���� ���ص� �Ǳ�����
			else {
				MAP[ny][nx] = 1;
				MAP[Sv[i].y][Sv[i].x] = 0;
				Sv[i].y = ny;
				Sv[i].x = nx;
			}
			break;
		}
	}
}

int main() {

	input();
	for (int i = 0; i < M; i++)
	{
		// �絹������ ��������
		moveDear();
		// �� ���� ��Ÿ�� �̵�
		moveSanta();
		int dieCnt = 0;
		for (int i = 0; i < P; i++)
		{
			if (Sv[i].die) {
				dieCnt++;
				continue;
			}
			Sv[i].Score++;
		}
		// ��Ÿ�� �� �׾����� �� �̻� ���ʿ� X
		if (dieCnt == P) {
			break;
		}
		Turn++;
	}
	sort(Sv.begin(), Sv.end(), SeqOperater);
	for (int i = 0; i < P; i++)
	{
		cout << Sv[i].Score << " ";
	}

	return 0;
}