#include <iostream>
#include <algorithm>
using namespace std;

int n;
long long solution[5001];
long long res1, res2, res3;
long long temp = 4000000001;

void bs() {
	//i값을 고정 시킬 것이므로 for문써서 하나 값 고정
	//세개씩 고를 것이므로 n-2까지
	for (int i = 0; i < n - 2; i++) {
		//i값 고정으로 더해주고 그 다음거부터 이분 탐색 시작
		int st = i + 1;
		int ed = n - 1;

		//중복 안되므로 등호 빼주기
		while (st < ed) {
			long long a = solution[i] + solution[st] + solution[ed];
			//0이면 바로 답이므로 return
			if (a == 0) {
				res1 = solution[i];
				res2 = solution[st];
				res3 = solution[ed];
				return;
			}
			//temp가 현재 더한 값의 절댓값보다 크다면 용액들 갱신해주기
			if (temp > abs(a)) {
				temp = abs(a);
				res1 = solution[i];
				res2 = solution[st];
				res3 = solution[ed];
			}
			//세용액 더한 값이 0보다 작고 temp보다 절댓값이 크다면 
			//앞에서 늘려주기
			if (a < 0) st++;
			//세용액 더한 값이 0보다 크고 temp보다 절댓값이 크다면
			//끝에서 줄여주기
			else ed--;
		}
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) cin >> solution[i];
	//이분탐색을 위한 오름차순 정렬
	sort(solution, solution + n);

	bs();
	cout << res1 << " " << res2 << " " << res3;
}