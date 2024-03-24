#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

string key, password, message;

vector<char> res;
vector<char> result;

int vis[26];
char map[5][5];

void makemap() {

	int cnt = 0;
	int cnt2 = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {

			if (cnt < key.length()) {
				if (vis[key[cnt] - 'A'] == 0) {
					char temp = key[cnt];
					map[i][j] = temp;
					vis[key[cnt] - 'A'] = 1;
				}
				else {
					j--;
				}
				cnt++;
			}
			else {
				if (vis[cnt2] == 0) {
					map[i][j] = 'A' + cnt2;
					vis[cnt2] = 1;
				}
				else {
					j--;
				}
				cnt2++;
			}
		}
	}
}

void makecode() {
	for (int i = 0; i < message.length(); i = i + 2) {
		if (message[i] == message[i + 1]) {
			if (message[i] == 'X') {
				res.push_back(message[i]);
				res.push_back('Q');
			}
			else {
				res.push_back(message[i]);
				res.push_back('X');
			}
			i--;
		}
		else {
			res.push_back(message[i]);
			res.push_back(message[i + 1]);
		}
	}

	if (res[res.size() - 1] == '\0') {
		res[res.size() - 1] = 'X';
	}
}

void transcode() {
	for (int i = 0; i < res.size(); i = i + 2) {

		int x_1 = 0;
		int y_1 = 0;
		int x_2 = 0;
		int y_2 = 0;

		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (res[i] == map[j][k]) {
					x_1 = k;
					y_1 = j;
				}
				else if (res[i + 1] == map[j][k]) {
					x_2 = k;
					y_2 = j;
				}
			}
		}

		if (y_1 == y_2) {
			result.push_back(map[y_1][(x_1 + 1) % 5]);
			result.push_back(map[y_2][(x_2 + 1) % 5]);

		}
		else if (x_1 == x_2) {
			result.push_back(map[(y_1 + 1) % 5][x_1]);
			result.push_back(map[(y_2 + 1) % 5][x_2]);
		}
		else {
			result.push_back(map[y_1][x_2]);
			result.push_back(map[y_2][x_1]);
		}
	}
}

int main() {

	//freopen("sample.txt", "r", stdin);

	cin >> message;
	cin >> key;

	vis[9] = 1;
	makemap();
	makecode();
	transcode();

	for (int i = 0; i < result.size(); i++) {
		cout << result[i];
	}

	return 0;
}