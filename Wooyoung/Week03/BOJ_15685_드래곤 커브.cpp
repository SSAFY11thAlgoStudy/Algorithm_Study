#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

// 0 : 우, 1 : 상, 2 : 좌, 3 : 하

int n, x, y, d, g, ans;
int map[101][101];
struct Info {
	int x, y, d, g;
};
vector<Info>v;

void dragon(Info a) {

	int cur_x = a.x;
	int cur_y = a.y;
	int cur_d = a.d;
	int cur_g = a.g;

	vector<int>line;
	line.push_back(cur_d);
	// 세대에 맞는 이동 선분 기록 (0,1,2,3)
	for (int i = 0; i < cur_g; i++) {
		vector<int>r_line;
		for (int j = line.size() - 1; j >= 0; j--) {
			r_line.push_back((line[j]+1)%4);
		}
		for (int j = 0; j < r_line.size(); j++) {
			line.push_back(r_line[j]);
		}
	}

	map[cur_x][cur_y] = 1;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == 0) {
			cur_x++;
		}
		else if (line[i] == 1) {
			cur_y--;
		}
		else if (line[i] == 2) {
			cur_x--;
		}
		else if (line[i] == 3) {
			cur_y++;
		}
		map[cur_x][cur_y] = 1;
	}

}

void cnt() {

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (map[i][j] == 1 && map[i + 1][j] == 1 && map[i][j + 1] == 1 && map[i + 1][j + 1] == 1) {
				ans++;
			}

		}

	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> d >> g;
		v.push_back({ x,y,d,g });
	}

	for (int i = 0; i < n; i++) {
		dragon(v[i]);
	}
	cnt();
	cout << ans;
	return 0;
}