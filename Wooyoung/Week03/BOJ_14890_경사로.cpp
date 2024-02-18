#include<iostream>

#include<vector>

#include<algorithm>
using namespace std;

// 길은 한 행 or 한 열
// 단, 모든 칸의 높이가 같아야함
// 이때, 경사로를 놓아서 높이를 키울 수 있다. (개당 1 증가, 길이 L)
// 경사로를 놓으려면 L개의 칸이 연속적이고, 높이가 같아야함
// 또한 낮은칸과 높은칸의 차이는 1이어야한다.


int n, l;
int ans;
int map[101][101];
int max_row[101];
int max_col[101];
bool visited[101][101];
vector<int>v_row[101];
vector<int>v_col[101];

void cnt_can() {


    // 다음 높이가 +1보다 크다면 ? 진행 불가
    // 다음 높이가 +1이라면 ? -> 현재 지나온 길이 L만큼 깔을 수 있는가?
    // 다음 높이가 -1이라면 ? -> 앞으로 나아갈 길이 L만큼 깔을 수 있는가? 
    // 경사로를 깔았다면 for문에서 continue로 판단 x
    // 즉, 현재 지점과 다음 지점의 높이가 같거나 
    // 다음 지점에 경사로가 깔려있으면 for문 continue
    // 이후 for문이 끝날 때 까지 false가 안바뀌면 현재 길은 통과가 가능


    // 가로줄
    for (int i = 0; i < n; i++) {
        bool row_checkdown[101] = { false, };
        bool row_checkup[101] = { false, };
        bool can = true;
        for (int j = 0; j < n - 1; j++) {
            // 높이 차이가 1보다 크다? -> break후 다음 줄로
            if (abs(v_row[i][j] - v_row[i][j + 1]) > 1) {
                can = false;
                break;
            }
        }
        // 현재줄을 더이상 확인 x -> 다음 줄로 이동
        if (!can)continue;

        // 높이 차이가 1보다 큰 경우가 없다면 경사로 만들기 
        // 이 때 오르막길 경사로를 설치할 때 
        // 기존에 내리막길 경사로를 설치한 경우가 있으면
        // 설치를 못하니 꼭 확인해주어야함 
        for (int j = 0; j < n - 1; j++) {


            // 다음 높이가 -1 인 경우 
            if (v_row[i][j] - v_row[i][j + 1] == 1) {
                // 다음 지점부터 끝까지 같은 높이가 얼마나 있는지 확인
                int cnt = 1;
                for (int k = j + 1; k < n - 1; k++) {
                    if (v_row[i][k] == v_row[i][k + 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // 현재 cnt는 j+1번째 지점부터 앞으로 똑같은 높이인 지점의 개수
                // cnt가 L개 이상이면 j+1번째부터 앞으로 L개까지 경사로를 깔음 => bool배열에 기록
                // 현재 지점도 경사로로 포함하기 위함임
                if (cnt >= l) {

                    for (int k = 1; k <= l; k++) {
                        row_checkdown[j + k] = true;
                    }
                }
            }

            // 다음 높이가 +1 인 경우
            else if (v_row[i][j] - v_row[i][j + 1] == -1 && !row_checkdown[j]) {
                // 현재 지점부터 0번까지 같은 높이가 얼마나 있는지 확인
                // 이때 경사로가 이미 설치되어 있으면 cnt로 포함 x 
                int cnt = 1;
                for (int k = j; k > 0; k--) {
                    if (v_row[i][k] == v_row[i][k - 1] && !row_checkdown[k - 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // 현재 cnt는 j번째 지점부터 뒤로 똑같은 높이인 지점의 개수
                // cnt가 L개 이상이면 j번째부터 뒤로 L개까지 경사로를 깔음 => bool배열에 기록
                if (cnt >= l) {

                    for (int k = 0; k < l; k++) {
                        row_checkup[j - k] = true;
                    }
                }
            }

        }

        // 현재 지점과 다음 지점과 높이가 같거나 
        // 다음 지점이 +1일 때 row_checkup의 현재 지점에 경사로가 있거나
        // 다음 지점이 -1일 때 row_checkdown의 다음 지점에 경사로가 있거나
        // 없으면 false 반환
        bool can_cnt = true;

        bool check[101] = { false, };
        for (int j = 0; j < n - 1; j++) {
            if ((v_row[i][j] == v_row[i][j + 1]) ||
                (v_row[i][j] - v_row[i][j + 1] == -1 && row_checkup[j]) ||
                (v_row[i][j] - v_row[i][j + 1] == 1 && row_checkdown[j + 1])) {
                continue;
            }
            can_cnt = false;
        }
        if (can_cnt) {
            ans++;
        }
    }

    // 세로줄
    for (int i = 0; i < n; i++) {
        bool col_checkdown[101] = { false, };
        bool col_checkup[101] = { false, };
        bool can = true;
        for (int j = 0; j < n - 1; j++) {
            // 높이 차이가 1보다 크다? -> break후 다음 줄로
            if (abs(v_col[i][j] - v_col[i][j + 1]) > 1) {
                can = false;
                break;
            }
        }
        // 현재줄을 더이상 확인 x -> 다음 줄로 이동
        if (!can)continue;

        // 높이 차이가 1보다 큰 경우가 없다면 경사로 만들기 
        for (int j = 0; j < n - 1; j++) {

            // 다음 높이가 -1 인 경우 
            if (v_col[i][j] - v_col[i][j + 1] == 1) {
                // 다음 지점부터 끝까지 같은 높이가 얼마나 있는지 확인
                int cnt = 1;
                for (int k = j + 1; k < n - 1; k++) {
                    if (v_col[i][k] == v_col[i][k + 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // 현재 cnt는 j+1번째 지점부터 앞으로 똑같은 높이인 지점의 개수
                // cnt가 L개 이상이면 j+1번째부터 앞으로 L개까지 경사로를 깔음 => bool배열에 기록
                if (cnt >= l) {

                    for (int k = 1; k <= l; k++) {
                        col_checkdown[j + k] = true;
                    }
                }
            }

            // 다음 높이가 +1 인 경우
            else if (v_col[i][j] - v_col[i][j + 1] == -1 && !col_checkdown[j]) {
                // 현재 지점부터 0번까지 같은 높이가 얼마나 있는지 확인
                int cnt = 1;
                for (int k = j; k > 0; k--) {
                    if (v_col[i][k] == v_col[i][k - 1] && !col_checkdown[k - 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // 현재 cnt는 j번째 지점부터 뒤로 똑같은 높이인 지점의 개수
                // cnt가 L개 이상이면 j번째부터 뒤로 L+1개까지 경사로를 깔음 => bool배열에 기록
                if (cnt >= l) {

                    for (int k = 0; k < l; k++) {
                        col_checkup[j - k] = true;
                    }
                }
            }

        }
        // 현재 지점과 다음 지점과 높이가 같거나 
        // 다음 지점이 +1일 때 현재 지점에 경사로가 있거나
        // 다음 지점이 -1일 때 다음 지점에 경사로가 있거나
        // 없으면 false 반환
        bool can_cnt = true;
        for (int j = 0; j < n - 1; j++) {
            if ((v_col[i][j] == v_col[i][j + 1]) ||
                (v_col[i][j] - v_col[i][j + 1] == -1 && col_checkup[j]) ||
                (v_col[i][j] - v_col[i][j + 1] == 1 && col_checkdown[j + 1])) {
                continue;
            }
            can_cnt = false;
        }
        if (can_cnt) {
            ans++;
        }
    }

}

int main() {

    int high;
    cin >> n >> l;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> high;
            v_row[i].push_back(high);
            v_col[j].push_back(high);
        }
    }
    cnt_can();
    cout << ans;



    return 0;
}