#include<iostream>
#include<vector>
#include<string>

using namespace std;
vector<char>map;
char map_mat[5][5];
string mes;
string result;

void input() {
	int dat[100] = { 0 };
	cin >> mes;
	string key;
	cin >> key;
	for (int i = 0; i < key.size(); i++)
	{
		if (dat[key[i]] == 1) {
			continue;
		}
		else {
			map.push_back(key[i]);
			dat[key[i]] = 1;
		}
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		if (dat[i] == 1 || i == 'J') {
			continue;
		}
		map.push_back(i);
	}
}

void solve(char c[]) {
	int firsty, firstx;
	int secondy, secondx;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (c[0] == map[i * 5 + j]) {
				firsty = i;
				firstx = j;
			}
			if (c[1] == map[i * 5 + j]) {
				secondy = i;
				secondx = j;
			}
		}
	}
	//경우 1
	if (firsty == secondy) {
		firstx = (firstx + 1) % 5;
		secondx = (secondx + 1) % 5;

		result += map[firsty * 5 + firstx];
		result += map[secondy * 5 + secondx];
	}
	//경우 2
	else if (firstx == secondx) {
		firsty = (firsty + 1) % 5;
		secondy = (secondy + 1) % 5;

		result += map[firsty * 5 + firstx];
		result += map[secondy * 5 + secondx];
	}
	//경우 3
	else {
		result += map[firsty * 5 + secondx];
		result += map[secondy * 5 + firstx];
	}
}

int main() {
	input();

	for (int i = 0; i < mes.size(); i++)
	{
		char c[2] = {};
		if (mes.size() <= i + 1) {
			c[0] = mes[i];
			c[1] = 'X';
			solve(c);
		}
		else if (mes[i] == mes[i + 1]) {
			if (mes[i] == 'X') {
				c[0] = mes[i];
				c[1] = 'Q';
				solve(c);
			}
			else {
				c[0] = mes[i];
				c[1] = 'X';
				solve(c);
			}
		}
		else {
			c[0] = mes[i];
			c[1] = mes[i + 1];
			i++;
			solve(c);
		}
	}
	cout << result;
	return 0;
}