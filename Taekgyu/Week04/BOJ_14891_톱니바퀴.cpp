#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

int MAP[4][8]; // �¿� ���� ��
int K; // ȸ���� �����ϴ� Ƚ��
int circle; // �����¿� ��ġ �Է�
int dir; // ���� �¿��� ȸ������ �Է�
int DAT[4]; // 4�� �¿��� ȸ������ ���
string line; // �¿� gear ��
int sum;

// DAT ���� // ���� ����
// ���� �¿� ��ġ : st
// ���� ���� ���� : dir
void func() {
	int st = circle - 1;

	// ������ �¿��� ȸ���ϴ��� �Ǵ��ϰ� DAT�� ȸ������ ����

	// --------- ���������� �Ǵ��� �� ----------------
	// ���� �ڽ��� �¿��� ȸ���� �ְ�
	// �ڽ��� �¿��� 2�� �ε�����
	// ������ �¿��� 6�� �ε����� �ٸ��� Ȯ��

	// --------- �������� �Ǵ��� �� ----------------
	// ���� �ڽ��� �¿��� ȸ���� �ְ�
	// �ڽ��� �¿��� 6�� �ε�����
	// ���� �¿��� 2�� �ε����� �ٸ��� Ȯ��

	// ������ ù��° �¿��� ��� 1-2-3-4 ����
	if (st == 0) {
		DAT[st] = dir;
		for (int i = 0; i < 3; i++)
		{
			if (MAP[i][2] != MAP[i + 1][6] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i + 1] = dir;
			}
			else {
				DAT[i + 1] = 0;
			}
		}
	}
	// ������ �׹�° �¿��� ��� 4-3-2-1 ����
	else if (st == 3) {
		DAT[st] = dir;
		for (int i = 3; i > 0; i--)
		{
			if (MAP[i][6] != MAP[i - 1][2] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i - 1] = dir;
			}
			else {
				DAT[i - 1] = 0;
			}
		}
	}
	// ������ �߰� �¿��� ��� �ݺ��� �ΰ��� ��� �ľ�
	else if (st >= 1 && st < 3) {
		DAT[st] = dir;
		// ���� �¿� ���� ���� �Ǵ�
		for (int i = st; i > 0; i--)
		{
			if (MAP[i][6] != MAP[i - 1][2] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i - 1] = dir;
			}
			else {
				DAT[i - 1] = 0;
			}
		}
		// ���� �¿� ���� ������ �Ǵ�
		for (int i = st; i < 3; i++)
		{
			if (MAP[i][2] != MAP[i + 1][6] && DAT[i] != 0) {
				dir = -DAT[i];
				DAT[i + 1] = dir;
			}
			else {
				DAT[i + 1] = 0;
			}
		}
	}
}

// �ϼ��� DAT ���� �迭�� ���� �¿� ȸ�� ����
void solution() {

	// ù��° �¿����� ������ �¿����� �ݺ���
	for (int i = 0; i < 4; i++)
	{
		// ȸ������ �ʴ� �¿��̸� �Ѿ~
		if (DAT[i] == 0) {
			continue;
		}
		//�ð�������� ȸ���ϸ�
		if (DAT[i] == 1) {
			int temp = MAP[i][7];
			for (int j = 7; j > 0; j--)
			{
				MAP[i][j] = MAP[i][j - 1];
			}
			MAP[i][0] = temp;
		}
		// �ݽð�������� ȸ���ϸ�
		else if (DAT[i] == -1) {
			int temp = MAP[i][0];
			for (int j = 0; j < 7; j++)
			{
				MAP[i][j] = MAP[i][j + 1];
			}
			MAP[i][7] = temp;
		}
	}
}

int main() {
	for (int i = 0; i < 4; i++)
	{
		cin >> line;
		for (int j = 0; j < 8; j++)
		{
			int a = line[j] - '0';
			MAP[i][j] = a;
		}
	}
	cin >> K;
	// �� K�� ȸ�� ����
	for (int i = 0; i < K; i++)
	{
		cin >> circle >> dir;
		func();
		solution();
	}
	// K�� ȸ���� �� �� �¿��� ���� �ջ�
	if (MAP[0][0] == 1) {
		sum += 1;
	}
	if (MAP[1][0] == 1) {
		sum += 2;
	}
	if (MAP[2][0] == 1) {
		sum += 4;
	}
	if (MAP[3][0] == 1) {
		sum += 8;
	}
	cout << sum;
	return 0;
}