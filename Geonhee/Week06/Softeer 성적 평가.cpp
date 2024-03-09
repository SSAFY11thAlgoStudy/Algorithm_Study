#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    //점수 입력 받을 벡터
    vector<vector<int>> scores(3, vector<int>(n));
    //성적 마다 순위 저장할 벡터
    vector<vector<int>> ranks(3, vector<int>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> scores[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        //점수 및 인덱스 내림차순 정렬할 벡터 
        vector<pair<int, int>> sorted_scores;
        for (int j = 0; j < n; j++) {
            sorted_scores.push_back({ scores[i][j], j });
        }
        //내림차순 정렬
        sort(sorted_scores.begin(), sorted_scores.end(), greater<pair<int, int>>());
        int rank = 1; //순위를 누적할 변수
        int cnt = 0; // 점수가 같을 때 순위 누적할 변수
        for (int j = 0; j < n; j++) {
            //점수가 다르다면
            if (j > 0 && sorted_scores[j - 1].first != sorted_scores[j].first) {
                rank += cnt; //누적된 cnt값 rank에 더해주고
                cnt = 1; //cnt는 1로 초기화
            }
            else {
                cnt++; //점수가 같다면 1씩 누적
            }
            //각 점수 인덱스에 맞게 순위 넣어주기
            ranks[i][sorted_scores[j].second] = rank;
        }
    }
    //순위 출력
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cout << ranks[i][j] << " ";
        }
        cout << '\n';
    }
    //합산된 점수 및 인덱스 누적할 벡터
    vector<pair<int, int>> sorted_ranks;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            //0일때 인덱스 다 받기
            if (i == 0) {
                sorted_ranks.push_back({ scores[i][j], j });
            }
            //나머지 점수 인덱스에 맞게 더해주기
            else {
                sorted_ranks[j].first += scores[i][j];
            }
        }
    }
    //내림차순 정렬
    sort(sorted_ranks.begin(), sorted_ranks.end(), greater<pair<int, int>>());

    //최종 점수합 순위를 저장할 벡터
    vector<vector<int>> final_ranks(1, vector<int>(n));

    int rank = 1; //순위를 누적할 변수
    int cnt = 0; // 점수가 같을 때 순위 누적할 변수
    for (int i = 0; i < n; i++) {
        //점수가 다르다면
        if (i > 0 && sorted_ranks[i - 1].first != sorted_ranks[i].first) {
            rank += cnt;
            cnt = 1;
        }
        else {
            cnt++; //점수가 같다면 1씩 누적
        }
        //각 점수 인덱스에 맞게 순위 넣어주기
        final_ranks[0][sorted_ranks[i].second] = rank;
    }
    //최종 점수합 순위 출력
    for (int i = 0; i < n; i++) {
        cout << final_ranks[0][i] << " ";
    }
    return 0;
}
