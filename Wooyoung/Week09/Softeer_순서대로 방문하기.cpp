#include<iostream>
#include<vector>
using namespace std;
int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };

bool visited[4][4];
bool must_visit[4][4];
int map[4][4];
int n, m;
int s_y, s_x, e_y, e_x;
int ans, cnt = 1;
struct pos {
    int y, x;
};
vector<pos>seq;
vector<pos>save;
bool isValid(int y, int x) {
    return y >= 0 && x >= 0 && y < n&& x < n && !visited[y][x] && map[y][x] == 0;
}
void func(int y, int x) {
    // 방문해야하는 지점을 모두 채운 경우

    if (cnt == m && y == e_y && x == e_x) {
        for (int i = 0; i < m; i++) {
            if (seq[i].y != save[i].y || seq[i].x != save[i].x)return;
        }
        ans++;
        return;
    }
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (!isValid(ny, nx))continue;
        visited[ny][nx] = true;
        if (must_visit[ny][nx]) {
            cnt++;
            save.push_back({ ny,nx });
            func(ny, nx);
            save.pop_back();
            cnt--;
        }
        else {
            func(ny, nx);
        }
        visited[ny][nx] = false;
    }
}

int main(int argc, char** argv)
{
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        int y, x;
        cin >> y >> x;
        must_visit[y - 1][x - 1] = true;
        seq.push_back({ y - 1,x - 1 });
        if (i == 0) {
            s_y = y - 1;
            s_x = x - 1;
        }
        if (i == m - 1) {
            e_y = y - 1;
            e_x = x - 1;

        }
    }
    visited[s_y][s_x] = true;
    save.push_back({ s_y,s_x });
    func(s_y, s_x);
    cout << ans;
    return 0;
}