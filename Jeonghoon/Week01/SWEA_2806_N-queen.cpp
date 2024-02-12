#include<iostream>
#include<cstring>

using namespace std;

int T;
int N;
int map[10];
int cnt;


void init() {
	memset(map, 0, sizeof(map));
	cnt = 0;
}

int check(int a, int b) {
	for (int i = 0; i < a; i++) {
		if ((i + map[i]) == (a + b) || (i - map[i]) == (a - b) || map[i] == map[a]) {
			return 1;
		}
	}
	return 0;
}

void queen(int level) {
	if (level == N) {
		cnt++;
		return;
	}

	for (int y = 0; y < N; y++) {
		int check1 = 0;
		map[level] = y;

		if (level > 0) {
			check1 = check(level, y);
		}

		if (check1 == 0) {
			queen(level + 1);
		}
	}
}

int main() {

	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		init();

		cin >> N;
		queen(0);

		cout << "#" << tc << " " << cnt << "\n";
	}

	return 0;
}