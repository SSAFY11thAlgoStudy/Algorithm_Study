#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;

// N*N���ڿ��� ����
// ������ ���ڿ��� ������� ����
// �ʱ⿡ �÷��̾���� ���Ⱑ ���� �� ���ڿ� ��ġ�ϸ� �ʱ�ɷ�ġ�� ����
// ����� ����� �÷��̾��� ��ȣ
// ������ ����� �ʱ� �ɷ�ġ
// ���ε� ������ ����� ���ݷ�

// ������ ���ϰ� �ִ� ������ ��ĭ ����
// �װ� ���࿡ �� ������ ����ٸ�
// ���� 180 Ʋ�� 1ĭ ����
// �ϴ� �ľ�
// ���� ��ǥ�� �� ������ �ƴ���
// �� ���̶�� ����Ʋ�� �ϳ� ����
// �� ���̶�� �׳� �ϳ� ����

// ���� ��ġ������ �̺�Ʈ
// �ش� ĭ�� �����ִ��� Ȯ��
// ���� �ִ� ��� ���� ȹ��
// �ٵ� ���� ���� �̹� ������ �ִٸ� 
// �� �� ���� ��� 
// �� ���� �� ĭ�� ������.

// �÷��̾���� ������� �����ϸ鼭
// ���� ĭ���� ������ ���� �ο��.
// �� ���ݷ��� ���Ͽ� �� ū �÷��̾ �̱��
// �� ��ġ�� ���� ��쿡�� �ʱ� �ɷ�ġ�� ���� �÷��̾ �̱��.
// �̱� �÷��̾�� ��� �÷��̾���� ���ݷ� ���� ��ŭ ������ ��´�.

// �� �÷��̾�� ������ �ִ� ���� �ش� ���ڿ� ��������
// �ش� �÷��̾ ���� ������ �ִ� ������ ��ĭ ����
// ���� �̵��Ϸ��� ĭ�� �ٸ� �÷��̾ �ִ� ����
// ���� ���� ��쿡�� ���������� 90���� ȸ���Ͽ� ��ĭ�� ���̴� ���� �̵�

// ��� Ǯ���ΰ�?
// 1. �Է¹ޱ�
// 2. �÷��̾� �����Է�
// 3. ���� ���� �Է�
// 4. ���� ��ġ�� ���� ���Ѻ��� �ε��� ����
// 5. ������� �̵� ( ���� ���Ƴ���� ���� ���� ) -> �÷��̾ ������ ��� ���� �� ������ ��� �����Ұ��ΰ�?
// �ϴ� ������ ������ �ش� ���� ���� ����
// �׸��� ������ ������Ʈ �ϴ� �������� totalPower���� Power�� �� ���� ����ִ� ���ѿ� �ش��Ѵ�.
// �÷��̾ �ִ� ��ġ ������ Ȱ���Ͽ� ���� ���Ϳ� �߰�
// �׷� ���� ���Ͱ� ĭ���� �ϳ� �̻� ���� �� �ִ�.
// �׷� �� ĭ�� �ش��ϴ� ���� ������ŭ ������ ( �� �߿� ū ���� ���� )
// 6. fight �Լ� ���� ( ���� ������ �ٸ� �÷��̾ ������ )
// 7. ���ڴ� defeat �Լ��� �� ( ���� ���� �̵� ���� + ���� ������Ʈ )
// 8. ���ڴ� �ش� ĭ���� ���� ������Ʈ ����
// 9. ���带 ��� �����ϰ� ���� ���

struct Player {
	int y;
	int x;
	int dir;
	int Power;
	int totalPower;
	int Score;
};

struct Gun {
	int y;
	int x;
	int Att;
};

vector<Player>player;
vector<Gun>gun;

// ����ũ��
int n;
// �÷��̾� ��
int m;
// ������ ��
int k;

int MAP[20][20];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };


void input() {
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int Num = 0;
			cin >> Num;
			if (Num != 0) {
				gun.push_back({ i,j,Num });
			}
		}
	}

	for (int i = 0; i < m; i++)
	{
		int x, y, d, s = 0;
		cin >> x >> y >> d >> s;
		player.push_back({ x - 1,y - 1,d,s,s,0 });
	}

}

void updateGun(int y, int x, int who) {

	// �� �� ���⸦ ���� �� �ִٸ� ���� ������
	int gunPower = 0;
	int gunIdx = -1;
	for (int g = 0; g < gun.size(); g++)
	{
		if (y == gun[g].y && x == gun[g].x) {
			if (gunPower < gun[g].Att) {
				gunIdx = g;
				gunPower = gun[g].Att;
			}
		}
	}
	// ���Ƴ�����
	if (player[who].totalPower < player[who].Power + gunPower) {
		// ���� ���� �Ŀ� ����
		int beforeAtt = player[who].totalPower - player[who].Power;
		// ���� ���⸦ ���Ŷ�
		if (beforeAtt != 0) {
			gun.push_back({ y,x, beforeAtt });
		}
		// �� �� ���⸦ ������ (������ ����)
		player[who].totalPower = player[who].Power + gunPower;
		gun.erase(gun.begin() + gunIdx, gun.begin() + gunIdx + 1);
	}
}

void defeat(int idx) {
	// �� �÷��̾� ó��
	// ������ �� ĭ�� ������
	int beforeAtt = player[idx].totalPower - player[idx].Power;
	if (beforeAtt != 0) {
		player[idx].totalPower -= beforeAtt;
		gun.push_back({ player[idx].y, player[idx].x, beforeAtt });
	}

	int go = 1;
	while (go == 1) {
		// ���� ��ġ�� ���� �ƴϸ鼭 ��ĭ�̸� go�� 0�� ����
		// while ���� ����������

		// �ش� �������� ��ĭ�̵��� ��ġ�� ���Ѵ�.
		int ny = player[idx].y + dy[player[idx].dir];
		int nx = player[idx].x + dx[player[idx].dir];

		int whoexist = 0;
		for (int i = 0; i < m; i++)
		{
			// �ڱ��ڽ��� �������� �ʴ´�.
			if (idx == i)continue;
			if (ny == player[i].y && nx == player[i].x) {
				whoexist = 1;
			}
		}
		// ��ĭ�̸�!!! ���⸸ �� �����ϰ� while�� Ż��
		if (ny < n && nx < n && ny >= 0 && nx >= 0 && whoexist == 0) {
			go = 0;
			continue;
		}
		// ���̰ų� �÷��̾ ������ 90�� ȸ��
		player[idx].dir = (player[idx].dir + 1) % 4;
	}
	// �ٲ� ���⿡ �°� �̵�
	player[idx].y += dy[player[idx].dir];
	player[idx].x += dx[player[idx].dir];
	// ������ ���� ������Ʈ
	updateGun(player[idx].y, player[idx].x, idx);
}

void fight(int fr, int se) {

	// ���� �̰���� �Ǵ��϶�
	// fr�� �̱���
	if (player[fr].totalPower > player[se].totalPower) {
		// fr�� ������ ��������.
		player[fr].Score += player[fr].totalPower - player[se].totalPower;
		// se�� ����
		defeat(se);
		// ���ڴ� �� ĭ���� ���� ������Ʈ ����
		updateGun(player[fr].y, player[fr].x, fr);
	}

	// se�� �̱���
	else if (player[se].totalPower > player[fr].totalPower) {
		// se�� ������ ��������.
		player[se].Score += player[se].totalPower - player[fr].totalPower;
		// fr�� ����
		defeat(fr);
		// ���ڴ� �� ĭ���� ���� ������Ʈ ����
		updateGun(player[se].y, player[se].x, se);
	}

	// fr�� se�� ���� ������ ���� Power�� �ºΰ���
	// ��� ������ ���� �� ����
	else {
		// fr�� ���� Power�� ���� ���
		if (player[fr].Power > player[se].Power) {
			defeat(se);
			updateGun(player[fr].y, player[fr].x, fr);
		}
		// se�� ���� Power�� ���� ���
		else {
			defeat(fr);
			updateGun(player[se].y, player[se].x, se);
		}
	}
}

void move() {

	// �÷��̾���� ������� �����Ѵ�
	for (int i = 0; i < m; i++)
	{

		// �ش� ��ġ���� ��ĭ ���� ��ġ�� ���ض�
		int ny = player[i].y + dy[player[i].dir];
		int nx = player[i].x + dx[player[i].dir];

		// �� ��ġ�� �� ���̸� �Ųٷ�~ ( ���⺤�� �Ųٷ� �ϰ� ��ĭ ���� )
		if (ny >= n || nx >= n || ny < 0 || nx < 0) {
			player[i].dir = (player[i].dir + 2) % 4;
			ny = player[i].y + dy[player[i].dir];
			nx = player[i].x + dx[player[i].dir];
		}
		// �� ��ġ�� �̵�
		player[i].y = ny;
		player[i].x = nx;

		// �� ��ġ�� �ٸ��÷��̾ ������ fight
		int fightflag = 0;
		for (int j = 0; j < m; j++)
		{
			if (i == j)continue;
			if (ny == player[j].y && nx == player[j].x) {
				fightflag = 1;
				fight(i, j);
			}
		}

		if (fightflag == 0) {
			// ���� ������Ʈ
			updateGun(ny, nx, i);
		}
	}
}

int main() {

	input();
	for (int i = 0; i < k; i++)
	{
		move();
	}
	for (int i = 0; i < m; i++)
	{
		cout << player[i].Score << " ";
	}
	return 0;
}