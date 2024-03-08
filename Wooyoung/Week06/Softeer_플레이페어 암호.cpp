#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>

using namespace std;

char MAP[5][5];

unordered_map<char, int>map;
unordered_map<int, char>cp_map;
string Message;
string Key;

vector<pair<char, char>>words;
vector<char>answer;
void fillKey() {
	map['J'] = 9999;
	int start_idx = 0;
	for (int i = 0; i < Key.length(); i++) {
		// 아직 저장되지 않은 알파벳이면 표에 추가
		if (map.count(Key[i]) == 0) {
			map[Key[i]] = start_idx++;
		}
	}
	for (int i = 0; i < 26; i++) {
		char cur_alpha = char(65 + i);
		if (map.count(cur_alpha) == 0) {
			map[cur_alpha] = start_idx++;
		}
	}
	for (auto p : map) {
		cp_map[p.second] = p.first;
	}
}

void cutMessage() {

	int cur_idx = 0;
	while (1) {
		if (cur_idx == Message.length() - 1) {
			// 현재 마지막 글자면?
			words.push_back({ Message[cur_idx],'X' });
			break;
		}
		char now_alpha = Message[cur_idx];
		char next_alpha = Message[cur_idx + 1];
		if (now_alpha == next_alpha) {
			// 같으면?
			if (now_alpha == 'X') {
				words.push_back({ 'X','Q' });
			}
			else {
				words.push_back({ now_alpha,'X' });
			}
			cur_idx++;
		}
		else {
			words.push_back({ now_alpha,next_alpha });
			cur_idx += 2;
			if (cur_idx == Message.length())break;
		}
	}

}

void encryption() {

	for (int i = 0; i < words.size(); i++) {

		char first = words[i].first;
		char second = words[i].second;

		int f_row = map[first] / 5;
		int f_col = map[first] % 5;


		int s_row = map[second] / 5;
		int s_col = map[second] % 5;

		// 같은 행이면
		if (f_row == s_row) {
			f_col += 1;
			s_col += 1;
			if (f_col % 5 == 0) {
				f_col -= 5;
			}
			if (s_col % 5 == 0) {
				s_col -= 5;
			}
		}

		// 같은 열이면
		else if (f_col == s_col) {
			f_row += 1;
			s_row += 1;
			if (f_row % 5 == 0) {
				f_row -= 5;
			}
			if (s_row % 5 == 0) {
				s_row -= 5;
			}
		}

		// 둘다 아니면
		else {
			int temp = f_col;
			f_col = s_col;
			s_col = temp;
		}

		answer.push_back(cp_map[f_row * 5 + f_col]);
		answer.push_back(cp_map[s_row * 5 + s_col]);
	}

}

int main() {

	cin >> Message;
	cin >> Key;
	fillKey();
	cutMessage();
	encryption();

	for (auto p : answer) {
		cout << p;
	}

	return 0;
}