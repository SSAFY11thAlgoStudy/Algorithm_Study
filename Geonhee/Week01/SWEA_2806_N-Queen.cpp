#include <iostream>
#include <algorithm>
using namespace std;
int t, n, cnt = 0; // cnt = queen�� ���� �� �ִ� ����� �� 
int d[11]; // queen ���� �迭 
bool check(int x) {
    for (int i = 0; i < x; i++) {  // x�� ���� �����ϴ��� Ȯ��
        if (d[x] == d[i] || abs(d[x] - d[i]) == x - i)
            return false;  // d[x] == d[i]�̸� �������� ���� ���
        // abs(d[x]-d[i]) == x - i �� �밢���� ���� ��� 
    }
    return true;
}
void dfs(int x) {
    if (x == n) {  // n�� �������� ���� ���������� �����Ƿ� 
        cnt++;
        return;
    }
    else {
        for (int i = 0; i < n; i++) { // 0~n-1���� queen�� �����ϹǷ�
            d[x] = i; // d[x]�ڸ��� i ����
            if (check(x)) // x������ ���ؼ�  queen �迭 check���ֱ�
                dfs(x + 1); //true�� �°� ��ġ�����Ƿ� x+1���� �Ѿ��
        }
    }

}
int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        cnt = 0; // t��ŭ ���ƾ��ϹǷ� cnt = 0���� �׻� �ʱ�ȭ
        dfs(0);  // 0���� n-1���� ������ �ǹǷ� 0���� ����
        cout << "#" << i + 1 << " " << cnt << '\n';
    }
    return 0;
}