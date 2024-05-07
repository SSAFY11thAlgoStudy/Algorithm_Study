#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int T;

//각각 친구를 저장할 배열
unordered_set<string>fr[200001];
//전체 인원수 저장할 map
unordered_map<string, int> mem;

int main() {

	//freopen("sample.txt", "r", stdin);
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int cnt = 0;
	cin >> T;
	for (int i = 0; i < T; i++) {

		//테케마다 초기화
		for (int i = 0; i < cnt; i++) {
			fr[i].clear();
		}
		mem.clear();

		int N;
		cin >> N;
		cnt = 0;

		for (int i = 0; i < N; i++) {
			string m1, m2;
			cin >> m1 >> m2;

			//각 맴버 전체 목록에 넣기
			mem.insert({ m1,cnt });
			cnt++;
			mem.insert({ m2,cnt });
			cnt++;

			//각 맴버의 번호 찾기
			auto it1 = mem.find(m1);
			int m1_ind = it1->second;

			auto it2 = mem.find(m2);
			int m2_ind = it2->second;

			//본인 넣기
			fr[m1_ind].insert(m1);
			fr[m2_ind].insert(m2);

			//뒷한테 앞사람 친구 목록 넣기
			for (string i : fr[m1_ind]) {
				fr[m2_ind].insert(i);
			}

			//앞사람한테 뒷사람 목록 넣기
			for (string i : fr[m2_ind]) {
				fr[m1_ind].insert(i);
			}

			cout << fr[m2_ind].size() << "\n";
		}
	}

	return 0;
}