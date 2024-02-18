#include<iostream>
#include<vector>
using namespace std;

int n, m, x, y, k;
int map[21][21];
vector<int> dice(6); // ��, �Ʒ�, ��, ��, ��, ��

bool isValid(int dir)
{
	int nx = x;
	int ny = y;
	if (dir == 1)	// ����
		ny++;
	else if (dir == 2)	// ����
		ny--;
	else if (dir == 3)	// ����
		nx--;
	else
		nx++;	// ����

	if (nx < 0 || nx >= n || ny < 0 || ny >= m) return false;
	else
	{
		x = nx;
		y = ny;
		return true;
	}
}

void roll(int dir)
{
	// �ֻ����� ������ �� ���� ��ġ�� �ش��ϴ� ���� �ٲ��־���Ѵ�.

	vector<int> tmp = dice;

	// �������� ������? ->  �� �ڴ� ��� x 
	if (dir == 1)
	{
		// ���� -> ����
		dice[0] = tmp[4];

		// ���� -> �Ʒ���
		dice[1] = tmp[5];

		// �Ʒ��� -> ����
		dice[4] = tmp[1];

		// ���� -> ����
		dice[5] = tmp[0];
	}
	else if (dir == 2)
	{
		dice[0] = tmp[5];
		dice[1] = tmp[4];
		dice[4] = tmp[0];
		dice[5] = tmp[1];
	}
	else if (dir == 3)
	{
		dice[0] = tmp[3];
		dice[1] = tmp[2];
		dice[2] = tmp[0];
		dice[3] = tmp[1];
	}
	else
	{
		dice[0] = tmp[2];
		dice[1] = tmp[3];
		dice[2] = tmp[1];
		dice[3] = tmp[0];
	}
}

int main()
{

	cin >> n >> m >> x >> y >> k;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
		}
	}

	int dir;
	for (int i = 0; i < k; i++) {
		cin >> dir;

		// �ֻ����� �ε��� ���� Ȯ�� ��
		if (!isValid(dir)) continue;

		// �ֻ����� ������.
		roll(dir);

		// ���� ĭ�� 0�� �ƴ� ���ڰ� ����������
		if (map[x][y] > 0) {
			// �ֻ��� �ٴڸ� (1�� �ε����� �Ʒ��鿡 �ش�) ĭ�� ���ڰ� ����ȴ�.
			dice[1] = map[x][y];

			// ���� ĭ�� �ִ� ���� 0���� ��ü
			map[x][y] = 0;
		}

		// ���� ĭ�� 0�� ����������
		else {
			// �ش� ĭ�� �ֻ��� �ٴڸ鿡 ���� ���� �����ϱ�
			map[x][y] = dice[1];
		}

		cout << dice[0] << "\n";
	}

	return 0;
}