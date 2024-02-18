#define _NO_CRT_NO_SECURE
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int N, L; // ���� ũ��, ������ ����
int MAP[110][110];// �Է¹޴� ��� ��
int Runway[110][110]; // ���� ��ġ �� �迭
int ansCnt; // ���� ī��Ʈ
int flag; // ������ �����ϴ��� �Ǵ�

// �ذ��� : ���� üũ �� ���� üũ
// ���� üũ �� ���ʺ��� üũ ���̽��� �����ʺ��� üũ ���̽� ����
// ���ʺ��� üũ �� : ������ �κ��� ������ ���� ����( ��, ���� ���̸�ŭ �����Ѱ� üũ )
// �����ʺ��� üũ �� : ���� �κ��� ������ ���� ����( ��, ���� ���̸�ŭ �����Ѱ� üũ )
// 
// ������ üũ����
// 1. ���� �迭 �ʿ��� ��ø Ȯ��
// 2. ���� ���̰� 2���� ���� �ʴ���


// ���� ���� ���� üũ
void runway_ROW() {

	// ���� �� üũ 
	for (int i = 0; i < N; i++)
	{
		flag = 0;

		// �����ʿ��� �������� ����
		for (int j = N - 1; j > 0; j--)
		{
			if (flag == 1) {
				break;
			}
			// ������ ���̰� 1�̻��� ��
			// ���ΰ� ��ġ�Ǵ� ������ �������� Ȯ���ϴ� �κ�
			if (L > 1) {
				// ������ ���� ��
				if (MAP[i][j - 1] - MAP[i][j] == 1) {
					for (int k = 1; k < L; k++)
					{
						if (j + k >= N) {
							flag = 1;
							break;
						}
						// ���� ���̸�ŭ �������� �ʴٸ�
						if (MAP[i][j] != MAP[i][j + k]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i][j + k]++;
						}
					}
				}
			}

			// ������ ���� ���̰� 2���� �̻� ��
			if (j >= 1) {
				if (abs(MAP[i][j - 1] - MAP[i][j]) >= 2) {
					flag = 1;
					break;
				}
			}
			// ������ ���̰� 1�� ��
			// ������ ���̸�ŭ �������� üũ�� �ʿ䰡 ����
			if (L == 1) {
				if (MAP[i][j - 1] - MAP[i][j] == 1) {
					Runway[i][j]++;
				}
			}
		}

		// ���ʿ��� ���������� ����
		for (int j = 0; j < N - 1; j++)
		{
			if (flag == 1) {
				break;
			}

			if (L > 1) {
				// �������� ���� ��
				if (MAP[i][j] - MAP[i][j + 1] == -1) {
					for (int k = 1; k < L; k++)
					{
						if (j - k < 0) {
							flag = 1;
							break;
						}
						// ���� ���̸�ŭ �������� �ʴٸ�
						if (MAP[i][j] != MAP[i][j - k]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i][j - k]++;
						}
					}
				}
			}
			// ������ ���� ���̰� 2���� ������ �Ǵ��ϴ� �κ���
			// �� �ݺ������� �������� Ȯ�� ��

			// ������ ���̰� 1�� ��
			// ������ ���̸�ŭ �������� üũ�� �ʿ䰡 ����
			if (L == 1) {
				if (MAP[i][j] - MAP[i][j + 1] == -1) {
					Runway[i][j]++;
				}
			}
		}

		// ���ʽ���, �����ʽ��� �Ǵ��� ���� �� ���� �迭 Ȯ�� 
		for (int j = 0; j < N; j++)
		{
			// ���� ������ �� ���������� ���ΰ� ��ĥ ��
			if (Runway[i][j] >= 2) {
				flag = 1;
				break;
			}
		}
		// ���� ������ ��� �����Ѵٸ� ī��Ʈ ����~
		if (flag == 0) {
			ansCnt++;
		}
	}
}


// ���� ���� ���� üũ
// ���� ���� ���� ����
void runway_COL() {

	for (int j = 0; j < N; j++)
	{
		flag = 0;

		for (int i = N - 1; i > 0; i--)
		{
			if (flag == 1) {
				break;
			}

			if (L > 1) {
				if (MAP[i - 1][j] - MAP[i][j] == 1) {
					for (int k = 1; k < L; k++)
					{
						if (i + k >= N) {
							flag = 1;
							break;
						}
						if (MAP[i][j] != MAP[i + k][j]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i + k][j]++;
						}
					}
				}
			}

			if (i >= 1) {
				if (abs(MAP[i - 1][j] - MAP[i][j]) >= 2) {
					flag = 1;
					break;
				}
			}

			if (L == 1) {
				if (MAP[i - 1][j] - MAP[i][j] == 1) {
					Runway[i][j]++;
				}
			}
		}

		for (int i = 0; i < N - 1; i++)
		{
			if (flag == 1) {
				break;
			}

			if (L > 1) {

				if (MAP[i][j] - MAP[i + 1][j] == -1) {
					for (int k = 1; k < L; k++)
					{
						if (i - k < 0) {
							flag = 1;
							break;
						}

						if (MAP[i][j] != MAP[i - k][j]) {
							flag = 1;
							break;
						}
					}if (flag == 0) {
						for (int k = 0; k < L; k++)
						{
							Runway[i - k][j]++;
						}
					}
				}
			}

			if (L == 1) {
				if (MAP[i][j] - MAP[i + 1][j] == -1) {
					Runway[i][j]++;
				}
			}
		}

		for (int i = 0; i < N; i++)
		{

			if (Runway[i][j] >= 2) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			ansCnt++;
		}
	}
}

int main() {

	cin >> N >> L;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> MAP[i][j];
		}
	}
	runway_ROW();
	// ���� ���� �Ǵ� �� ���� �迭 �ʱ�ȭ
	memset(Runway, 0, sizeof(Runway));
	runway_COL();
	cout << ansCnt;
	return 0;
}