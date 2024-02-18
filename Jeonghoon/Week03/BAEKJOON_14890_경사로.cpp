//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//
//using namespace std;
//
//int N, L;
//int map[101][101];
//int cnt;
//
//void input() {
//	cin >> N >> L;
//	for (int i = 0; i < N; i++){
//		for (int j = 0; j < N; j++){
//			cin >> map[i][j];
//		}
//	}
//}
//
//void solve1() {
//	for (int i = 0; i < N; i++){
//		int flag = 0;
//
//		for (int j = 1; j < N; j++){
//			if (j < L) {
//				if (map[i][j] != map[i][j - 1]) {
//					flag = 1;
//				}
//			}
//
//			if (j >= L && L > 0) {
//				if (map[i][j-1] != map[i][j]) {
//					for (int k = j - L; k < j-1; k++) {
//						if ((map[i][j] - map[i][k]) != 1) {
//							flag = 1;
//							break;
//						}
//					}
//				}
//			}
//
//			if (flag == 1) {
//				break;
//			}
//		}
//		if (flag == 0) {
//			cnt++;
//		}
//	}
//}
//
//int main() {
//	freopen("sample.txt", "r", stdin);
//
//	input();
//	solve1();
//	cout << cnt;
//	return 0;
//}