#include <iostream>
using namespace std;
int arr[11][11] = { 0 }; //n이 1~10까지이므로 11로 초기화
int t, n;
void print(int tc) {
	arr[0][0] = 1;  // 첫번째 줄은 항상 1
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || j == 0) // 규칙을 찾아보면 i==j인데와 j==0인데는 항상 1이므로
				arr[i][j] = 1;
			else {
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
			} // 위에 왼쪽 대각선 + 위에 오른쪽 대각선 수의 합
		}
	}
	cout << "#" << tc + 1 << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) { //필요 없는 값들 제외 시키기 위해서 i까지
			if (arr[i][j] != 0) //0이 아니면 !
				cout << arr[i][j] << " ";
		}
		cout << '\n';
	}
}
int main() {
	cin >> t;
	for (int i = 0; i < t; i++) { //t개의 테스트케이스 
		cin >> n;
		print(i);  // 계산하고 출력하는 함수
	}

	return 0;
}