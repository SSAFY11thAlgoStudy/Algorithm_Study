#include<iostream>
#include<cstring>
using namespace std;

int N, L;
int map[100][100] = { 0 };



int solve() {
    int cnt = 0;

    // 가로 수색
    for (int x = 0; x < N; x++) {
        int flag = 1;

        //맴셋을 백준에서 런타임 오류로 인해 생성초기화로 전환
        int stairs[100] = { 0 };
        for (int y = 0; y < N - 1; y++) {
            //이미 글른건 빠르게 스킵
            if (flag == 0) break;

            // 내 위치와 다음이 같으면 패스
            if (map[y][x] == map[y + 1][x]) continue;

            // 다음이 내 위치보다 작을 경우
            else if (map[y][x] > map[y + 1][x]) {
                for (int l = 1; l <= L; l++) {
                    //맵밖을 벗어나서 확인하는 경우
                    //다음 위치들(L개)이 내위치보다 +1 크기가 아닌 경우
                    //계단이 설치되지 된 경우
                    if (y + l >= N || !(map[y][x] - 1 == map[y + l][x]) || stairs[y + l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[y + l] = 1;
                }
            }

            // 다음이 내 위치보다 클 경우
            else if (map[y][x] < map[y + 1][x]) {
                for (int l = 0; l < L; l++) {
                    //맵밖을 벗어나서 확인하는 경우
                    //다음 위치들(L개)이 내위치보다 -1 크기가 아닌 경우
                    //계단이 설치되지 된 경우
                    if (y - l < 0 || !(map[y + 1][x] - 1 == map[y - l][x]) || stairs[y - l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[y - l] = 1;
                }
            }
        }
        if (flag == 1) cnt++;
    }

    // 세로 수색
    for (int y = 0; y < N; y++) {
        int flag = 1;
        int stairs[100] = { 0 };
        for (int x = 0; x < N - 1; x++) {

            //이미 글른건 빠르게 스킵
            if (flag == 0) break;

            // 내 위치와 다음이 같으면 패스
            if (map[y][x] == map[y][x + 1]) continue;

            // 다음이 내 위치보다 작을 경우
            else if (map[y][x] > map[y][x + 1]) {
                for (int l = 1; l <= L; l++) {
                    //맵밖을 벗어나서 확인하는 경우
                    //다음 위치들(L개)이 내위치보다 +1 크기가 아닌 경우
                    //계단이 설치되지 된 경우
                    if (x + l >= N || !(map[y][x] - 1 == map[y][x + l]) || stairs[x + l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[x + l] = 1;
                }
            }

            // 다음이 내 위치보다 클 경우
            else if (map[y][x] < map[y][x + 1]) {
                for (int l = 0; l < L; l++) {
                    //맵밖을 벗어나서 확인하는 경우
                    //다음 위치들(L개)이 내위치보다 -1 크기가 아닌 경우
                    //계단이 설치되지 된 경우
                    if (x - l < 0 || !(map[y][x + 1] - 1 == map[y][x - l]) || stairs[x - l] == 1) {
                        flag = 0;
                        break;
                    }
                    stairs[x - l] = 1;
                }
            }
        }
        if (flag == 1) cnt++;
    }

    return cnt;
}

void input() {
    cin >> N >> L;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> map[i][j];
        }
    }
}

int main() {
    input();
    cout << solve();
    return 0;
}