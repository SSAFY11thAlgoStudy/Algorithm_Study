#include <iostream>
using namespace std;

int dx[4] = { 0,0,-1,1 };
int dy[4] = { 1,-1,0,0 };
int dice[7] = { 0 };
int n, m, x, y, k;
int map[21][21];
int command[1001]; //명령어 넣을 배열


void rolling() {
	for (int i = 0; i < k; i++) {
		int dir = command[i]; // 명령어
		bool check = true;  // 범위 나갔는지 판별하기 위한 것
		int nx = x + dx[dir - 1]; // dir = 3 (1,0), dir = 2 (-1,0), dir = 1 (0,-1), dir = 0 (0,1)
		int ny = y + dy[dir - 1]; // 방향 벡터도 일부러 dir값 순서에 맞게 만들어줬음
		if (nx >= n || nx < 0 || ny >= m || ny < 0) { // 범위를 벗어나면
			check = false; // false
		}
		if (!check) continue; //false면 아무것도 안해야 하므로 continue
		x = nx; // true이면 범위 안이므로 x,y좌표 업데이트
		y = ny;

		if (dir == 4) { // 4이면 남쪽으로 
			int temp = dice[1]; // 2 => 6 => 5 => 1
			dice[1] = dice[5];  // 1    2    6    5
			dice[5] = dice[6];  // 5    1    2    6
			dice[6] = dice[2];  // 6    5    1    2
			dice[2] = temp;
		}
		else if (dir == 3) { // 3이면 북쪽으로
			int temp = dice[1]; // 2 => 1 => 5 => 6
			dice[1] = dice[2];  // 1    5    6    2
			dice[2] = dice[6];  // 5    6    2    1
			dice[6] = dice[5];  // 6    2    1    5
			dice[5] = temp;
		}
		else if (dir == 2) { // 2이면 서쪽으로
			int temp = dice[1];  // 4 1 3  => 1 3 6  => 3 6 4 =>  6 4 1
			dice[1] = dice[4];   //   6         4         1         3
			dice[4] = dice[6];
			dice[6] = dice[3];
			dice[3] = temp;
		}
		else if (dir == 1) { // 1이면 동쪽으로
			int temp = dice[1];  // 4 1 3  => 6 4 1  => 3 6 4 =>  1 3 6
			dice[1] = dice[3];   //   6         3         1         4
			dice[3] = dice[6];
			dice[6] = dice[4];
			dice[4] = temp;
		}
		if (map[x][y] == 0) { // 0일때
			map[x][y] = dice[6]; // 칸에 주사위 바닥면 값 업데이트
		}
		else {  // 0이 아닐때
			dice[6] = map[x][y]; // 주사위 바닥면 값 칸의 값으로 업데이트 하고
			map[x][y] = 0;       // 칸의 값은 0으로 업데이트
		}
		cout << dice[1] << '\n';  // 가장 윗면 값 출력 

	}

}

int main() {
	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < k; i++) {
		cin >> command[i];
	}
	rolling();
	return 0;
}