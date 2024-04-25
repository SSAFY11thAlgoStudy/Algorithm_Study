#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M; // 정점의 개수 N과 간선의 개수 M을 저장할 변수 선언
int degree[32001] = { 0, }; // 각 정점의 진입 차수를 저장할 벡터
vector<int> v[32001]; // 인접 리스트 형태의 그래프 표현
vector<int> result; //결과

//입력
void input() {
    cin >> N >> M; // 정점의 개수 N과 간선의 개수 M을 입력 받음
    for (int i = 0; i < M; i++) {
        int front_num, back_num;
        cin >> front_num >> back_num;
        v[front_num].push_back(back_num); // 그래프 정보를 저장
        degree[back_num]++; // 도착 정점의 진입 차수 증가
    }
}


void solve() {
    //queue를 이용해 더이상 노드가 없는 값을 삽입함
    queue<int> q;
    for (int i = 1; i <= N; i++)
    {
        // 차수가 0인것은 앞쪽에 들어와도 상관없는 값임으로 q에 삽입
        if (degree[i] == 0) {
            q.push(i);
        }
    }

    //q가 전부 빌때까지 반복
    while (!q.empty()) {
        int num = q.front();
        q.pop();
        //큐에서 나온 값은 바로 결과 배열에 삽입
        result.push_back(num);

        //큐에 나온 값이 부모가 되는 노드를 확인해서 차수를 감소시킨다.
        for (int i : v[num])
        {
            degree[i]--;
            // 감소 시킨 차수가 0이되면 더이상 그 수앞에 올수는 이미 queue에 들어온것임으로 queue에 넣어줌
            if (degree[i] == 0) {
                q.push(i);
            }
        }
    }
}

int main() {
    //입력
    input();

    solve();

    // 결과 출력
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    return 0;
}