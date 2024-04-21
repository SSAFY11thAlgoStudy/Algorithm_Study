#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>

using namespace std;

// N * N �̷ΰ� ����
// ���� r
// ������ c����
// -1�� �Է¹ޱ�

// �̷δ� 3������ ���·� �����Ѵ�
// ��ĭ �� �ⱸ
// ���� �������� �����ϸ�
// ȸ���ϸ� �������� -1�� ���δ�.
// �������� 0�� �Ǹ� ��ĭ���� ����ȴ�.
// �����ڴ� 1�ʸ��� ��ĭ�� �����δ�.
// �����̴� ������ ������ ����

// �ִܰŸ� |x1-x2| + |y1-y2|
// ��� �����ڴ� ���ÿ� �����δ�.
// �����¿�� ������ �� �ִ�.
// ���̸� ����
// ������ ĭ�� ���� �ӹ��� �ִ� ĭ���� �ִܰŸ��� ��������Ѵ�.
// ������ �� �ִ� ĭ�� �ΰ��̻��̶�� ������ ��, �Ϸ� �����̴� ���� �켱
// �����ڰ� ������ �� ���ٸ� �������� �ʴ´�
// ��ĭ�� 2���̻��� �����ڰ� ���� �� �ִ�.
// ����ϸ� ��Ÿ�� �����Ӱ� �Ȱ��� �����̸� �ȴ�.

// �����ڰ� �̵��� ���� ��
// �̷ΰ� ȸ���Ѵ�.
// �ⱸ�� ���� ����� �����ڸ� �����Ͽ� ���簢���� ��´�.
// ���ǿ� �´� ���簢���� ������ ���� ���� �ִ� ���簢���� �켱
// �ð�������� 90�� ȸ���ϸ�, ȸ���� ���� �������� 1�� ���Դϴ�.

// K�ʵ��� ���� ������ ��� �ݺ��Ѵ�.
// K�� ���� ��� �����ڰ� Ż�⿡ �����ϸ� ���� ��
// ������ ������ ��, ��� �����ڵ��� �̵��Ÿ� �հ� �ⱸ ��ǥ�� ����ض�
struct person
{
	int y;
	int x;
	int dis;
	bool exit;
};

struct Square {
	int y;
	int x;
	int size;

	bool operator<(Square Right)const {
		if (size < Right.size)return true;
		if (size > Right.size)return false;

		if (y < Right.y)return true;
		if (y > Right.y)return false;

		if (x < Right.x)return true;
		if (x > Right.x)return false;

		return false;
	}
};

// ������ ��ġ ����
vector<person>pv;
vector<Square>sv;
int N;
int M;
int K;
int MAP[12][12];
int cpMAP[12][12];
int turnMAP[12][12];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,1,-1 };
int exitCnt;
int totalMove;
int exY;
int exX;

void input() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	for (int i = 0; i < M; i++)
	{
		int y, x = 0;
		cin >> y >> x;
		pv.push_back({ y - 1,x - 1,0,false });
	}
	cin >> exY >> exX;
	exY--;
	exX--;
}

void turnSquare(int stY, int stX, int size) {
	// ���簢���� ����� �������� ����� �̿��ؼ� ���� ������ ����

	// �ش����簢�� �ȿ� �ִ� ������ �ľ�
	for (int i = 0; i < M; i++)
	{
		if (pv[i].exit)continue;
		// ȸ���ϴ� ���簢�� �ȿ� �ִٸ� ȸ�� ���Ѽ� ����
		if (pv[i].y >= stY && pv[i].y <= stY + size && pv[i].x >= stX && pv[i].x <= stX + size) {
			int my = pv[i].y - stY;
			int mx = pv[i].x - stX;
			int ny = mx;
			int nx = size - my;
			pv[i].y = ny + stY;
			pv[i].x = nx + stX;
		}
	}

	memset(cpMAP, 0, sizeof(cpMAP));
	// ���� Ư�� ������ 0,0���� �����ϴ� cpMAP�� �����Ѵ�.

	for (int i = 0; i <= size; i++)
	{
		for (int j = 0; j <= size; j++)
		{
			if (MAP[stY + i][stX + j] >= 1 && MAP[stY + i][stX + j] <= 9) {
				cpMAP[i][j] = MAP[stY + i][stX + j] - 1;
			}
			else {
				cpMAP[i][j] = MAP[stY + i][stX + j];
			}
		}
	}

	memset(turnMAP, 0, sizeof(turnMAP));
	// cpMAP�� ������.
	for (int i = 0; i <= size; i++)
	{
		for (int j = 0; j <= size; j++)
		{
			turnMAP[i][j] = cpMAP[size - j][i];
		}
	}

	for (int i = 0; i <= size; i++)
	{
		for (int j = 0; j <= size; j++)
		{
			MAP[i + stY][j + stX] = turnMAP[i][j];
		}
	}

	// Ż�ⱸ ����
	int ey = exY - stY;
	int ex = exX - stX;

	int eY = ex;
	int eX = size - ey;

	exY = eY + stY;
	exX = eX + stX;

}

void move() {

	// �ⱸ������ �Ÿ��� �����Ѵ�.
	for (int i = 0; i < M; i++)
	{
		// �̹� Ż���ߴٸ� ��Ƽ��
		if (pv[i].exit)continue;
		int Dis = abs(pv[i].y - exY) + abs(pv[i].x - exX);
		pv[i].dis = Dis;
	}

	// ���� ���� ��ġ�� �����¿� 4������ �ּ� �Ÿ��� ����Ѵ�.
	for (int i = 0; i < M; i++)
	{
		if (pv[i].exit)continue;
		// ���� ��ġ���� �ⱸ������ �Ÿ��� ����

		int MinDis = pv[i].dis;
		for (int d = 0; d < 4; d++)
		{
			int ny = pv[i].y + dy[d];
			int nx = pv[i].x + dx[d];
			if (ny >= N || nx >= N || ny < 0 || nx < 0)continue;
			// ���̸� ��������
			if (MAP[ny][nx] >= 1 && MAP[ny][nx] <= 9)continue;
			int findDis = abs(ny - exY) + abs(nx - exX);
			if (findDis < MinDis) {
				MinDis = findDis;
				// ��������
				totalMove++;
				pv[i].y = ny;
				pv[i].x = nx;
				// �����ΰ��� Ż�ⱸ���
				if (ny == exY && nx == exX) {
					pv[i].exit = true;
					exitCnt++;
				}
				break;
			}
		}
	}

}

void makeSquare() {

	int targetY = 0;
	int targetX = 0;

	// Ÿ�ټ���������
	// ���簢���� ����� ȸ������
	int stX = 21e8;
	int stY = 21e8;
	int Size = 1;

	// ��� ������ ���͸� �� ���鼭
	// ���簢���� �����.
	// �� �߿� ���� ������ ���ʿ� �ְ�
	// ���ʿ� �ִ� ���簢���� �������� ����� �̴´�.

	sv.clear();

	for (int i = 0; i < M; i++)
	{
		if (pv[i].exit)continue;

		targetY = pv[i].y;
		targetX = pv[i].x;

		if (targetX == exX || targetY == exY) {

			// y���� ���ٸ�
			// �������� x���� �����Ѵ�.
			if (targetY == exY) {
				Size = abs(targetX - exX);

				// �� ���� �÷����� �������� �ʹ��̴�
				if (targetY - Size <= 0) {
					// target�� ���ʿ��ִ°��
					if (targetX < exX) {
						stY = 0;
						stX = targetX;
					}
					else {
						stY = 0;
						stX = exX;
					}
				}

				else {
					// target�� ���ʿ��ִ°��
					if (targetX < exX) {
						stY = targetY - Size;
						stX = targetX;
					}
					else {
						stY = targetY - Size;
						stX = exX;
					}
				}
			}
			// x���� ���ٸ�
			// �������� y���� �����Ѵ�.
			else {
				Size = abs(targetY - exY);

				// �� �������� �÷����� �������� �ʹ��̴�
				if (targetX - Size <= 0) {
					// target�� �����ִ°��
					if (targetY < exY) {
						stX = 0;
						stY = targetY;
					}
					else {
						stX = 0;
						stY = exY;
					}
				}

				else {
					// target�� �����ִ°��
					if (targetY < exY) {
						stX = targetX - Size;
						stY = targetY;
					}
					else {
						stX = targetX - Size;
						stY = exY;
					}
				}
			}

		}
		else {
			// x�� y���� �ΰ� �� �ٸ��ٸ�~
			// ���� ���ϱ�
			// target�� Ż�ⱸ�� ������
			// x y���� ���ؼ� ������ ū ���� �������� �ȴ�.
			// �׸��� ���簢���� ũ�⸦ �� ������ ���� �� �ִ�.

			int endY = 0;
			int endX = 0;
			// targetX�� exX ��
			if (targetX >= exX) {
				endX = targetX;
			}
			else {
				endX = exX;
			}
			// targetY�� exY��
			if (targetY >= exY) {
				endY = targetY;
			}
			else {
				endY = exY;
			}

			// end�� ( ���簢���� �� ������ �Ʒ� )
			// �� �������� ���簢�� ũ�⸦ ������
			int difX = abs(targetX - exX);
			int difY = abs(targetY - exY);

			if (difX >= difY) {
				Size = difX;
			}
			else {
				Size = difY;
			}

			// �׷� �������� ���� �� �ִ�.
			// �������� ������ - ������
			stY = endY - Size;
			stX = endX - Size;

			if (stY < 0) {
				stY = 0;
			}
			if (stX < 0) {
				stX = 0;
			}
		}

		// ���Ϳ��߰��ϰ� ��Ʈ ����
		sv.push_back({ stY, stX, Size });
	}

	sort(sv.begin(), sv.end());

	turnSquare(sv[0].y, sv[0].x, sv[0].size);
}


int main() {

	input();

	for (int i = 0; i < K; i++)
	{
		// ��� �����ڰ� Ż���ߴٸ� break;

		move();
		if (exitCnt == M) {
			break;
		}
		makeSquare();
	}

	cout << totalMove << endl << exY + 1 << " " << exX + 1;

	return 0;
}