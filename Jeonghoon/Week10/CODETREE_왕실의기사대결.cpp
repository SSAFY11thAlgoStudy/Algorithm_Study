#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

int L, N, Q;
//함정, 벽 맵
int map[42][42];
//기사 위치 맵
int kmap[42][42];
//움직일지 말지 확인하는 플래그
int flag;

//기사 정보
struct Knight {
    int y, x;
    int h, w;
    int k;
};

//명령정보
struct Command {
    int num, dir;
};

vector<Knight> k;
vector<Command> c;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

//죽었는지 살았는지 확인
bool isdie[31];
// 공격 받았는지 확인
bool isattacked[31];
int damage[31];

void input() {

    cin >> L >> N >> Q;

    for (int i = 0; i <= L + 1; i++) {
        for (int j = 0; j <= L + 1; j++) {

            if (i == 0 || j == 0 || i == L + 1 || j == L + 1) {
                map[i][j] = 2;
            }
            else {
                cin >> map[i][j];
            }
        }
    }

    k.push_back({});
    for (int i = 1; i <= N; i++) {
        int t1, t2, t3, t4, t5;
        cin >> t1 >> t2 >> t3 >> t4 >> t5;
        k.push_back({ t1,t2,t3,t4,t5 });

        for (int r = t1; r < t1 + t3; r++) {
            for (int c = t2; c < t2 + t4; c++) {
                kmap[r][c] = i;
            }
        }
    }

    c.push_back({});
    for (int i = 1; i <= Q; i++) {
        int t1, t2;
        cin >> t1 >> t2;
        c.push_back({ t1,t2 });
    }
}

void movek(int sy, int sx, int dir) {

    //이동할 좌표
    int ny = sy + dy[dir];
    int nx = sx + dx[dir];

    //명령받은 기사 정보
    int height = k[kmap[sy][sx]].h;
    int width = k[kmap[sy][sx]].w;
    int num = kmap[sy][sx];

    //기사 영역만큼 이동
    for (int i = ny; i < ny + k[kmap[sy][sx]].h; i++) {
        for (int j = nx; j < nx + k[kmap[sy][sx]].w; j++) {
            if (kmap[i][j] != 0 && kmap[i][j] != kmap[sy][sx]) {
                //연쇄이동
                movek(k[kmap[i][j]].y, k[kmap[i][j]].x, dir);
            }
        }
    }

    //기존 자리는 0으로
    for (int r = sy; r < sy + height; r++) {
        for (int c = sx; c < sx + width; c++) {
            kmap[r][c] = 0;
        }
    }

    //새로 이동한 자리에 숫자 넣기
    for (int r = ny; r < ny + height; r++) {
        for (int c = nx; c < nx + width; c++) {
            kmap[r][c] = num;
        }
    }

    //좌표 갱신
    k[num].y = ny;
    k[num].x = nx;
}

void movepos(int sy, int sx, int dir) {

    //이동할 좌표
    int ny = sy + dy[dir];
    int nx = sx + dx[dir];

    //영역만큼 확인
    for (int i = ny; i < ny + k[kmap[sy][sx]].h; i++) {
        for (int j = nx; j < nx + k[kmap[sy][sx]].w; j++) {
            //벽이면 플래그 1
            if (map[i][j] == 2) {
                flag = 1;
                return;
            }

            //다른 기사가 있다면 연쇄이동 여부 확인
            if (kmap[i][j] != 0 && kmap[i][j] != kmap[sy][sx]) {
                movepos(k[kmap[i][j]].y, k[kmap[i][j]].x, dir);
                //공격 받은 기사 표시
                isattacked[kmap[i][j]] = true;
            }
        }
    }

    if (flag == 1) return;
}

void checktrap() {

    for (int i = 1; i <= N; i++) {
        int trap = 0;

        //공격 받은 사람들만 점수 체크
        if (isattacked[i] == true) {
            for (int r = k[i].y; r < k[i].y + k[i].h; r++) {
                for (int c = k[i].x; c < k[i].x + k[i].w; c++) {
                    if (map[r][c] == 1) {
                        trap++;
                    }
                }
            }

            //체력 - 함정 수
            k[i].k -= trap;

            // 데미지가 체력보다 크면 죽음
            if (k[i].k <= 0) {
                isdie[i] = true;
                //그 기사 위치 지우기
                for (int r = k[i].y; r < k[i].y + k[i].h; r++) {
                    for (int c = k[i].x; c < k[i].x + k[i].w; c++) {
                        kmap[r][c] = 0;
                    }
                }

            }
            else {
                damage[i] += trap;
            }
        }
    }
}

void solve() {

    for (int i = 1; i <= Q; i++) {

        //초기화
        flag = 0;
        for (int i = 0; i <= N; i++) {
            isattacked[i] = false;
        }

        //죽은사람 명령은 무시
        if (isdie[c[i].num] == true) continue;

        //움직여야하는 기사 번호
        int k_ind = c[i].num;

        //명령대로 갈 수 있는지 체크
        movepos(k[k_ind].y, k[k_ind].x, c[i].dir);
        isattacked[k_ind] = false;

        if (flag == 1)continue;

        //명령대로 갈 수 있으면 움직이기
        movek(k[k_ind].y, k[k_ind].x, c[i].dir);

        //움직인 뒤에 체력을 위해 주위 체크
        checktrap();

    }
}

int main() {

    //freopen("sample.txt", "r", stdin);

    input();
    solve();

    int result = 0;
    for (int i = 1; i <= N; i++) {
        if (isdie[i] == false) {
            result += damage[i];
        }
    }
    cout << result;

    return 0;
}