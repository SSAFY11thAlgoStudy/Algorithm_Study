#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

//���� ���� ����
int N1;

//��ɾ� ����
int N2;

char frontC;
int pos; //��ġ����
int Num; //���� ���� ����

int main() {

    freopen("sample_input.txt", "r", stdin);

    for (int tc = 1; tc <= 10; tc++) {
        cin >> N1;
        vector<int> v;
        // ���� ��ȣ�� �Է�
        for (int i = 0; i < N1; i++) {
            int origin = 0;
            cin >> origin;
            v.push_back(origin);
        }

        cin >> N2;
        vector<int> cv;
        // ��ɾ� �Է�
        for (int i = 0; i < N2; i++) {
            cin >> frontC >> pos >> Num;

            if (frontC == 'I') {
                for (int j = 0; j < Num; j++) {
                    int ins = 0;
                    cin >> ins;
                    cv.push_back(ins);
                }
                // ���� ��ȣ���� ��ɾ� ����
                v.insert(v.begin() + pos, cv.begin(), cv.end());
                // ��ɾ� �ʱ�ȭ
                cv.clear();

            }
        }

        cout << "#" << tc << " ";
        for (int i = 0; i < 10; i++) {
            cout << v[i] << " ";
        }
        cout << endl;
        // ��� �� ���� ��ȣ�� �ʱ�ȭ
        v.clear();
    }

    return 0;
}