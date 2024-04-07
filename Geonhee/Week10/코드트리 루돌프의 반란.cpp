#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int n, m, p, c, d;
int ry, rx;
int map[52][52] = { 0 };
int dy[4] = { -1,0,1,0 }; //0123 상우하좌
int dx[4] = { 0,1,0,-1 };
bool santa_live[32] = { false }; //산타가 살아 있는지
pair<int, int> santa_location[32]; //번호에 따른 산타 좌표 
int final_score[32];
int stun_santa[1004];

//연쇄충돌 확인 및 일반충돌 처리 
//c만큼 밀린 y,x좌표, 해당 방향으로 1밀리기 위한 y,x 현재 산타 번호
void crash(int cy, int cx, int my, int mx, int s_num) {
    //첫번째 충돌한 산타처리
    int idx = map[cy][cx];
    map[cy][cx] = s_num;
    santa_location[s_num] = { cy,cx };

    //그 다음 연쇄로 충돌한 산타 처리
    int newy = cy + my;
    int newx = cx + mx;
    //범위 넘어가면 바로 out
    if (newy > n || newy < 1 || newx > n || newx < 1) {
        santa_live[idx] = false;
        santa_location[idx] = { 0,0 };
        return;
    }
    else {
        //밀렸는데 또 연쇄라면 다시 재귀
        if (map[newy][newx] > 0) crash(newy, newx, my, mx, idx);
        //밀렸는데 비었으면 넣고 끝
        else {
            map[newy][newx] = idx;
            santa_location[idx] = { newy,newx };
            return;
        }
    }
}


//루돌프의 움직임
//루돌프 이동, 산타와 충돌하면 산타 밀어주고 루돌프의 힘에 해당하는 점수 해당 산타에 더해주기
//연쇄적으로 충돌하는 경우도 생각
void move_dear(int y, int x, int turn) {
    int santa_num = 0; //가까운 산타 번호
    int mind = 1e9; //가까운 거리
    pair<int, int> same_distance; //가까운 산타 좌표 

    //가까운 거리 찾기(산타의 수 만큼)
    for (int i = 1; i <= p; i++) {
        //산타 죽었으면 continue
        if (!santa_live[i]) continue;
        //현재 루돌프와 산타[i]의 거리
        int nowd = pow((ry - santa_location[i].first), 2) + pow((rx - santa_location[i].second), 2);
        //비교해서 가까운 산타 찾아주기
        if (mind > nowd) {
            mind = nowd;
            same_distance = { santa_location[i].first,santa_location[i].second };
            santa_num = i;
        }
        //같으면 y좌표,x좌표 순으로 비교해서 산타 찾아주기 
        else if (mind == nowd) {
            if (same_distance.first == santa_location[i].first) {
                if (same_distance.second > santa_location[i].second) continue;
                else {
                    same_distance = { santa_location[i].first,santa_location[i].second };
                    santa_num = i;
                }
            }
            else if (same_distance.first > santa_location[i].first) continue;
            else {
                same_distance = { santa_location[i].first,santa_location[i].second };
                santa_num = i;
            }
        }
    }

    //가까운 산타 찾았으므로 루돌프 이동 시키기

    //가까운 산타가 존재하면 움직임 시작 없으면 살아있는 산타 X이므로 끝내야함
    if (santa_num) {
        int tempry = ry, temprx = rx;
        int movey, movex;
        if (ry - same_distance.first < 0) movey = 1;
        else if (ry - same_distance.first > 0)movey = -1;
        else movey = 0;
        if (rx - same_distance.second < 0) movex = 1;
        else if (rx - same_distance.second > 0) movex = -1;
        else movex = 0;
        //루돌프 이동 및 이전 루돌프 위치 0
        ry += movey;
        rx += movex;
        //map[ry][rx] = -1;
        map[tempry][temprx] = 0;
        //루돌프 이동 했는데 산타가 있을 경우
        if (same_distance.first == ry && same_distance.second == rx) {
            //스턴
            //산타 움직일때 turn+1보다 크면 다시 움직일 수 있음
            stun_santa[santa_num] = turn + 1;
            int tempy = same_distance.first + movey * c;
            int tempx = same_distance.second + movex * c;
            //범위 넘어가면
            if (tempy > n || tempy < 1 || tempx > n || tempx < 1) {
                final_score[santa_num] += c;
                santa_live[santa_num] = false; //산타 탈락
                map[same_distance.first][same_distance.second] = 0; //탈락한 산타 위치 초기화
                santa_location[santa_num] = { 0,0 }; //탈락한 산타 위치 초기화
                map[ry][rx] = -1;
                return;
            }
            //범위 맞고 0보다 크면 연쇄충돌 처리
            if (map[tempy][tempx] > 0) {
                //연쇄충돌 처리
                //c만큼 밀린 y,x좌표, 해당 방향으로 1밀리기 위한 y,x 현재 산타 번호
                crash(tempy, tempx, movey, movex, santa_num);

            }
            //일반충돌
            else {
                map[same_distance.first][same_distance.second] = 0;
                map[tempy][tempx] = santa_num;
                santa_location[santa_num] = { tempy,tempx };
            }
            final_score[santa_num] += c; //해당하는 산타 번호에 c만큼 점수 더해주기
        }
    }
    //루돌프 좌표 값 넣어주기
    map[ry][rx] = -1;
}

//산타의 움직임
void move_santa(int turn) {
    for (int i = 1; i <= p; i++) {
        //산타 죽었거나 스턴 상태이면 continue
        if (!santa_live[i]) continue;
        if (stun_santa[i] >= turn) continue;
        //i번째 산타 위치
        int tempsy = santa_location[i].first;
        int tempsx = santa_location[i].second;

        //산타 움직일 수 있는지와 4방향에 대해 최소 값 구하기
        int mindis = pow((tempsy - ry), 2) + pow((tempsx - rx), 2);
        int flag = -1;

        for (int k = 0; k < 4; k++) {
            int ny = tempsy + dy[k];
            int nx = tempsx + dx[k];
            //범위 넘어가거나 다른 산타가 있으면 continue
            if (ny > n || ny < 1 || nx > n || nx < 1 || map[ny][nx] > 0) continue;
            int dis = pow((ny - ry), 2) + pow((nx - rx), 2);
            //거리 최소 값 비교 
            if (mindis > dis) { //우선순위를 위해 등호는 빼주기
                mindis = dis;
                flag = k; //방향 넣어주기
            }
        }
        //움직일 수 있으면
        if (flag != -1) {
            //움직이기
            tempsy += dy[flag];
            tempsx += dx[flag];

            //움직였는데 루돌프와 충돌할 경우
            if (tempsy == ry && tempsx == rx) {

                stun_santa[i] = turn + 1;
                //반대방향으로 d만큼 밀려나기
                int tempcy = tempsy + (-dy[flag] * d);
                int tempcx = tempsx + (-dx[flag] * d);

                //d가1이면 어차피 그자리 그대로 이므로 점수만 더해준다.
                if (d == 1) {
                    final_score[i] += d;
                }

                else {
                    //충돌해서 밀렸는데 범위를 넘어갈 경우
                    if (tempcy > n || tempcy < 1 || tempcx > n || tempcx < 1) {
                        final_score[i] += d;
                        santa_live[i] = false;
                        map[santa_location[i].first][santa_location[i].second] = 0;
                        santa_location[i] = { 0,0 };
                        continue;
                    }
                    else {
                        //연쇄 충돌
                        if (map[tempcy][tempcx] > 0) {
                            map[santa_location[i].first][santa_location[i].second] = 0;
                            crash(tempcy, tempcx, -dy[flag], -dx[flag], i);

                        }
                        //일반 충돌
                        else {
                            map[tempcy][tempcx] = i; //새로운 좌표에 산타 번호 넣기
                            map[santa_location[i].first][santa_location[i].second] = 0; //그 전좌표 0
                            santa_location[i] = { tempcy,tempcx }; //산타 위치 업데이트
                        }
                    }
                    //충돌한 산타i에대해 d만큼 점수 더해주기
                    final_score[i] += d;
                }
            }
            //충돌 X
            else {
                map[santa_location[i].first][santa_location[i].second] = 0;
                map[tempsy][tempsx] = i;
                santa_location[i] = { tempsy,tempsx };
            }
        }
    }
}

int main() {
    cin >> n >> m >> p >> c >> d;
    cin >> ry >> rx;
    map[ry][rx] = -1;
    for (int i = 1; i <= p; i++) {
        int num, y, x;
        cin >> num >> y >> x;
        map[y][x] = num;
        santa_location[num] = { y,x };
        santa_live[num] = true;
    }
    for (int i = 1; i <= m; i++) {
        move_dear(ry, rx, i);

        move_santa(i);

        bool flag = false;
        //살아 남은 산타들 1점씩 추가
        //살아 남은 산타가 있는지 확인
        for (int i = 1; i <= p; i++) {
            if (santa_live[i]) {
                flag = true;
                final_score[i] += 1;
            }
        }
        //한명도 안살아있다면 게임 종료 
        if (!flag) break;
    }
    for (int i = 1; i <= p; i++) {
        cout << final_score[i] << " ";
    }
}