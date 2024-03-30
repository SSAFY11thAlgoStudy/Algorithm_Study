#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

int n, q;
vector<int>fuel;

void input() {
	cin >> n >> q;
	int num;
	for (int i = 0; i < n; i++) {
		cin >> num;
		fuel.push_back(num);
	}
	sort(fuel.begin(), fuel.end());
}

int binarysearch(int m) {
	int mid, low = 0, high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (fuel[mid] == m) return mid;
		else if (fuel[mid] < m) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}

	return 0;
}
int main(int argc, char** argv)
{
	input();
	int num, m;
	for (int i = 0; i < q; i++) {
		cin >> m;
		num = binarysearch(m);

		cout << num * (n - num - 1) << "\n";
	}

	return 0;
}