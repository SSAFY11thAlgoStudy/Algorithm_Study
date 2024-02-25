#include <iostream>
#include <vector>
using namespace std;

int n;
int dragon[101][101];
int dx[4] = { 0, -1, 0, 1 }; // 0,1,2,3에 맞게 방향 배열 만듬
int dy[4] = { 1, 0, -1, 0 };
void curve(int x, int y, int d, int g) {
    vector<int> v; // 이전 방향 값을 저장하기 위한 벡터
    v.push_back(d);
    dragon[x][y] = 1; // 시작점 = 1
    x += dx[d];  //d방향 만큼 움직여주고
    y += dy[d];
    dragon[x][y] = 1; // 끝점 = 1

    for (int i = 0; i < g; i++) { // g세대만큼 돌아야하므로
        for (int j = v.size() - 1; j >= 0; j--) { // 1->2->3->2 => 3->0->3->2 그 전 방향 값에 마지막 수 +1이
            int dir = (v[j] + 1) % 4;          // 다음 세대 드래곤 커브 방향임
            x += dx[dir];
            y += dy[dir];
            dragon[x][y] = 1;
            v.push_back(dir); // 다음 세대를 위해 방향 값 넣어주기 
        }
    }
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, d, g;
        cin >> y >> x >> d >> g; //x,y가 편해서 y먼저 입력 받음
        curve(x, y, d, g);
    }
    int res = 0;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            if (dragon[i][j] == 1 && dragon[i][j + 1] == 1 && dragon[i + 1][j] == 1 && dragon[i + 1][j + 1] == 1) {
                res++; // 네 꼭짓점 모두 1(드래곤 커브의 일부)이면 res++
            }
        }
    }
    cout << res;
    return 0;
}