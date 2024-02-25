#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;


// ��� ���ϰ� �Ϸ��� 0��, 5�� �ε����� -1�� ä�� ��� ��ġ
deque<int>wheel[6];

// �� ��ϰ� ȸ���� �� �ִ°�
bool can_rot[6];

// 1�� ��� 3��° <-> 2�� ��� 7��°
// 2�� ��� 3��° <-> 3�� ��� 7��°
// 3�� ��� 3��° <-> 4�� ��� 7��°
// -> �ε����� -1��

// ���� ���� ���� �� -> �ٸ� ��Ϲ����� ������ x
// ���� �ٸ� ���� �� -> �ٸ� ��Ϲ����� �ݴ�� ������

string s;
int k, ans;
vector<pair<int, int>>v;

// ��ϰ� �ð�� ȸ�� ?
// ABCDEF -> FABCDE

// ��ϰ� �ݽð�� ȸ��?
// ABCDEF -> BCDEFA 

// �׷��ٸ� K���� ȸ���� ��ģ ��
// �� ��Ϲ����� �ð�, �ݽð�� �̵��� Ƚ���� �����Ͽ�
// �ش� Ƚ����ŭ ���������� 1���� ���� �̵������ָ� ���� �ʳ�?
// �ð���� �̵� +1, �ݽð���� �̵� -1

// ------------------------------------------------------------
// �ϳ��� �����°� �ƴ϶� ���ÿ� ������ ��... ��ͷ� Ǯ�ٰ� ����� �ٽ� ����


void check_rot(int now_wheel) {
	memset(can_rot, false, sizeof(can_rot));
	can_rot[now_wheel] = true;
	// ���� ��� ���� ������, ���������� ȸ�� ���� ��� ã��
	for (int i = now_wheel; i >= 1; i--) {
		if (wheel[i][6] != wheel[i - 1][2] && wheel[i - 1][2] != -1) {
			can_rot[i - 1] = true;
		}
		else {
			break;
		}
	}
	for (int i = now_wheel; i <= 4; i++) {
		if (wheel[i][2] != wheel[i + 1][6] && wheel[i + 1][6] != -1) {
			can_rot[i + 1] = true;
		}
		else {
			break;
		}
	}
}


void simulation() {


	for (int i = 0; i < k; i++) {


		int now_wheel = v[i].first;
		int now_dir = v[i].second;
		check_rot(now_wheel);


		int dirs[5] = { 0, };

		// ���� ��� �ð� ���� 
			// �� �ڸ� �� ������
			// ���� ��ϰ� ¦�� -> ¦���� �ð�, Ȧ���� �ݽð�
		if (now_dir == 1) {

			if (now_wheel % 2 == 0) {
				dirs[1] = -1;
				dirs[2] = 1;
				dirs[3] = -1;
				dirs[4] = 1;
			}
			else {
				dirs[1] = 1;
				dirs[2] = -1;
				dirs[3] = 1;
				dirs[4] = -1;
			}
		}
		else {
			if (now_wheel % 2 == 0) {
				dirs[1] = 1;
				dirs[2] = -1;
				dirs[3] = 1;
				dirs[4] = -1;
			}
			else {
				dirs[1] = -1;
				dirs[2] = 1;
				dirs[3] = -1;
				dirs[4] = 1;
			}
		}

		// ������ ��� Ȯ�� �� ó��

		for (int i = 1; i <= 4; i++) {

			if (can_rot[i]) {
				if (dirs[i] == 1) {
					// �ð���� 
					int temp = wheel[i].back();
					wheel[i].push_front(temp);
					wheel[i].pop_back();
				}
				else {
					// �ݽð����
					int temp = wheel[i].front();
					wheel[i].push_back(temp);
					wheel[i].pop_front();
				}
			}

		}

	}
}


int main() {
	for (int i = 0; i < 6; i++) {
		if (i >= 1 && i <= 4) {

			cin >> s;
			for (int j = 0; j < 8; j++) {
				wheel[i].push_back(s[j] - '0');
			}
		}
		else {
			for (int j = 0; j < 8; j++) {
				wheel[i].push_back(-1);
			}
		}
	}

	cin >> k;

	int num, dir;

	for (int i = 0; i < k; i++) {
		cin >> num >> dir;
		v.push_back({ num,dir });
	}

	simulation();

	for (int i = 1; i <= 4; i++) {
		if (wheel[i][0] == 1) {
			ans += pow(2, i - 1);
		}
	}
	cout << ans;
	return 0;
}