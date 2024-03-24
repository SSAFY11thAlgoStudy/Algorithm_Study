#include <iostream>
#include <algorithm>
using namespace std;

int h, w;
char map[26][26];
bool visited[26][26] = { false };
int a, b;
string dir = "v<^>";
int dy[4] = { 1,0,-1,0 };
int dx[4] = { 0,-1,0,1 };
int d;

void find() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            //현재 좌표 근처 #의 갯수 넣어줄 변수 
            int temp = 0;
            for (int k = 0; k < 4; k++) {
                int ny = i + dy[k];
                int nx = j + dx[k];
                //4방향으로 현재 #의 갯수 구해주기
                if (ny < h && ny >= 0 && nx < w && nx >= 0) {
                    if (map[i][j] == '#' && map[ny][nx] == '#') {
                        temp++;
                    }
                }
            }
            //1이면 출발 지점이 될 수 있음
            if (temp == 1) {
                a = i;
                b = j;
                //출발 지점을 기준으로 처음 로봇이 바라보는 방향 구해주기
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k];
                    int nx = j + dx[k];
                    //범위 안에 있고
                    if (ny < h && ny >= 0 && nx < w && nx >= 0) {
                        // 시작 점 근처 4방향중 같은 # 방향이 처음 방향
                        if (map[i][j] == '#' && map[ny][nx] == '#') d = k;
                    }
                }
                //찾았으면 return
                return;
            }
        }
    }
}

void command(int y, int x) {
    //이동한 칸은 #일 것이므로 바로 방문 체크
    visited[y][x] = true;
    //2칸전진해야하므로 한칸 더 더해주기
    y += dy[d];
    x += dx[d];
    //전진 했으므로 A출력
    cout << "A";
    //한칸 더 전진한 칸도 방문 체크
    visited[y][x] = true;

    //4방향에 대해서 방향 바꿔야하는지 체크
    for (int k = 0; k < 4; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];

        if (ny < h && ny >= 0 && nx < w && nx >= 0) {
            if (map[ny][nx] == '#' && !visited[ny][nx]) {
                //(d=1,< => d=0,v), L ,k = 0
                //(d=0,v => d=3,>), L , k = 3
                //(d=3,> => d=2,^), L , k = 2 
                if (d - k == 1 || d - k == -3) cout << "L";
                //(d=2,^ => d=3,>), R , k = 3
                //(d=3,> => d=0,v), R , k = 0
                //(d=0,v => d=1,<), R , k = 1
                else if (d - k == -1 || d - k == 3) cout << "R";
                //바뀐 방향은 k와 같음
                d = k;
                return command(ny, nx);
            }
        }
    }
}

int main() {
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++) {
            map[i][j] = s[j];
        }
    }
    find();
    cout << a + 1 << " " << b + 1 << '\n';
    cout << dir[d] << '\n';
    //출발 지점 방문 체크
    visited[a][b] = true;
    //출발 지점 방문 체크 했으므로 방향 다음 좌표부터 시작
    command(a + dy[d], b + dx[d]);
    return 0;
}