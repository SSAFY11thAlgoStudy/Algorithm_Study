#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	for (int t = 0; t < 10; t++) {
		int n, n1;
		cin >> n;
		vector<int> arr; // 원본 암호문 입력 받기 위한 벡터
		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			arr.push_back(a);
		}
		cin >> n1;
		for (int i = 0; i < n1; i++) {
			char s;   // I 받기
			int x, y; // x의 위치 y개 명령어 
			cin >> s >> x >> y;
			vector<int> temp;  // y개 명령어 받기 위한 벡터 
			for (int j = 0; j < y; j++) {
				int num;
				cin >> num;
				temp.push_back(num);
			}
			arr.insert(arr.begin() + x, temp.begin(), temp.end());
			// arr의 시작 위치 + x부터 시작 해서 temp 배열 그대로 넣기																											
		}
		cout << "#" << t + 1 << " ";
		for (int i = 0; i < 10; i++)
			cout << arr[i] << " ";
		cout << '\n';
	}
	return 0;
}