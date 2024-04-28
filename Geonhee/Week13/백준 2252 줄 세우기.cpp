#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int dat[32001];
vector<int> student[32001];

void line_up() {
	//먼저 들어간게 먼저 나와야하므로 q사용
	queue<int> q;
	//아무나 앞에서도 상관 없는 것들을 q에 넣어주기
	for (int i = 1; i <= n; i++) {
		if (!dat[i]) q.push(i);
	}
	for (int i = 0; i < n; i++) {
		//q에 있는거 출력
		int now = q.front();
		q.pop();
		cout << now << " ";
		//현재 now :{}에 있는 것들에 대해서 조사
		for (int x : student[now]) {
			//dat[x]1빼주기
			dat[x]--;
			//만약 dat[x]가 0이라면 이제 줄 세워도 되므로 q에 넣어주기
			if (!dat[x]) q.push(x);
		}
	}

}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		//a다음으로 b가 나와야하므로 a:{b} 이렇게 넣어주고
		student[a].push_back(b);
		//b가 뒤에 나와야할  횟수를 dat배열에 저장
		dat[b]++;
	}
	line_up();
	return 0;
}
//처음에는 dat[a]++해서 넣어줘서 위에서 1인것들에 대해서
//q에 넣어줬더니
//4 3
//4 2
//3 1
//2 3
//이렇게 2가 4보다 뒤에 나와야하는데 q에 넣을때 4보다 먼저 들어가서 먼저 출력되는 경우가 있어서
//반대로 뒤에 나와야하는 것들에 대해서 dat배열에 횟수를 저장해서 해줬더니 통과함
//뒤에 나와야하는 것들에 대해서 저장하면 a에 나왔더라도 b에 한번이라도 나오면
//q에 추가가 안되므로 뒤에 나와야하는 것들에 대해서 횟수를 세주는 것이 맞다고 판단
