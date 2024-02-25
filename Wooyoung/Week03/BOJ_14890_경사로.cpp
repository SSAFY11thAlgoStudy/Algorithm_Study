#include<iostream>

#include<vector>

#include<algorithm>
using namespace std;

// ���� �� �� or �� ��
// ��, ��� ĭ�� ���̰� ���ƾ���
// �̶�, ���θ� ���Ƽ� ���̸� Ű�� �� �ִ�. (���� 1 ����, ���� L)
// ���θ� �������� L���� ĭ�� �������̰�, ���̰� ���ƾ���
// ���� ����ĭ�� ����ĭ�� ���̴� 1�̾���Ѵ�.


int n, l;
int ans;
int map[101][101];
int max_row[101];
int max_col[101];
bool visited[101][101];
vector<int>v_row[101];
vector<int>v_col[101];

void cnt_can() {


    // ���� ���̰� +1���� ũ�ٸ� ? ���� �Ұ�
    // ���� ���̰� +1�̶�� ? -> ���� ������ ���� L��ŭ ���� �� �ִ°�?
    // ���� ���̰� -1�̶�� ? -> ������ ���ư� ���� L��ŭ ���� �� �ִ°�? 
    // ���θ� ��Ҵٸ� for������ continue�� �Ǵ� x
    // ��, ���� ������ ���� ������ ���̰� ���ų� 
    // ���� ������ ���ΰ� ��������� for�� continue
    // ���� for���� ���� �� ���� false�� �ȹٲ�� ���� ���� ����� ����


    // ������
    for (int i = 0; i < n; i++) {
        bool row_checkdown[101] = { false, };
        bool row_checkup[101] = { false, };
        bool can = true;
        for (int j = 0; j < n - 1; j++) {
            // ���� ���̰� 1���� ũ��? -> break�� ���� �ٷ�
            if (abs(v_row[i][j] - v_row[i][j + 1]) > 1) {
                can = false;
                break;
            }
        }
        // �������� ���̻� Ȯ�� x -> ���� �ٷ� �̵�
        if (!can)continue;

        // ���� ���̰� 1���� ū ��찡 ���ٸ� ���� ����� 
        // �� �� �������� ���θ� ��ġ�� �� 
        // ������ �������� ���θ� ��ġ�� ��찡 ������
        // ��ġ�� ���ϴ� �� Ȯ�����־���� 
        for (int j = 0; j < n - 1; j++) {


            // ���� ���̰� -1 �� ��� 
            if (v_row[i][j] - v_row[i][j + 1] == 1) {
                // ���� �������� ������ ���� ���̰� �󸶳� �ִ��� Ȯ��
                int cnt = 1;
                for (int k = j + 1; k < n - 1; k++) {
                    if (v_row[i][k] == v_row[i][k + 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // ���� cnt�� j+1��° �������� ������ �Ȱ��� ������ ������ ����
                // cnt�� L�� �̻��̸� j+1��°���� ������ L������ ���θ� ���� => bool�迭�� ���
                // ���� ������ ���η� �����ϱ� ������
                if (cnt >= l) {

                    for (int k = 1; k <= l; k++) {
                        row_checkdown[j + k] = true;
                    }
                }
            }

            // ���� ���̰� +1 �� ���
            else if (v_row[i][j] - v_row[i][j + 1] == -1 && !row_checkdown[j]) {
                // ���� �������� 0������ ���� ���̰� �󸶳� �ִ��� Ȯ��
                // �̶� ���ΰ� �̹� ��ġ�Ǿ� ������ cnt�� ���� x 
                int cnt = 1;
                for (int k = j; k > 0; k--) {
                    if (v_row[i][k] == v_row[i][k - 1] && !row_checkdown[k - 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // ���� cnt�� j��° �������� �ڷ� �Ȱ��� ������ ������ ����
                // cnt�� L�� �̻��̸� j��°���� �ڷ� L������ ���θ� ���� => bool�迭�� ���
                if (cnt >= l) {

                    for (int k = 0; k < l; k++) {
                        row_checkup[j - k] = true;
                    }
                }
            }

        }

        // ���� ������ ���� ������ ���̰� ���ų� 
        // ���� ������ +1�� �� row_checkup�� ���� ������ ���ΰ� �ְų�
        // ���� ������ -1�� �� row_checkdown�� ���� ������ ���ΰ� �ְų�
        // ������ false ��ȯ
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

    // ������
    for (int i = 0; i < n; i++) {
        bool col_checkdown[101] = { false, };
        bool col_checkup[101] = { false, };
        bool can = true;
        for (int j = 0; j < n - 1; j++) {
            // ���� ���̰� 1���� ũ��? -> break�� ���� �ٷ�
            if (abs(v_col[i][j] - v_col[i][j + 1]) > 1) {
                can = false;
                break;
            }
        }
        // �������� ���̻� Ȯ�� x -> ���� �ٷ� �̵�
        if (!can)continue;

        // ���� ���̰� 1���� ū ��찡 ���ٸ� ���� ����� 
        for (int j = 0; j < n - 1; j++) {

            // ���� ���̰� -1 �� ��� 
            if (v_col[i][j] - v_col[i][j + 1] == 1) {
                // ���� �������� ������ ���� ���̰� �󸶳� �ִ��� Ȯ��
                int cnt = 1;
                for (int k = j + 1; k < n - 1; k++) {
                    if (v_col[i][k] == v_col[i][k + 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // ���� cnt�� j+1��° �������� ������ �Ȱ��� ������ ������ ����
                // cnt�� L�� �̻��̸� j+1��°���� ������ L������ ���θ� ���� => bool�迭�� ���
                if (cnt >= l) {

                    for (int k = 1; k <= l; k++) {
                        col_checkdown[j + k] = true;
                    }
                }
            }

            // ���� ���̰� +1 �� ���
            else if (v_col[i][j] - v_col[i][j + 1] == -1 && !col_checkdown[j]) {
                // ���� �������� 0������ ���� ���̰� �󸶳� �ִ��� Ȯ��
                int cnt = 1;
                for (int k = j; k > 0; k--) {
                    if (v_col[i][k] == v_col[i][k - 1] && !col_checkdown[k - 1]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                // ���� cnt�� j��° �������� �ڷ� �Ȱ��� ������ ������ ����
                // cnt�� L�� �̻��̸� j��°���� �ڷ� L+1������ ���θ� ���� => bool�迭�� ���
                if (cnt >= l) {

                    for (int k = 0; k < l; k++) {
                        col_checkup[j - k] = true;
                    }
                }
            }

        }
        // ���� ������ ���� ������ ���̰� ���ų� 
        // ���� ������ +1�� �� ���� ������ ���ΰ� �ְų�
        // ���� ������ -1�� �� ���� ������ ���ΰ� �ְų�
        // ������ false ��ȯ
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