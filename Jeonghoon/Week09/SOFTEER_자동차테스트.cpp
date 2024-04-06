#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int n, q;
vector<int> v;
bool vis[1000000001];

void input() {

	cin >> n >> q;

	//입력받은 숫자 벡터에 저장
	//입력받은 숫자 표시
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		v.push_back(temp);
		vis[temp] = true;
	}

	//정렬
	sort(v.begin(), v.end());
}

void bs(int tar) {
	//이분 탐색
	//시작 인덱스 1
	//끝 인덱스 입력받은 마지막 인덱스
	int sp = 1;
	int ep = n - 1;

	while (1) {

		int r = (sp + ep) / 2;

		if (tar == v[r]) {
			//타겟 숫자를 찾으면
			//그 숫자기준 왼쪽 수 갯수 * 오른쪽 수 갯수
			cout << (n - r - 1) * r << "\n";
			break;
		}
		else if (tar > v[r]) {
			sp = r;
		}
		else {
			ep = r;
		}
	}
}

int main() {

	input();

	for (int i = 0; i < q; i++) {

		//타겟 숫자 하나씩 받기
		int temp;
		cin >> temp;

		// 맨 왼쪽이거나 오른쪽이면 경우의 수가 0개 이므로 0출력
		if (temp == v[0] || temp == v[n - 1]) {
			cout << 0 << "\n";
		}
		//입력 받지 않은 숫자도 0개로 출력
		else if (vis[temp] == false) {
			cout << 0 << "\n";
		}
		//있는 숫자면 이분탐색
		else {
			bs(temp);
		}
	}

	return 0;
}