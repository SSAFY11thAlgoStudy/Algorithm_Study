#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct fight {
    int r, c, h, w, k, health;
    bool live;
};

int l, n, q;
int map[41][41]; //장애물 벽 맵
int knight[41][41]; //기사들 위치 맵
int dy[4] = { -1,0,1,0 }; //상우하좌
int dx[4] = { 0,1,0,-1 };
vector<fight> v;
vector<int> crash;

void command(int idx, int d) {
    if (!v[idx].live) return; //사라졌으면 바로 return
    bool visited[41][41] = { false }; //방문 배열 이미 체크한 거는 또 갈필요 없으니
    queue<pair<int, int>> q;
    //현재 idx에 해당하는 기사의 좌표 값들 q에 넣어주기
    for (int i = v[idx].r; i < v[idx].r + v[idx].h; i++) {
        for (int j = v[idx].c; j < v[idx].c + v[idx].w; j++) {
            q.push({ i,j });
            visited[i][j] = true;
        }
    }
    //벽 있는지 판단
    int flag = 1;
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        int ny = y + dy[d];
        int nx = x + dx[d];
        //범위 안에 있고 d방향으로 이동한게 벽이 아니고
        if (ny <= l && ny >= 1 && nx <= l && nx >= 1 && map[ny][nx] != 2) {
            //방문하지 않았는데
            if (!visited[ny][nx]) {
                //다른 기사 라면
                if (knight[ny][nx] > 0) {
                    int nidx = knight[ny][nx];
                    crash.push_back(nidx);
                    //다른 기사에 대해서도 벽이 있는지 조사해야하므로 q에 넣어주고 방문체크
                    for (int i = v[nidx].r; i < v[nidx].r + v[nidx].h; i++) {
                        for (int j = v[nidx].c; j < v[nidx].c + v[nidx].w; j++) {
                            q.push({ i,j });
                            visited[i][j] = true;
                        }
                    }
                }
            }
        }
        //벽이라면
        else {
            flag = 0;
            crash.clear(); //벽 판단하기전에 들어가져 있는거 없애줘야함
            break;
        }
    }
    //벽이라면 바로 이동할 수 없으니 끝내면 됨
    if (!flag) return;
    //기사 이동한거 넣어주고 원래 맵에 옮겨주기 위함
    int knight_save[41][41] = { 0 };
    //명령받은 기사 이동시키기
    for (int i = v[idx].r; i < v[idx].r + v[idx].h; i++) {
        for (int j = v[idx].c; j < v[idx].c + v[idx].w; j++) {
            knight[i][j] = 0; //이동했으므로 0으로 초기화 해주기
            //knight[i + dy[d]][j + dx[d]] = idx + 1; //기사 해당방향으로 이동시켜주기
            knight_save[i + dy[d]][j + dx[d]] = idx;
        }
    }
    //idx에 해당하는 기사 좌표 업데이트
    v[idx].r += dy[d];
    v[idx].c += dx[d];


    //밀린 기사 수에 맞게 이동시키기
    for (int i = 0; i < crash.size(); i++) {
        int nidx = crash[i];
        for (int j = v[nidx].r; j < v[nidx].r + v[nidx].h; j++) {
            for (int t = v[nidx].c; t < v[nidx].c + v[nidx].w; t++) {
                //knight[i + dy[d]][j + dx[d]] = nidx+1;
                knight[j][t] = 0; //기사 이동했으므로 0으로 초기화 해주기
                knight_save[j + dy[d]][t + dx[d]] = nidx;
            }
        }
        //nidx에 해당하는 기사 좌표 업데이트
        v[nidx].r += dy[d];
        v[nidx].c += dx[d];
    }
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            //기사 이동한게 있는 거만 원래 기사 맵에 넣어줘야함
            if (knight_save[i][j]) knight[i][j] = knight_save[i][j];
        }
    }
}

void damage() {
    //밀린 기사 수에 맞게 데미지 줘야함
    for (int i = 0; i < crash.size(); i++) {
        int idx = crash[i];
        for (int j = v[idx].r; j < v[idx].r + v[idx].h; j++) {
            for (int t = v[idx].c; t < v[idx].c + v[idx].w; t++) {
                //장애물이 있을때만
                if (map[j][t] == 1) {
                    //피는 -1닳게하고 데미지 점수는 +1 해주기
                    v[idx].k -= 1;
                    v[idx].health += 1;
                    //체력 없어지면 바로 기사 사라지게 하기
                    if (v[idx].k <= 0) {
                        v[idx].live = false;
                        for (int a = v[idx].r; a < v[idx].r + v[idx].h; a++) {
                            for (int b = v[idx].c; b < v[idx].c + v[idx].w; b++) {
                                knight[a][b] = 0;
                            }
                        }
                    }
                }
            }
        }

    }
}

int main() {
    cin >> l >> n >> q;
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= l; j++) {
            cin >> map[i][j];
        }
    }
    //-1해줬는데 귀찮아서 v[0]을 채워주는 걸로 바꿈
    v.push_back({ 0,0,0,0,0,0,true });
    for (int i = 1; i <= n; i++) {
        int r, c, h, w, k;
        cin >> r >> c >> h >> w >> k;
        v.push_back({ r,c,h,w,k,0,true });
        for (int y = r; y < r + h; y++) {
            for (int x = c; x < c + w; x++) {
                knight[y][x] = i;
            }
        }
    }
    for (int i = 1; i <= q; i++) {
        int x, d;
        cin >> x >> d;
        command(x, d);
        damage(); //다 밀고 나서 데미지 주기
        crash.clear();//다음 턴을 위해 clear해주기
    }
    int res = 0;
    //생존한 기사들의 데미지만 합산
    for (int i = 1; i <= n; i++) {
        if (v[i].live) res += v[i].health;
    }
    cout << res;
    return 0;
}