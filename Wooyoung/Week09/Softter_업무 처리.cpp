#include<iostream>
#include<deque>
#include<cmath>
#include<algorithm>
// 트리 높이 h
// 말단 직원 당 대기 업무 k
// 업무 진행 시간 r
// h일 때 말단 직원 수는 ? 2의 h제곱
// 사장 번호 0, 말단 직원의 왼쪽 끝부터 오른쪽 방향으로 번호는 ? 2의 h제곱 -1 ~ 2의 (h+1)제곱 -2
// h=10일 때, 전체 직원의 수는 1=3, 2=7, 3=15, -> 2^(h+1) - 1 = 2048-1, 2100으로 사이즈 지정

using namespace std;
int h, k, r, ans, day;
int end_left, end_right;
struct Info {
    int num;
    bool odd;
};

deque<Info>workers[2100];

void input() {
    cin >> h >> k >> r;
    end_left = pow(2, h) - 1;
    end_right = pow(2, h + 1) - 2;
    for (int i = end_left; i <= end_right; i++) {
        int num;
        for (int j = 0; j < k; j++) {
            cin >> num;
            if (i % 2 == 0) {
                workers[i].push_back({ num,false });
            }
            else {
                workers[i].push_back({ num,true });
            }
        }
    }
}

// 맨 위 루트부터 왼쪽, 오른쪽 재귀로 탐색
// 원래 업무를 올린 후 다음 날 상사가 처리하는 방식을 거꾸로 진행
// 상사가 처리해야할 업무가 있으면 처리 후 밑에 내려가서 부하 직원에게 업무를 올리도록 설정

void func(int root) {
    if (root > end_right)return;
    if (!workers[root].empty()) {
        // 부서장
        if (root == 0) {
            int start = 0;
            bool check = false;
            if (day % 2 == 0) {
                for (int i = 0; i < workers[0].size(); i++) {
                    if (!workers[0][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < workers[0].size(); i++) {
                    if (workers[0][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            // 처리할 홀수,짝수번 째 업무가 있을 때만 처리
            if (check) {

                Info finish = workers[0][start];
                ans += finish.num;
                workers[0].erase(workers[0].begin() + start);
            }
        }
        // 상사
        else if (root < end_left) {
            int start = 0;
            bool check = false;
            if (day % 2 == 0) {
                for (int i = 0; i < workers[root].size(); i++) {
                    if (!workers[root][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < workers[root].size(); i++) {
                    if (workers[root][i].odd) {
                        start = i;
                        check = true;
                        break;
                    }
                }
            }
            if (check) {

                Info work = workers[root][start];
                // 상사 기준 오른쪽 부하인 경우
                if (root % 2 == 0) {
                    work.odd = false;
                    workers[(root - 1) / 2].push_back(work);
                }
                else {
                    work.odd = true;
                    workers[(root) / 2].push_back(work);
                }
                workers[root].erase(workers[root].begin() + start);
            }
        }
        // 말단 직원
        else {
            Info work = workers[root][0];
            if (root % 2 == 0) {
                workers[(root - 1) / 2].push_back(work);
            }
            else {
                workers[root / 2].push_back(work);
            }
            workers[root].pop_front();
        }
    }
    func(root + 1);
    return;
}

bool Isempty() {
    for (int i = 0; i <= end_right; i++) {
        if (!workers[i].empty())return false;
    }

    return true;
}

int main(int argc, char** argv)
{
    input();
    for (int i = 0; i < r; i++) {
        day++;
        func(0);
    }
    cout << ans;
    return 0;
}