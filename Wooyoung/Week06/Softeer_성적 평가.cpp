#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int n;
struct Info {
	int num, idx, grade;
};

bool compare(Info a, Info b) {
	return a.num > b.num;
}

struct compare2 {
	bool operator()(Info a, Info b) {
		return a.idx > b.idx;
	}
};


vector<Info>v[4];
priority_queue<Info, vector<Info>, compare2>pq[4];
Info sum[100001];
int grade[100001];
// 각 대회 등수 출력 및 최종 등수 출력 
int main() {
	cin >> n;
	int num;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < n; j++) {
			cin >> num;
			v[i].push_back({ num,j,0 });
			sum[j].num += num;
			sum[j].idx = j;
		}
	}

	for (int i = 0; i < n; i++) {
		v[3].push_back({ sum[i].num,sum[i].idx,0 });
	}

	for (int i = 0; i < 4; i++) {
		sort(v[i].begin(), v[i].end(), compare);
	}

	for (int i = 0; i < 4; i++) {
		pq[i].push({ v[i][0].num,v[i][0].idx,v[i][0].grade + 1 });
		int cur_grade = 1;
		int prev_grade = 1;
		for (int j = 1; j < n; j++) {
			Info now = v[i][j];
			Info prev = v[i][j - 1];
			if (now.num != prev.num) {
				cur_grade++;
				prev_grade = cur_grade;
				pq[i].push({ now.num,now.idx,cur_grade });
			}
			else {
				cur_grade++;
				pq[i].push({ now.num,now.idx,prev_grade });
			}
		}
	}



	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < n; j++) {
			cout << pq[i].top().grade << " ";
			pq[i].pop();
		}
		cout << "\n";
	}



	return 0;
}