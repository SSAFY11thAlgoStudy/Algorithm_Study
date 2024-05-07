#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>

using namespace std;

/*
알고리즘 월말평가랑 같은 문제
그때는 벡터로 받아서 퀵소트하고 지우고 넣고 반복해서
시간초과가 났으니
이번에는 힙소트로 풀기
*/

int N;
int result;

//힙소트 하기위한 조건
struct Num {
    int cost;
    bool operator<(Num right) const {
        if (cost < right.cost) return false;
        if (cost > right.cost) return true;
        return false;
    }
};

priority_queue<Num>pq;

//맨 앞에 2개 빼고 
//그 2개 합해서
//다시 넣기
void solve() {
    auto a = pq.top();
    pq.pop();
    auto b = pq.top();
    pq.pop();

    int s = a.cost + b.cost;
    result += s;
    pq.push({ s });
}

int main() {

	freopen("sample.txt", "r", stdin);

	cin >> N;

	for (int i = 0; i < N; i++){
        int temp;
        cin >> temp;
        pq.push({temp });
	}

    while (pq.size() > 1) {
        solve();
    }

    cout << result;

	return 0;
}