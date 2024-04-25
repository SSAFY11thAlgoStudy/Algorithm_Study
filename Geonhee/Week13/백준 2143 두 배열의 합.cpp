#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long long t;
int n, m;
int a[1001], b[1001];
vector<int> a_prefix;
vector<int> b_prefix;
long long res;

int lowerBound(int tar) {
    int st = 0;
    int en = b_prefix.size();

    while (st < en) {
        int mid = (st + en) / 2;
        if (b_prefix[mid] < tar) st = mid + 1;
        else en = mid;
    }
    return st;
}

int upperBound(int tar) {
    int st = 0;
    int en = b_prefix.size();

    while (st < en) {
        int mid = (st + en) / 2;
        if (b_prefix[mid] <= tar) st = mid + 1;
        else en = mid;
    }
    return st;
}

int main() {
    cin >> t;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> b[i];

    //a에서 나올 수 있는 모든 합 만들기
    for (int i = 0; i < n; i++) {
        int x = a[i];
        a_prefix.push_back(x);
        for (int j = i + 1; j < n; j++) {
            x += a[j];
            a_prefix.push_back(x);
        }
    }
    //b에서 나올 수 있는 모든 합 만들기
    for (int i = 0; i < m; i++) {
        int x = b[i];
        b_prefix.push_back(x);
        for (int j = i + 1; j < m; j++) {
            x += b[j];
            b_prefix.push_back(x);
        }
    }
    //a 누적합은 놔두고 b 누적합만 정렬해서
    //t - a 누적합 벡터값 해서 인덱스 찾기 위함
    sort(b_prefix.begin(), b_prefix.end());
    for (int i = 0; i < a_prefix.size(); i++) {
        int temp = t - a_prefix[i];
        //같은 값이 있는 것은 아나 어디서 부터 어디까지 있는지 모르니
        // lowerbound, upperbound를 써야한다.
        //lowerbound = 시작 인덱스 반환, temp가 없으면 temp보다 큰 첫 인덱스 반환
        //upperbound = 끝 다음의 인덱스 반환, temp가 없으면 temp보다 큰 첫 인덱스 반환
        long long lb = lowerBound(temp);
        long long ub = upperBound(temp);
        // ub 인덱스 값 - lb 인덱스 값 하면 temp인덱스 의 수
        res += (ub - lb);
    }
    cout << res;
    return 0;
}