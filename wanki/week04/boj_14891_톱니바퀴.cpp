#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using namespace std;

vector<char>wheel[5];

//�Է�
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
    // �ð����
    if (dir == 1) {
        char swap = wheel[num][7];
        wheel[num].insert(wheel[num].begin(), swap);
        wheel[num].pop_back();
    }
    // �ݽð� ����
    else if (dir == -1) {
        char swap = wheel[num][0];
        wheel[num].push_back(swap);
        wheel[num].erase(wheel[num].begin());
    }
}

// ������ �˻�
void right_search(int num, int dir) {
    //������ �ٱ����� ����� ������,
    //�������� ���� 2���� �� ������ ������ 6���� �ٸ��� 
    //�� ������ ������ �����ʵ� Ȯ���Ͽ� ȸ����Ų��.(���)
    //���� ���ٸ� �� �������� �������� ������ ���� ȸ������ �ʴ´�.
    if (num < 4 && wheel[num][2] != wheel[num + 1][6]) {
        right_search(num + 1, -dir);
    }
    //�ּ� ������ ȸ���Ѵ�.
    Turn(num, dir);
}

// ���� �˻�
void left_search(int num, int dir) {
    //���� �ٱ����� ����� ������,
    //�������� ���� 6���� �� ���� ������ 2���� �ٸ��� 
    //�� ���� ������ ���ʵ� Ȯ���Ͽ� ȸ����Ų��. (���)
    //���� ���ٸ� �� �������� ������ ������ ���� ȸ������ �ʴ´�.
    if (num > 1 && wheel[num][6] != wheel[num - 1][2]) {
        left_search(num - 1, -dir);
    }
    //�ּ� ������ ȸ���Ѵ�.
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
        // ������ �˻縦 �Ϸ��ϸ� �Է¹��� ������ ���ư��⿡ �� ������ ������
        Turn(num, -dir);
        left_search(num, dir);
    }

    // ���� ���
    // ������ 2^wheel_num[0,1,2,3]�� ũ�⸦ ����
    int result = 0;
    for (int i = 1; i <= 4; i++) {
        if (wheel[i][0] == '1') {
            result += pow(2, i - 1);
        }
    }
    cout << result;

    return 0;
}
