#define _CRT_SECURE_NO_WARNING
#include <iostream>

using namespace std;

int N, cnt = 0;
//체스판에 위치를 저장
// position[행] = 열의 위치
int position[13];

// 
int isvalid(int node, int i) {
    for (int j = 0; j < node; j++)
    {
        // 내 아래탐색
        if (position[j] == i)return 0;
        // 우하 탐색
        if (position[j] + (node - j) == i) return 0;
        // 좌하 탐색
        if (position[j] - (node - j) == i) return 0;
    }
    return 1;
}

//node는 행을 뜻함
void dfs(int node) {

    // 기저조건 node(행)이 N까지 왔을 때 
    if (node == N) {
        cnt++;
        return;
    }

    // 열도 N까지 있기 때문에 N개의 시작 위치 탐색
    for (int i = 0; i < N; i++)
    {
        // 유효위치인지 탐색
        if (isvalid(node, i)) {
            //맞다면, node행에 i열의 위치 값 삽입
            position[node] = i;
            // 재귀
            dfs(node + 1);
        }
    }
}


int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;

        dfs(0);
        cout << "#" << tc << " " << cnt;
    }

    return 0;
}
