#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;


// 계산 편하게 하려고 0번, 5번 인덱스에 -1로 채운 톱니 설치
deque<int>wheel[6];

// 각 톱니가 회전할 수 있는가
bool can_rot[6];

// 1번 톱니 3번째 <-> 2번 톱니 7번째
// 2번 톱니 3번째 <-> 3번 톱니 7번째
// 3번 톱니 3번째 <-> 4번 톱니 7번째
// -> 인덱스라 -1씩

// 서로 같은 값일 때 -> 다른 톱니바퀴는 움직임 x
// 서로 다른 값일 때 -> 다른 톱니바퀴는 반대로 움직임

string s;
int k, ans;
vector<pair<int, int>>v;

// 톱니가 시계로 회전 ?
// ABCDEF -> FABCDE

// 톱니가 반시계로 회전?
// ABCDEF -> BCDEFA 

// 그렇다면 K번의 회전을 마친 후
// 각 톱니바퀴가 시계, 반시계로 이동한 횟수를 저장하여
// 해당 횟수만큼 최종적으로 1번만 값을 이동시켜주면 되지 않나?
// 시계방향 이동 +1, 반시계방향 이동 -1

// ------------------------------------------------------------
// 하나씩 돌리는게 아니라 동시에 돌리는 것... 재귀로 풀다가 지우고 다시 시작


void check_rot(int now_wheel) {
	memset(can_rot, false, sizeof(can_rot));
	can_rot[now_wheel] = true;
	// 현재 톱니 기준 좌측끝, 우측끝까지 회전 가능 톱니 찾기
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

		// 현재 톱니 시계 방향 
			// 맨 뒤를 맨 앞으로
			// 현재 톱니가 짝수 -> 짝수는 시계, 홀수는 반시계
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

		// 가능한 톱니 확인 후 처리

		for (int i = 1; i <= 4; i++) {

			if (can_rot[i]) {
				if (dirs[i] == 1) {
					// 시계방향 
					int temp = wheel[i].back();
					wheel[i].push_front(temp);
					wheel[i].pop_back();
				}
				else {
					// 반시계방향
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