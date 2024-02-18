#include<iostream>
#include<vector>
using namespace std;

int n, m, x, y, k;
int map[21][21];
vector<int> dice(6); // 위, 아래, 앞, 뒤, 좌, 우

bool isValid(int dir)
{
	int nx = x;
	int ny = y;
	if (dir == 1)	// 동쪽
		ny++;
	else if (dir == 2)	// 서쪽
		ny--;
	else if (dir == 3)	// 북쪽
		nx--;
	else
		nx++;	// 남쪽

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
	// 주사위를 굴렸을 때 이전 위치에 해당하는 값을 바꿔주어야한다.

	vector<int> tmp = dice;

	// 동쪽으로 굴리면? ->  앞 뒤는 상관 x 
	if (dir == 1)
	{
		// 좌측 -> 윗면
		dice[0] = tmp[4];

		// 우측 -> 아랫면
		dice[1] = tmp[5];

		// 아랫면 -> 좌측
		dice[4] = tmp[1];

		// 윗면 -> 우측
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

		// 주사위의 인덱스 범위 확인 후
		if (!isValid(dir)) continue;

		// 주사위를 굴린다.
		roll(dir);

		// 현재 칸에 0이 아닌 숫자가 적혀있으면
		if (map[x][y] > 0) {
			// 주사위 바닥면 (1번 인덱스는 아랫면에 해당) 칸에 숫자가 복사된다.
			dice[1] = map[x][y];

			// 현재 칸에 있던 수는 0으로 교체
			map[x][y] = 0;
		}

		// 현재 칸에 0이 적혀있으면
		else {
			// 해당 칸에 주사위 바닥면에 적힌 숫자 복사하기
			map[x][y] = dice[1];
		}

		cout << dice[0] << "\n";
	}

	return 0;
}