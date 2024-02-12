#include <iostream>
using namespace std;
int r, c, t, ds = 0; //ds = 남아있는 먼지 총합
int x1, x2;
int dust[51][51];
int arr[51][51]; // 동시에 늘어나는 먼지를 담기 위한 배열
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

void spread() {  //먼지 확산
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (dust[i][j] == -1 || dust[i][j] == 0) continue; // -1이면 공기청정기, 0이면 더해도 의미 없음
			int cnt = 0; //4가지 방향중 확산된 칸의 수
			int temp = dust[i][j] / 5; // 현재 미세먼지 양의 /5만큼 퍼지므로

			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx >= r || nx < 0 || ny >= c || ny < 0) continue;
				if (dust[nx][ny] == -1) continue;

				cnt++;  //조건 다 만족하면 한칸 퍼진 것 이므로
				arr[nx][ny] += temp; // arr배열에 temp더해주기
			}
			dust[i][j] = dust[i][j] - (temp * cnt); // 현재 미세먼지 값은 총 확산된 칸의수*temp

		}
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (dust[i][j] != -1) {
				dust[i][j] += arr[i][j]; // 현재 미세먼지 배열에 퍼진 먼지 값 업데이트
				arr[i][j] = 0; // 퍼진 먼지 값 초기화
			}
		}
	}
}

void air() {
	//위쪽 방향

	//왼쪽
	for (int i = x1 - 1; i >= 0; i--) {
		dust[i + 1][0] = dust[i][0];
	}
	//위쪽
	for (int i = 0; i < c - 1; i++) {
		dust[0][i] = dust[0][i + 1];
	}
	//오른쪽
	for (int i = 0; i < x1; i++) {
		dust[i][c - 1] = dust[i + 1][c - 1];
	}
	//아래쪽
	for (int i = c - 1; i > 1; i--) {
		dust[x1][i] = dust[x1][i - 1];
	}

	dust[x1][1] = 0;
	dust[x1][0] = -1;

	//아래쪽 방향
	//왼쪽
	for (int i = x2; i < r; i++) {
		dust[i][0] = dust[i + 1][0];
	}
	//아래쪽
	for (int i = 0; i < c - 1; i++) {
		dust[r - 1][i] = dust[r - 1][i + 1];
	}
	//오른쪽
	for (int i = r - 1; i > x2; i--) {
		dust[i][c - 1] = dust[i - 1][c - 1];
	}
	// 위쪽
	for (int i = c - 1; i > 1; i--) {
		dust[x2][i] = dust[x2][i - 1];
	}
	dust[x2][0] = -1;
	dust[x2][1] = 0;

}
int main() {
	cin >> r >> c >> t;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> dust[i][j];
			if (dust[i][j] == -1) {
				if (x1 == 0) x1 = i;
				else x2 = i;
			}
		}
	}
	for (int i = 0; i < t; i++) {
		spread();
		air();
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (dust[i][j] > 0) {
				ds += dust[i][j];
			}
		}
	}
	cout << ds;
	return 0;
}