#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M; // ������ ���� N�� ������ ���� M�� ������ ���� ����
int degree[32001] = { 0, }; // �� ������ ���� ������ ������ ����
vector<int> v[32001]; // ���� ����Ʈ ������ �׷��� ǥ��
vector<int> result; //���

//�Է�
void input() {
    cin >> N >> M; // ������ ���� N�� ������ ���� M�� �Է� ����
    for (int i = 0; i < M; i++) {
        int front_num, back_num;
        cin >> front_num >> back_num;
        v[front_num].push_back(back_num); // �׷��� ������ ����
        degree[back_num]++; // ���� ������ ���� ���� ����
    }
}


void solve() {
    //queue�� �̿��� ���̻� ��尡 ���� ���� ������
    queue<int> q;
    for (int i = 1; i <= N; i++)
    {
        // ������ 0�ΰ��� ���ʿ� ���͵� ������� �������� q�� ����
        if (degree[i] == 0) {
            q.push(i);
        }
    }

    //q�� ���� �������� �ݺ�
    while (!q.empty()) {
        int num = q.front();
        q.pop();
        //ť���� ���� ���� �ٷ� ��� �迭�� ����
        result.push_back(num);

        //ť�� ���� ���� �θ� �Ǵ� ��带 Ȯ���ؼ� ������ ���ҽ�Ų��.
        for (int i : v[num])
        {
            degree[i]--;
            // ���� ��Ų ������ 0�̵Ǹ� ���̻� �� ���տ� �ü��� �̹� queue�� ���°������� queue�� �־���
            if (degree[i] == 0) {
                q.push(i);
            }
        }
    }
}

int main() {
    //�Է�
    input();

    solve();

    // ��� ���
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }

    return 0;
}