#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

//특성 A는 0 특성 B는 1
int t, d, w, k;
int map[14][21];
int copy_map[14][21];
int res;

void init() {
	memset(map, -1, sizeof(map));
	memset(copy_map, -1, sizeof(copy_map));
	res = 1e9;
}

void input() {
	cin >> d >> w >> k;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < w; j++) {
			cin >> map[i][j];
			copy_map[i][j] = map[i][j];
		}
	}
}

bool check() {
	int check_cnt = 0;
	for (int i = 0; i < w; i++) {
		int a_cnt = 0, b_cnt = 0;

		for (int j = 0; j < d; j++) {
			if (copy_map[j][i] == 0) {
				a_cnt++;
				b_cnt = 0;
			}
			else if(copy_map[j][i] == 1) {
				a_cnt = 0;
				b_cnt++;
			}
			if (a_cnt >= k || b_cnt >= k) {
				check_cnt++;
				break;
			}
		}
		if (a_cnt < k && b_cnt < k) return false;
	}
	if (check_cnt == w) return true;
	else return false;
}
//해당 약품 넣어주기
void insert_drug(int temp, int idx) {
	for (int i = 0; i < w; i++) {
		copy_map[idx][i] = temp;
	}
}
//다시 원래대로 돌려서 다른 경우 탐색해주기
void turn_drug(int idx) {
	for (int i = 0; i < w; i++) {
		copy_map[idx][i] = map[idx][i];
	}
}

void dfs(int x, int cnt) {
	if (res < cnt) return;
	if (x == d) {
		if (check()) {
			res = min(res, cnt);
		}
		return;
	}
	//투입 안할때
	dfs(x + 1, cnt);
	//투입 할때 A
	insert_drug(0, x);
	dfs(x + 1, cnt + 1);
	//투입 할때 B
	insert_drug(1,x);
	dfs(x + 1, cnt + 1);
	//다른 경우를 위해 되돌려주기
	turn_drug(x);
}

int main() {
	cin >> t;
	for (int tc = 0; tc < t; tc++) {
		init();
		input();
		//약품 투입하지 않고도 성능검사 통과하는 경우 
		int de = 1;
		if (check()) {
			cout << "#" << tc + 1 << " " << 0 << '\n';
		}
		//약품 투입해야하는 경우
		else {
			dfs(0, 0);
			cout << "#" << tc + 1 << " " << res << '\n';
		}
	}

}