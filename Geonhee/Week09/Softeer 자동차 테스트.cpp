#include <iostream>
#include <algorithm>
using namespace std;

int n, q;
int arr[50001];

int bs(int x) {
    int st = 0;
    int en = n - 1;
    int mid = 0;
    while (st <= en) {
        mid = (st + en) / 2;
        // x�� ã������ �ε��� �� return���ֱ�
        if (x == arr[mid]) return mid;
        // ���� arr[mid] ���� �� ũ�ٸ� en index��  mid������ 1 �ٿ��ֱ�
        else if (arr[mid] > x) en = mid - 1;
        // ���� arr[mid]���� �� �۴ٸ� st index�� mid������ 1 �÷��ֱ�
        else st = mid + 1;
    }
    return 0;
}

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    //�̺�Ž���� ���� ����
    sort(arr, arr + n);
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        //ó���� ���� �������� ��� �߰� ���� �� �� �����Ƿ� 0 ���
        if (arr[0] == a || arr[n - 1] == a) {
            cout << 0 << '\n';
            continue;
        }
        else {
            int idx = bs(a);
            //���� �ε��� ���� �����ſ� ���� * ū�ſ� ����
            cout << idx * (n - idx - 1) << '\n';
        }
    }
    return 0;
}