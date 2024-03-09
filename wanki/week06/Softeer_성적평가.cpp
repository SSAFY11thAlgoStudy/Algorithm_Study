#include<iostream>
#include <algorithm>
#include<vector>

using namespace std;

int N;
int score[4][100001];
vector<pair<int, int>> ranking[4];

void input() {
    cin >> N;
    for (int j = 0; j < 3; j++) {
        for (int i = 1; i <= N; i++) {
            int a;
            cin >> a;
            ranking[j].push_back(make_pair(a, i));
            score[3][i] += a;
        }
        sort(ranking[j].begin(), ranking[j].end(), greater<pair<int, int>>());
    }

    for (int i = 1; i <= N; i++) {
        ranking[3].push_back(make_pair(score[3][i], i));
    }
    sort(ranking[3].begin(), ranking[3].end(), greater<pair<int, int>>());
}

int main(int argc, char** argv)
{
    input();

    for (int i = 0; i < 4; i++)
    {
        int cnt = 0;
        int beforescore = 0;
        int beforerank = 0;
        for (auto m : ranking[i]) {
            cnt++;
            if (beforescore == m.first) {
                score[i][m.second] = beforerank;
            }
            else {
                score[i][m.second] = cnt;
                beforerank = cnt;
                beforescore = m.first;
            }
        }
    }


    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j <= N; j++) {
            cout << score[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
