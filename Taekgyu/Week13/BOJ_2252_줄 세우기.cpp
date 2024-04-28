#define _CRT_SECURE_NO_WARNINGS
#include<queue>
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
int M;
// 인접 리스트 저장 벡터
vector<int>v[32001];
// 내 앞에 몇개가 있냐~~~~~
int DAT[32001];

int main() {

	cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int fr, en = 0;
		cin >> fr >> en;
		v[fr].push_back(en);
		// en보다 fr이 앞에 있으니까
		// en번째 DAT에 +1을 추가한다
		// 저장된 값은 순서라고 생각한다
		DAT[en]++;
	}

	queue<int>q;

	// 앞에 있는 요소들은 미리 큐에 넣어버리자
	for (int i = 1; i <= N; i++)
	{
		// 가장 우선으로 오는 학생들은 미리 큐에 넣어버리자
		// 먼저 출력될 수 있게
		if (DAT[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		// q에 저장된 값은 앞에 아무것도 없는 큐의 요소들이 저장된다
		cout << now << " ";
		// 앞의 요소보다 뒤에 있는 요소가 있다면
		for (int i = 0; i < v[now].size(); i++)
		{
			// 그 뒤에 있는 요소의 순서를 -1 줄여준다
			DAT[v[now][i]]--;
			// 그 요소가 순서가 땡겨져서 0이 되면 q에 넣어 출력한다
			if (DAT[v[now][i]] == 0) {
				q.push(v[now][i]);
			}
		}
	}
	return 0;
}