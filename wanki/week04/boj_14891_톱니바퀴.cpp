#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

vector<char>wheel[5];

//입력
void input() {
    char input_data;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> input_data;
            wheel[i].push_back(input_data);
        }
    }
}

void Turn(int num, int dir) {
    // 시계방향
    if (dir == 1) {
        char swap = wheel[num][7];
        wheel[num].insert(wheel[num].begin(), swap);
        wheel[num].pop_back();
    }
    // 반시계 방향
    else if (dir == -1) {
        char swap = wheel[num][0];
        wheel[num].push_back(swap);
        wheel[num].erase(wheel[num].begin());
    }
}

// 오른쪽 검사
void right_search(int num, int dir) {
    //오른쪽 바깥으로 벗어나지 않으며,
    //돌려야할 바퀴 2번과 그 오른쪽 바퀴의 6번이 다르면 
    //그 오른쪽 바퀴의 오른쪽도 확인하여 회전시킨다.(재귀)
    //만약 같다면 그 바퀴포함 오른쪽의 바퀴는 절대 회전하지 않는다.
    if (num < 4 && wheel[num][2] != wheel[num + 1][6]) {
        right_search(num + 1, -dir);
    }
    //최소 본인은 회전한다.
    Turn(num, dir);
}

// 왼쪽 검사
void left_search(int num, int dir) {
    //왼쪽 바깥으로 벗어나지 않으며,
    //돌려야할 바퀴 6번과 그 왼쪽 바퀴의 2번이 다르면 
    //그 왼쪽 바퀴의 왼쪽도 확인하여 회전시킨다. (재귀)
    //만약 같다면 그 바퀴포함 왼쪽의 바퀴는 절대 회전하지 않는다.
    if (num > 1 && wheel[num][6] != wheel[num - 1][2]) {
        left_search(num - 1, -dir);
    }
    //최소 본인은 회전한다.
    Turn(num, dir);
}

int main() {
    input();
    int K;
    cin >> K;
    for (int i = 0; i < K; i++)
    {
        int num, dir;
        cin >> num >> dir;
        right_search(num, dir);
        // 오른쪽 검사를 완료하면 입력받은 바퀴도 돌아가기에 그 전으로 돌려줌
        Turn(num, -dir);
        left_search(num, dir);
    }

    // 점수 계산
    // 점수는 2^wheel_num[0,1,2,3]의 크기를 가짐
    int result = 0;
    for (int i = 1; i <= 4; i++) {
        if (wheel[i][0] == '1') {
            result += pow(2, i - 1);
        }
    }
    cout << result;

    return 0;
}
