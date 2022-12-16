#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

int waysToClimbMemoization(int n, const vector<int>& jumps, unordered_map<int, int>& cache) {

	if (cache.find(n) != cache.end())
		return cache[n];

	if (n == 0)
		return 1;

	auto ans = 0;

	for (auto jump : jumps)
		if (0 <= n - jump)
			ans += waysToClimbMemoization(n - jump, jumps, cache);

	cache[n] = ans;
	return ans;
}

int waysToClimbTabulation(int n, const vector<int>& jumps) {

	vector<int> dp(n + 1, 0);
	dp[0] = 1;

	for (int i = 1; i <= n; ++i)
		for (auto jump : jumps)
			if (0 <= i - jump)
				dp[i] += dp[i - jump];

	return dp[n];
}

int main() {

	auto testCase = [](int n, const vector<int>& jumps, int expectedOutput) {
		cout << "__________" << endl;
		cout << "TEST CASE" << endl;
		cout << "Number of Steps: " << n << endl;
		cout << "Possible Jumps: ";
		for (auto i : jumps)
			cout << i << " ";
		cout << endl;
		cout << "Expected Output: " << expectedOutput << endl;
		unordered_map<int, int> cache;
		auto ansMem = waysToClimbMemoization(n, jumps, cache);
		cout << "Output of Memoization: " << ansMem << endl;
		auto ansTab = waysToClimbTabulation(n, jumps);
		cout << "Output of Tabulation: " << ansTab << endl;
		cout << "STATUS: " << (((ansMem == ansTab) && (ansTab == expectedOutput)) ? "PASS" : "FAIL") << endl;
		cout << "__________" << endl;
	};

	testCase( 10, { 2, 4, 5, 8 }, 11 );

	return 0;
}