#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<climits>
#define MAX INT_MAX
using namespace std;

int map[11][11];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,1,-1 };
int N, M, K;
int exit_y, exit_x;
int out_cnt;
struct Info {
    int y, x, score;
    bool isOut;
};

struct Info2 {
    int y, x, dist;
};

struct Cmp {
    bool operator()(Info2 a, Info2 b) {
        if (a.dist != b.dist) {
            return a.dist > b.dist;
        }
        else {
            if (a.y != b.y) {
                return a.y > b.y;
            }
            else {
                return a.x > b.x;
            }
        }
    }
};

vector<Info>Players;
void input() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
        }
    }
    int y, x;
    Players.push_back({ 0,0,0,true });
    for (int i = 1; i <= M; i++) {
        cin >> y >> x;
        Players.push_back({ y,x,0,false });
    }
    cin >> exit_y >> exit_x;
    map[exit_y][exit_x] = -1;
}

bool isValid(int y, int x) {
    return y >= 1 && x >= 1 && y <= N && x <= N && (map[y][x] == -1 || map[y][x] == 0);
}

bool movePlayers() {


    for (int i = 1; i < Players.size(); i++) {
        // 탈출한 참가자 이동 불가
        if (Players[i].isOut)continue;
        int cur_y = Players[i].y;
        int cur_x = Players[i].x;

        int cur_distance = abs(cur_y - exit_y) + abs(cur_x - exit_x);
        for (int j = 0; j < 4; j++) {
            int next_y = cur_y + dy[j];
            int next_x = cur_x + dx[j];

            // 벽 혹은 장외는 이동 불가
            if (!isValid(next_y, next_x))continue;

            int next_distance = abs(next_y - exit_y) + abs(next_x - exit_x);

            // 현재 거리보다 짧지 않은 경우 이동 불가
            if (next_distance >= cur_distance)continue;
            // 현재 거리보다 짧다면 다음 좌표 저장 후 다음 참가자 확인
            else {

                // 점수 획득
                Players[i].score++;

                // 출구인 경우 아웃 표시 
                if (next_distance == 0) {
                    out_cnt++;
                    Players[i].isOut = true;
                    if (out_cnt == M)return false;
                }
                // 출구가 아닌 경우 현재 플레이어 다음 좌표 등록
                else {
                    Players[i].y = next_y;
                    Players[i].x = next_x;
                }

                break;
            }

        }
    }
    return true;
}

priority_queue<Info2, vector<Info2>, Cmp> calAlldis() {
    // 플레이어 이동 후 플레이어 별로 출구와의 거리를 pq에 저장하여 반환
    priority_queue<Info2, vector<Info2>, Cmp>pq;
    // 두 점을 변으로 갖는 최소 길이 정사각형
    // 한 변의 길이 = dis (두 점의 y, x 차이 중 큰 값)
    // 정사각형의 좌상단 좌표(r,c)
    // (r,c)점을 기준으로 y,x 방향에 대해 dis만큼 정사각형을 그려야 한다
    // 만약 이를 충족하지 못하면 어쩔 수 없이 1로 이동한다.
    for (int i = 1; i < Players.size(); i++) {
        if (Players[i].isOut)continue;
        int dis_y = abs(Players[i].y - exit_y);
        int dis_x = abs(Players[i].x - exit_x);
        int dis = max(dis_y, dis_x);

        int r = max(Players[i].y, exit_y) - dis;
        int c = max(Players[i].x, exit_x) - dis;
        if (r < 1)r = 1;
        if (c < 1)c = 1;
        pq.push({ r,c,dis });

    }
    return pq;
}

void rotateMap() {

    priority_queue<Info2, vector<Info2>, Cmp>pq = calAlldis();
    Info2 rotPlayer = pq.top();
    int r = rotPlayer.y;
    int c = rotPlayer.x;
    int dis = rotPlayer.dist;

    // (r,c) 최상좌측 좌표, dis 한 변의 길이 
    // 플레이어 좌표를 플레이어 맵 카피본에 저장
    vector<int> c_pmap[11][11];
    for (int i = 1; i < Players.size(); i++) {
        if (Players[i].isOut)continue;
        int y = Players[i].y;
        int x = Players[i].x;
        c_pmap[y][x].push_back(i);
    }

    // 맵 좌표를 맵 카피본에 저장
    int c_map[11][11] = { 0, };
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            c_map[i][j] = map[i][j];
        }
    }

    int rot_x = c + dis;
    for (int i = r; i <= r + dis; i++) {
        int rot_y = r;
        for (int j = c; j <= c + dis; j++) {
            if (c_map[i][j] > 0)c_map[i][j]--;
            map[rot_y][rot_x] = c_map[i][j];
            // 플레이어 맵을 플레이어 벡터에 갱신
            if (!c_pmap[i][j].empty()) {
                for (auto p : c_pmap[i][j]) {
                    int player_num = p;
                    Players[player_num].y = rot_y;
                    Players[player_num].x = rot_x;
                }
            }

            if (map[rot_y][rot_x] == -1) {
                exit_y = rot_y;
                exit_x = rot_x;
            }
            rot_y++;
        }
        rot_x--;
    }


}

int main() {
    cin >> N >> M >> K;
    input();
    for (int i = 0; i < K; i++) {
        if (movePlayers()) {
            rotateMap();
        }
        else {
            break;
        }
    }
    int ans = 0;
    for (int i = 1; i <= M; i++) {
        ans += Players[i].score;
    }
    cout << ans << "\n";
    cout << exit_y << " " << exit_x;
    return 0;
}