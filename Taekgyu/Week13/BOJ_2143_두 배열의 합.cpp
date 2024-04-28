#define _CRT_SECURE_NO_WARNNGS
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

// 한 배열 A에 대해서
// 부 배열은 A[i], A[i+1], …, A[j-1], A[j] (단, 1 ≤ i ≤ j ≤ n)을 말한다
// 이러한 부배열의 합은 A[i]+…+A[j]를 의미한다
// 각 원소가 정수인 두 배열 A,B가 주어졌을 때
// A의 부배열의 합에 B 부배열의 합을 더해서 T가 되는 모든 부 배열 쌍의 개수를 구하라

int n;
int m;
int T;
int A[1001];
int B[1001];
vector<long long>Asum;
long long Ans;

int main() {

	cin >> T;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
	}
	for (int i = 0; i < n; i++)
	{
		long long sum = 0;
		for (int j = i; j < n; j++)
		{
			// 0, 01, 012, 1, 12, 2 ~~~
			// A 배열의 모든 부분합을 Asum 벡터에 저장한다
			sum += A[j];
			Asum.push_back(sum);
		}
	}

	sort(Asum.begin(), Asum.end());
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> B[i];
	}
	for (int i = 0; i < m; i++)
	{
		// B배열의 부분합을 구한다
		// 그 부분합과 T와의 차가 Asum에 있다면 부분합 경우의 수 ++
		long long sum = 0;
		for (int j = i; j < m; j++)
		{
			sum += B[j];
			// 찾아야하는 숫자
			long long findNum = T - sum;

			// Asum은 소트 되어있는 상태
			// 찾아야하는 숫자의 시작지점 = lower_bound
			// 찾아야하는 숫자의 끝 지점 = upper_bound
			// 둘의 인덱스 값을 빼주면 개수가 나온다
			Ans += (upper_bound(Asum.begin(), Asum.end(), findNum) - Asum.begin()) - (lower_bound(Asum.begin(), Asum.end(), findNum) - Asum.begin());
		}
	}
	cout << Ans;

	return 0;
}