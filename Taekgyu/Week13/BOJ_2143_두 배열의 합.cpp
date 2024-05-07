#define _CRT_SECURE_NO_WARNNGS
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

// �� �迭 A�� ���ؼ�
// �� �迭�� A[i], A[i+1], ��, A[j-1], A[j] (��, 1 �� i �� j �� n)�� ���Ѵ�
// �̷��� �ι迭�� ���� A[i]+��+A[j]�� �ǹ��Ѵ�
// �� ���Ұ� ������ �� �迭 A,B�� �־����� ��
// A�� �ι迭�� �տ� B �ι迭�� ���� ���ؼ� T�� �Ǵ� ��� �� �迭 ���� ������ ���϶�

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
			// A �迭�� ��� �κ����� Asum ���Ϳ� �����Ѵ�
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
		// B�迭�� �κ����� ���Ѵ�
		// �� �κ��հ� T���� ���� Asum�� �ִٸ� �κ��� ����� �� ++
		long long sum = 0;
		for (int j = i; j < m; j++)
		{
			sum += B[j];
			// ã�ƾ��ϴ� ����
			long long findNum = T - sum;

			// Asum�� ��Ʈ �Ǿ��ִ� ����
			// ã�ƾ��ϴ� ������ �������� = lower_bound
			// ã�ƾ��ϴ� ������ �� ���� = upper_bound
			// ���� �ε��� ���� ���ָ� ������ ���´�
			Ans += (upper_bound(Asum.begin(), Asum.end(), findNum) - Asum.begin()) - (lower_bound(Asum.begin(), Asum.end(), findNum) - Asum.begin());
		}
	}
	cout << Ans;

	return 0;
}