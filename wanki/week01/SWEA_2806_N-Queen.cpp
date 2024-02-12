#define _CRT_SECURE_NO_WARNING
#include <iostream>

using namespace std;

int N, cnt = 0;
//ü���ǿ� ��ġ�� ����
// position[��] = ���� ��ġ
int position[13];

// 
int isvalid(int node, int i) {
    for (int j = 0; j < node; j++)
    {
        // �� �Ʒ�Ž��
        if (position[j] == i)return 0;
        // ���� Ž��
        if (position[j] + (node - j) == i) return 0;
        // ���� Ž��
        if (position[j] - (node - j) == i) return 0;
    }
    return 1;
}

//node�� ���� ����
void dfs(int node) {

    // �������� node(��)�� N���� ���� �� 
    if (node == N) {
        cnt++;
        return;
    }

    // ���� N���� �ֱ� ������ N���� ���� ��ġ Ž��
    for (int i = 0; i < N; i++)
    {
        // ��ȿ��ġ���� Ž��
        if (isvalid(node, i)) {
            //�´ٸ�, node�࿡ i���� ��ġ �� ����
            position[node] = i;
            // ���
            dfs(node + 1);
        }
    }
}


int main()
{
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> N;

        dfs(0);
        cout << "#" << tc << " " << cnt;
    }

    return 0;
}
