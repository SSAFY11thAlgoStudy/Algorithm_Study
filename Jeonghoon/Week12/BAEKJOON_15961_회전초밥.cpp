#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>

using namespace std;

int N, D, K, C;
//전체 초밥 입력
int sushi[30001];
//먹은갯수 확인하는 dat
int eat[3001];
//최종결과
int result;

void input() {
	cin >> N >> D >> K >> C;

	for (int i = 0; i < N; i++) {
		cin >> sushi[i];
	}
}

void solve() {
	//먹은걸 뒤로 저장하고 앞으로 빼야 하므로 queue 사용
	queue<int> q;
	//먹은 종류 카운트
	int t_cnt = 0;

	//queue 초기 설정을 위해 K개 먹고 queue에 저장
	for (int i = 0; i < K; i++) {
		q.push(sushi[i]);
		//종류 늘리기
		t_cnt++;
		//먹은갯수 늘리기
		eat[sushi[i]]++;

		//쿠폰이랑 같다면 맨 마지막에 더해주면 되므로 --
		if (sushi[i] == C) {
			t_cnt--;
			continue;
		}

		//이미 먹은 종류면은 --;
		if (eat[sushi[i]] > 1) {
			t_cnt--;
		}
	}

	//비교를 위한 max_cnt
	int max_cnt = t_cnt;

	for (int i = K; i < N + K - 1; i++) {
		//맨 앞에것 빼고
		int t = q.front();
		q.pop();
		//먹은 수 --
		eat[t]--;

		//만약 중복해서 먹은게 아니라면 종류 카운트 --
		if (eat[t] == 0) {
			t_cnt--;
		}

		//쿠폰이랑 같은경우 미리 카운트를 빼줬기 때문에 ++
		if (t == C && eat[C] == 0) {
			t_cnt++;
		}

		q.push(sushi[i % N]);
		t_cnt++;
		//중복이면 --
		if (eat[sushi[i % N]] != 0) {
			t_cnt--;
		}

		//쿠폰이랑 같고 처음 먹는다면 --;
		if (sushi[i % N] == C && eat[C] == 0) {
			t_cnt--;
		}

		eat[sushi[i % N]]++;

		if (t_cnt > max_cnt) {
			max_cnt = t_cnt;
		}
	}
	//최종 먹은 종류수 + 쿠폰 1종류
	result = max_cnt + 1;
}

int main() {

	//freopen("sample.txt", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	input();
	solve();

	cout << result;

	return 0;
}