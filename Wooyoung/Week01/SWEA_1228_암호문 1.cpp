#include <iostream>
#include <vector>
#include <queue>
using namespace std;




int main() {

    int t = 10;
    for (int i = 1; i <= t; i++) {

        // N : ���� ��ȣ���� ���� (10<=N<=20)
        // num : ���� ��ȣ��
        // M : ��ɾ��� ���� (5<=M<=10)
        // c, x, y, s : 
        // c : ��ɾ� ����(����� ����(I)�� ����), 
        // x : �����ϰ��� �ϴ� ��ġ
        // y : �����ϰ��� �ϴ� ���� ����
        // s : �����ϰ��� �ϴ� ����
        int N, num, M, x, y, s;
        char c;
        vector<int>v;

        cin >> N;
        for (int j = 0; j < N; j++) {
            cin >> num;
            v.push_back(num);
        }
        cin >> M;

        for (int j = 0; j < M; j++) {
            vector<int>temp;
            cin >> c >> x >> y;
            for (int k = 0; k < y; k++) {
                cin >> s;
                temp.push_back(s);
            }
            // v������ x������ temp�� ���ۺ��� y��°���� ���� �����ϰڴ�.
            v.insert(v.begin() + x, temp.begin(), temp.begin() + y);
        }
        cout << "#" << i << " ";
        for (int j = 0; j < 10; j++) {
            cout << v[j] << " ";
        }
        cout << "\n";
    }

    return 0;
}