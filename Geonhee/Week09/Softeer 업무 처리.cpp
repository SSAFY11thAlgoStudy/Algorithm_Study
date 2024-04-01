#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

int h, k, r;
queue<int> all[2049];
queue<int> left_e[2049], right_e[2049];
int res = 0;

int main() {
    cin >> h >> k >> r;
    //전체 직원 수 
    int person = pow(2, h + 1);
    //말단 직원 수
    int junior = pow(2, h);
    //말단 직원들만 k개의 순서가 정해진 업무를 받음
    for (int i = 0; i < junior; i++) {
        for (int j = 0; j < k; j++) {
            int a;
            cin >> a;
            //말단 직원 index에 맞게 push
            all[junior + i].push(a);
        }
    }
    //업무 진행되는 날 만큼
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j < person; j++) {
            //말단 직원들의 업무가 있으면
            if (j >= junior) {
                //줄 업무가 없으면 continue
                if (!all[j].size()) continue;
                //현재 노드가 오른쪽 부하 직원이면
                if (j % 2 == 1)
                    //index / 2가 부모노드의 index
                    right_e[j / 2].push(all[j].front());
                //현재 노드가 왼쪽 부하 직원이면
                else if (j % 2 == 0)
                    left_e[j / 2].push(all[j].front());
                //해당 업무 처리 했으므로 pop
                all[j].pop();
            }
            //홀수 날 일떄
            else if (i % 2 == 1) {
                //왼쪽에 업무가 남았을 때
                if (left_e[j].size()) {
                    //현재 노드가 부서장 이라면 업무량 더해주기
                    if (j == 1) res += left_e[j].front();
                    //현재 노드가 오른쪽 부하 직원이면
                    else if (j % 2 == 1)
                        right_e[j / 2].push(left_e[j].front());
                    //현재 노드가 왼쪽 부하 직원이면
                    else if (j % 2 == 0)
                        left_e[j / 2].push(left_e[j].front());
                    //해당 업무 처리 했으므로 pop
                    left_e[j].pop();
                }
            }
            //짝수 날 일때
            else if (i % 2 == 0) {
                //오른쪽에 업무가 남았을 때
                if (right_e[j].size()) {
                    //부서장 이라면 업무량 더해주기
                    if (j == 1) res += right_e[j].front();
                    //현재 노드가 오른쪽 부하 직원이면
                    else if (j % 2 == 1)
                        right_e[j / 2].push(right_e[j].front());
                    //현재 노드가 왼쪽 부하 직원이면
                    else if (j % 2 == 0)
                        left_e[j / 2].push(right_e[j].front());
                    //해당 업무 처리 했으므로 pop
                    right_e[j].pop();
                }
            }
        }
    }
    cout << res << '\n';
    return 0;
}