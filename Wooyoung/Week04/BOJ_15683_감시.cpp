//#include<iostream>
//#include<cstring>
//#include<vector>
//#include<algorithm>
//#include<limits.h>
//#define MAX INT_MAX
//using namespace std;
//
//// 1�� ��,��,��,�� �� 1
//// 2�� ����, ���� �� 1
//// 3�� �ϵ�, ����, ����, ���� �� 1
//// 4�� ���ϼ�, �ϼ���, ������, ������ �� 1
//// 5�� �������� ��� ���� 
//// 6�� ��
//// CCTV�� �� ���⿡ ���� ��� �����ϸ�, ��(6)�� ���� ��� ���̻� ���� x 
//
//// CCTV�� ���� ���� �����ϴ� ��쿡�� ���ø� �ȹ޴� ������ ���� ���
//// 
//// ��ͷ� �� CCTV �� ������ �� �ִ� ��� ���⿡ ���� �Ѱ��� Ž��
//// ��� Ƚ���� CCTV�� ������ �� ���� ���ù��� �ʴ� ������ �Ź� �ִ�� ����
//
//int n, m, cnt_cctv, ans = MAX;
//int map[10][10];
//// �� �� �� ��
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
//	// ���������� cpy_temp ����� ���� ��Ϳ��� ����� ������ ���� ��Ϳ� �״�� �ݿ� �Ǵ� ������ ����
//	// �ѹ� �Ҵ�� �޸𸮿� ����ؼ� �����ǹǷ� ����� ����
//	// ��� ȣ�� ���� ���ο� �޸𸮿� �Ҵ��Ͽ� �����ؾ���
//
//	// ��� CCTV�� ���ø� ��ħ
//	if (depth == cnt_cctv) {
//		// ���� temp�� ����� 0�� ������ ���� ���� �ִ밪�� ����
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
//		// ��,��,��,�� �� 1
//		if (now_num == 1) {
//			for (int j = 0; j < 4; j++) {
//				// ��͸� ���� ������ 
//				// memcpy(cpy_temp, temp,sizeof(temp));�� �� ���
//				// �Լ��� �Ķ���ͷ� ���� �迭�� �迭�� ����Ű�� �������̴�.
//				// �׷��Ƿ�, sizeof(temp)�� int�� ũ���� 4����Ʈ�� ��ϵȴ�.
//				// �̷��� ����� ��� ���� ���簡 �ȵȴ�. (����!)
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
//				// �� ���⿡ ���� ���ø� �������� ���� CCTV�� �̵� (���)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//
//		// ��,�� �Ǵ� ��,�� �� 1
//		else if (now_num == 2) {
//			for (int j = 0; j < 2; j++) {
//				// ��͸� ���� ������ 
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
//				// ���� �Ǵ� �¿� ���⿡ ���� ���ø� �������� ���� CCTV�� �̵� (���)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//
//		// �� ��, �� ��, �� ��, �� �� �� 1
//
//		else if (now_num == 3) {
//			for (int j = 0; j < 4; j++) {
//				// ��͸� ���� ������ 
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
//				// ���� �Ǵ� �¿� ���⿡ ���� ���ø� �������� ���� CCTV�� �̵� (���)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//		// 012, 123, 230, 301
//		else if (now_num == 4) {
//			for (int j = 0; j < 4; j++) {
//				// ��͸� ���� ������ 
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
//				// ���� �Ǵ� �¿� ���⿡ ���� ���ø� �������� ���� CCTV�� �̵� (���)
//				recur(depth + 1, cpy_temp);
//			}
//		}
//
//
//		else if (now_num == 5) {
//			// ��͸� ���� ������ 
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
//			// �����¿� ���⿡ ���� ���ø� �������� ���� CCTV�� �̵� (���)
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

    // ���� ������Ʈ �� �ٽ� ������Ű�� ���� temp �迭
    // ���� map�� ������ ��, ��͹� ���� �� map�� �ٽ� temp ���� 
    int temp[10][10];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp[i][j] = map[i][j];
        }
    }

    // cctv�� ��ǥ, ��ȣ
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