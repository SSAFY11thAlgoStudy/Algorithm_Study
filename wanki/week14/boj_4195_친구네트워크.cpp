#include <iostream>
#include <unordered_map>

using namespace std;
unordered_map<string, string> um(200001);
unordered_map<string, int> nums(200001);


string find(string tar) {
	if (um[tar] == tar) return tar;
	string ret = find(um[tar]);

	//경로 압축
	um[tar] = ret;
	return ret;
}

void set_union(string a, string b) {
	string A = find(a);
	string B = find(b);

	if (A == B) return;

	um[B] = A;
	nums[A] += nums[B];
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;

	while (T--) {
		int n;
		cin >> n;

		um.clear();
		nums.clear();

		for (int i = 0; i < n; i++) {
			string a, b;
			cin >> a >> b;
			if (um.count(a) == 0) {
				um.insert(make_pair(a, a));
				nums.insert(make_pair(a, 1));
			}
			if (um.count(b) == 0) {
				um.insert(make_pair(b, b));
				nums.insert(make_pair(b, 1));
			}
			set_union(a, b);
			cout << nums[find(a)] << "\n";
		}
	}
	return 0;
}