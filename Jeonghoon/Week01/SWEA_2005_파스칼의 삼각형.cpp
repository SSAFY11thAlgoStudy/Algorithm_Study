#include<iostream>
#include<cstring>

using namespace std;

int N;

//�� ������ �迭
int dat[10][10];

//�ʱ�ȭ 0����
void init() {
	memset(dat, 0, sizeof(dat));
}

void solve(int level)
{
	//N�� �ݺ��ؾ� �ϹǷ� level�� N�̵Ǹ� ����
	if (level == N) {
		return;
	}


	for (int i = 0; i < N; i++) {
		//(level,0) �� ��� (level-1,0) �� ���� 1�̹Ƿ� ���� �� �־��ֱ�
		if (i == 0) {
			dat[level][i] = dat[level - 1][i];
		}

		//�̿ܿ��� (level-1, i-1) + (level-1,i) = (level,i)�̹Ƿ�
		else {
			dat[level][i] = dat[level - 1][i] + dat[level - 1][i - 1];
		}
	}

	//���� �ܰ�� �̵�
	solve(level + 1);
}

int main() {

	int T = 0;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		init();

		//�׻� (0,0)�� 1�̹Ƿ�
		dat[0][0] = 1;

		cin >> N;

		//ù ���� 1�� ó�������Ƿ� level 1���� ����
		solve(1);

		cout << "#" << tc << " " << endl;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (dat[i][j] == 0) {
					continue;
				}
				cout << dat[i][j] << " ";
			}
			cout << endl;
		}

	}

	return 0;
}