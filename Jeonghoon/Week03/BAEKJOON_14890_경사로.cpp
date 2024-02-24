#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>

using namespace std;

int N, L;
int map[101][101];
int cnt;
int check[101][101];

void input() {
	cin >> N >> L;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

void solve1() {

	for (int y = 0; y < N; y++) {
		int flag = 0;

		for (int x = 1; x < N; x++) {

			//높이 1차이 이상나면 break
			if (abs(map[y][x - 1] - map[y][x]) > 1) {
				flag = 1;
				break;
			}

			//내려가는 경사로 확인
			if ((map[y][x - 1] - map[y][x]) == 1) {
				for (int i = x; i < x + L; i++) {
					if (map[y][x] != map[y][i] || check[y][i] == 1) {
						flag = 1;
						break;
					}
					check[y][i] = 1;
				}
			}

			//올라가는 경사로 확인
			if ((map[y][x - 1] - map[y][x]) == -1) {
				for (int i = x - L; i < x; i++) {
					if (map[y][x - 1] != map[y][i] || check[y][i] == 1) {
						flag = 1;
						break;
					}
					check[y][i] = 1;
				}
			}
			if (flag == 1) {
				break;
			}

		}
		if (flag == 0) {
			cnt++;
		}
	}
}

void solve2() {
	for (int x = 0; x < N; x++) {
		int flag = 0;

		for (int y = 1; y < N; y++) {

			//높이 1차이 이상나면 break
			if (abs(map[y - 1][x] - map[y][x]) > 1) {
				flag = 1;
				break;
			}

			//내려가는 경사로 확인
			if ((map[y - 1][x] - map[y][x]) == 1) {
				for (int i = y; i < y + L; i++) {
					if (map[y][x] != map[i][x] || check[i][x] == 1) {
						flag = 1;
						break;
					}
					check[i][x] = 1;
				}
			}

			//올라가는 경사로 확인
			if ((map[y - 1][x] - map[y][x]) == -1) {
				for (int i = y - L; i < y; i++) {
					if (map[y - 1][x] != map[i][x] || check[i][x] == 1) {
						flag = 1;
						break;
					}
					check[i][x] = 1;
				}
			}
			if (flag == 1) {
				break;
			}
		}

		if (flag == 0) {
			cnt++;
		}
	}
}

int main() {
	//freopen("sample.txt", "r", stdin);

	input();

	solve1();
	memset(check, 0, sizeof(check));
	solve2();

	cout << cnt;

	return 0;
}