//#include<iostream>
//#include<cstring>
//#include<vector>
//#include<algorithm>
//#include<limits.h>
//#define MAX INT_MAX
//using namespace std;
//
//// 1번 동,서,남,북 중 1
//// 2번 가로, 세로 중 1
//// 3번 북동, 동남, 남서, 서북 중 1
//// 4번 동북서, 북서남, 서남동, 남동북 중 1
//// 5번 동서남북 모든 방향 
//// 6번 벽
//// CCTV는 각 방향에 대해 모두 감시하며, 벽(6)을 만날 경우 더이상 감지 x 
//
//// CCTV로 가장 많이 감시하는 경우에서 감시를 안받는 영역의 개수 출력
//// 
//// 재귀로 각 CCTV 별 감시할 수 있는 모든 방향에 대해 한개씩 탐색
//// 재귀 횟수가 CCTV의 개수일 때 현재 감시받지 않는 영역을 매번 최대로 갱신
//
//int n, m, cnt_cctv, ans = MAX;
//int map[10][10];
//// 북 동 남 서
//int dy[4] = { -1,0,1,0 };
//int dx[4] = { 0,1,0,-1 };
//
//
//
//struct Node {
//	int y, x, num;
//};
//vector<Node>v;
//
//bool isValid(int y, int x, int temp[10][10]) {
//	return y >= 0 && x >= 0 && y < n&& x < m&& temp[y][x] >= -1 && temp[y][x] <= 5;
//}
//
//
//void recur(int depth, int temp[10][10]) {
//
//	// 전역변수로 cpy_temp 선언시 이전 재귀에서 변경된 내용이 다음 재귀에 그대로 반영 되는 문제가 있음
//	// 한번 할당된 메모리에 계속해서 누적되므로 생기는 문제
//	// 재귀 호출 마다 새로운 메모리에 할당하여 복사해야함
//
//	// 모든 CCTV가 감시를 마침
//	if (depth == cnt_cctv) {
//		// 현재 temp에 저장된 0의 개수를 세어 가장 최대값을 갱신
//		int cnt = 0;
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < m; j++) {
//				if (temp[i][j] == 0) {
//					cnt++;
//				}
//			}
//		}
//		ans = min(ans, cnt);
//		return;
//	}
//	int cpy_temp[10][10];
//	for (int i = depth; i < v.size(); i++) {
//		int now_y = v[i].y;
//		int now_x = v[i].x;
//		int now_num = v[i].num;
//
//		// 상,하,좌,우 중 1
//		if (now_num == 1) {
//			for (int j = 0; j < 4; j++) {
//				// 재귀를 위한 복제본 
//				// memcpy(cpy_temp, temp,sizeof(temp));를 할 경우
//				// 함수의 파라미터로 받은 배열은 배열을 가리키는 포인터이다.
//				// 그러므로, sizeof(temp)는 int의 크기인 4바이트가 등록된다.
//				// 이렇게 사용할 경우 값이 복사가 안된다. (주의!)
//				memcpy(cpy_temp, temp, sizeof(cpy_temp));
//				int next_y = now_y + dy[j];
//				int next_x = now_x + dx[j];
//				if (!isValid(next_y, next_x, cpy_temp))continue;
//				while (isValid(next_y, next_x, cpy_temp)) {
//					if (cpy_temp[next_y][next_x] == 0) {
//						cpy_temp[next_y][next_x] = -1;
//					}
//					next_y += dy[j];
//					next_x += dx[j];
//				}
//				// 한 방향에 대한 감시를 마쳤으니 다음 CCTV로 이동 (재귀)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//
//		// 상,하 또는 좌,우 중 1
//		else if (now_num == 2) {
//			for (int j = 0; j < 2; j++) {
//				// 재귀를 위한 복제본 
//				memcpy(cpy_temp, temp, sizeof(cpy_temp));
//				int next_y1 = now_y + dy[j];
//				int next_x1 = now_x + dx[j];
//				int next_y2 = now_y + dy[j + 2];
//				int next_x2 = now_x + dx[j + 2];
//				if (!isValid(next_y1, next_x1, cpy_temp) && !isValid(next_y2, next_x2, cpy_temp))continue;
//				while (isValid(next_y1, next_x1, cpy_temp)) {
//					if (cpy_temp[next_y1][next_x1] == 0) {
//						cpy_temp[next_y1][next_x1] = -1;
//					}
//					next_y1 += dy[j];
//					next_x1 += dx[j];
//				}
//				while (isValid(next_y2, next_x2, cpy_temp)) {
//					if (cpy_temp[next_y2][next_x2] == 0) {
//						cpy_temp[next_y2][next_x2] = -1;
//					}
//					next_y2 += dy[j + 2];
//					next_x2 += dx[j + 2];
//				}
//				// 상하 또는 좌우 방향에 대한 감시를 마쳤으니 다음 CCTV로 이동 (재귀)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//
//		// 상 우, 상 좌, 남 좌, 남 우 중 1
//
//		else if (now_num == 3) {
//			for (int j = 0; j < 4; j++) {
//				// 재귀를 위한 복제본 
//				memcpy(cpy_temp, temp, sizeof(cpy_temp));
//				int next_y1 = now_y + dy[j];
//				int next_x1 = now_x + dx[j];
//				int next_y2 = now_y + dy[(j + 1) % 4];
//				int next_x2 = now_x + dx[(j + 1) % 4];
//				if (!isValid(next_y1, next_x1, cpy_temp) && !isValid(next_y2, next_x2, cpy_temp))continue;
//
//				while (isValid(next_y1, next_x1, cpy_temp)) {
//					if (cpy_temp[next_y1][next_x1] == 0) {
//						cpy_temp[next_y1][next_x1] = -1;
//					}
//					next_y1 += dy[j];
//					next_x1 += dx[j];
//				}
//				while (isValid(next_y2, next_x2, cpy_temp)) {
//					if (cpy_temp[next_y2][next_x2] == 0) {
//						cpy_temp[next_y2][next_x2] = -1;
//					}
//					next_y2 += dy[(j + 1) % 4];
//					next_x2 += dx[(j + 1) % 4];
//				}
//				// 상하 또는 좌우 방향에 대한 감시를 마쳤으니 다음 CCTV로 이동 (재귀)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//		// 012, 123, 230, 301
//		else if (now_num == 4) {
//			for (int j = 0; j < 4; j++) {
//				// 재귀를 위한 복제본 
//				memcpy(cpy_temp, temp, sizeof(cpy_temp));
//				int next_y1 = now_y + dy[j];
//				int next_x1 = now_x + dx[j];
//				int next_y2 = now_y + dy[(j + 1) % 4];
//				int next_x2 = now_x + dx[(j + 1) % 4];
//				int next_y3 = now_y + dy[(j + 2) % 4];
//				int next_x3 = now_x + dx[(j + 2) % 4];
//				if (!isValid(next_y1, next_x1, cpy_temp) && !isValid(next_y2, next_x2, cpy_temp)
//					&& !isValid(next_y3, next_x3, cpy_temp))continue;
//
//				while (isValid(next_y1, next_x1, cpy_temp)) {
//					if (cpy_temp[next_y1][next_x1] == 0) {
//						cpy_temp[next_y1][next_x1] = -1;
//					}
//					next_y1 += dy[j];
//					next_x1 += dx[j];
//				}
//				while (isValid(next_y2, next_x2, cpy_temp)) {
//					if (cpy_temp[next_y2][next_x2] == 0) {
//						cpy_temp[next_y2][next_x2] = -1;
//					}
//					next_y2 += dy[(j + 1) % 4];
//					next_x2 += dx[(j + 1) % 4];
//				}
//				while (isValid(next_y3, next_x3, cpy_temp)) {
//					if (cpy_temp[next_y3][next_x3] == 0) {
//						cpy_temp[next_y3][next_x3] = -1;
//					}
//					next_y3 += dy[(j + 2) % 4];
//					next_x3 += dx[(j + 2) % 4];
//				}
//				// 상하 또는 좌우 방향에 대한 감시를 마쳤으니 다음 CCTV로 이동 (재귀)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//
//
//		else if (now_num == 5) {
//			// 재귀를 위한 복제본 
//			memcpy(cpy_temp, temp, sizeof(cpy_temp));
//			for (int j = 0; j < 4; j++) {
//				int next_y = now_y + dy[j];
//				int next_x = now_x + dx[j];
//				if (!isValid(next_y, next_x, cpy_temp))continue;
//				while (isValid(next_y, next_x, cpy_temp)) {
//					if (cpy_temp[next_y][next_x] == 0) {
//						cpy_temp[next_y][next_x] = -1;
//					}
//					next_y += dy[j];
//					next_x += dx[j];
//				}
//			}
//			// 상하좌우 방향에 대한 감시를 마쳤으니 다음 CCTV로 이동 (재귀)
//			recur(depth + 1, cpy_temp);
//		}
//	}
//}
//
//int main() {
//	cin >> n >> m;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < m; j++) {
//			cin >> map[i][j];
//			if (map[i][j] >= 1 && map[i][j] <= 5) {
//				cnt_cctv++;
//				v.push_back({ i,j,map[i][j] });
//			}
//		}
//	}
//
//	recur(0, map);
//
//	cout << ans;
//
//	return 0;
//}


#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#define MAX INT_MAX
using namespace std;


int n, m, ans = MAX;
int map[10][10];
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
vector<pair<int, int>> cctv;

void update(int y, int x, int dir) {
    while (true) {
        y += dy[dir];
        x += dx[dir];
        if (y < 0 || y >= n || x < 0 || x >= m || map[y][x] == 6) break;
        if (map[y][x] == 0) map[y][x] = -1;
    }
}

void recover(int temp[10][10]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            map[i][j] = temp[i][j];
        }
    }
}

void dfs(int depth) {
    if (depth == cctv.size()) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == 0) cnt++;
            }
        }
        ans = min(ans, cnt);
        return;
    }

    // 값을 업데이트 후 다시 복구시키기 위한 temp 배열
    // 현재 map을 복사한 후, 재귀문 종료 후 map에 다시 temp 저장 
    int temp[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[i][j] = map[i][j];
        }
    }

    // cctv의 좌표, 번호
    int y = cctv[depth].first;
    int x = cctv[depth].second;
    int num = map[y][x];

    if (num == 1) {
        for (int d = 0; d < 4; d++) {
            update(y, x, d);
            dfs(depth + 1);
            recover(temp);
        }
    }
    else if (num == 2) {
        for (int d = 0; d < 2; d++) {
            update(y, x, d);
            update(y, x, d + 2);
            dfs(depth + 1);
            recover(temp);
        }
    }
    else if (num == 3) {
        for (int d = 0; d < 4; d++) {
            update(y, x, d);
            update(y, x, (d + 1) % 4);
            dfs(depth + 1);
            recover(temp);
        }
    }
    else if (num == 4) {
        for (int d = 0; d < 4; d++) {
            update(y, x, d);
            update(y, x, (d + 1) % 4);
            update(y, x, (d + 2) % 4);
            dfs(depth + 1);
            recover(temp);
        }
    }
    else if (num == 5) {
        for (int d = 0; d < 4; d++) {
            update(y, x, d);
        }
        dfs(depth + 1);
        recover(temp);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            if (map[i][j] >= 1 && map[i][j] <= 5) {
                cctv.push_back({ i, j });
            }
        }
    }

    dfs(0);

    cout << ans;

    return 0;
}