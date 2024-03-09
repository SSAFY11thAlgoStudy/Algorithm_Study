#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    //���� �Է� ���� ����
    vector<vector<int>> scores(3, vector<int>(n));
    //���� ���� ���� ������ ����
    vector<vector<int>> ranks(3, vector<int>(n));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> scores[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        //���� �� �ε��� �������� ������ ���� 
        vector<pair<int, int>> sorted_scores;
        for (int j = 0; j < n; j++) {
            sorted_scores.push_back({ scores[i][j], j });
        }
        //�������� ����
        sort(sorted_scores.begin(), sorted_scores.end(), greater<pair<int, int>>());
        int rank = 1; //������ ������ ����
        int cnt = 0; // ������ ���� �� ���� ������ ����
        for (int j = 0; j < n; j++) {
            //������ �ٸ��ٸ�
            if (j > 0 && sorted_scores[j - 1].first != sorted_scores[j].first) {
                rank += cnt; //������ cnt�� rank�� �����ְ�
                cnt = 1; //cnt�� 1�� �ʱ�ȭ
            }
            else {
                cnt++; //������ ���ٸ� 1�� ����
            }
            //�� ���� �ε����� �°� ���� �־��ֱ�
            ranks[i][sorted_scores[j].second] = rank;
        }
    }
    //���� ���
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cout << ranks[i][j] << " ";
        }
        cout << '\n';
    }
    //�ջ�� ���� �� �ε��� ������ ����
    vector<pair<int, int>> sorted_ranks;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            //0�϶� �ε��� �� �ޱ�
            if (i == 0) {
                sorted_ranks.push_back({ scores[i][j], j });
            }
            //������ ���� �ε����� �°� �����ֱ�
            else {
                sorted_ranks[j].first += scores[i][j];
            }
        }
    }
    //�������� ����
    sort(sorted_ranks.begin(), sorted_ranks.end(), greater<pair<int, int>>());

    //���� ������ ������ ������ ����
    vector<vector<int>> final_ranks(1, vector<int>(n));

    int rank = 1; //������ ������ ����
    int cnt = 0; // ������ ���� �� ���� ������ ����
    for (int i = 0; i < n; i++) {
        //������ �ٸ��ٸ�
        if (i > 0 && sorted_ranks[i - 1].first != sorted_ranks[i].first) {
            rank += cnt;
            cnt = 1;
        }
        else {
            cnt++; //������ ���ٸ� 1�� ����
        }
        //�� ���� �ε����� �°� ���� �־��ֱ�
        final_ranks[0][sorted_ranks[i].second] = rank;
    }
    //���� ������ ���� ���
    for (int i = 0; i < n; i++) {
        cout << final_ranks[0][i] << " ";
    }
    return 0;
}
