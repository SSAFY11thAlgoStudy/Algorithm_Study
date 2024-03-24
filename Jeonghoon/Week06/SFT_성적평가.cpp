#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

struct Sc {
	int num;
	int score;
};

vector<Sc> s[3];
int dat[4][100001];
int dat2[100001];
vector<Sc> r_total;

int N;

bool cmp(Sc a, Sc b) {
	return a.score > b.score;
}

void input() {
	cin >> N;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < N; j++){
			int temp;
			cin >> temp;
			s[i].push_back({ j+1, temp });
		}
	}
}

void init() {
	for (int i = 0; i < 3; i++){
		sort(s[i].begin(), s[i].end(), cmp);
	}
}

void solve() {
	for (int i = 0; i < 3; i++){
		int cnt = 0;
		for (int j = 0; j < N; j++){
			Sc result = s[i][j];

			if (j > 0) {
				if (s[i][j - 1].score == result.score) {
					cnt++;
					dat[i][result.num] = j + 1 - cnt;
					dat[3][result.num] += result.score;
				}
				else {
					cnt = 0;
					dat[i][result.num] = j + 1;
					dat[3][result.num] += result.score;
				}
			}
			else {
				dat[i][result.num] = j + 1;
				dat[3][result.num] += result.score;
			}
			
		}

		for (int j = 1; j <= N; j++){
			cout << dat[i][j] << " ";
		}
		cout << "\n";
	}

	for (int j = 1; j <= N; j++) {
		r_total.push_back({ j, dat[3][j] });
	}
	sort(r_total.begin(), r_total.end(), cmp);

	int cnt = 0;
	for (int j = 0; j < N; j++){
		Sc temp = r_total[j];

		if (j > 0) {
			if (r_total[j].score == r_total[j - 1].score) {
				cnt++;
				dat2[r_total[j].num] = j + 1 - cnt;
			}
			else {
				cnt = 0;
				dat2[r_total[j].num] = j + 1;
			}
		}
		else {
			dat2[r_total[j].num] = j + 1;
		}
	}

	for (int j = 1; j <= N; j++){
		cout << dat2[j] << " ";
	}
}

int main() {

	input();
	init();
	solve();

	return 0;
}