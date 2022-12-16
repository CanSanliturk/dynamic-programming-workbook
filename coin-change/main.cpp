#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
	Given an integer that represents an amount of money and a list of possible coins,
	find the minimum number of coins to make that amount. Return -1 if it is not possible
	to make the amount with the given coins
*/

int coinChange(int n, const vector<int>& coins) {

	auto maxInt = 1 << 30;
	vector<int> dp(n + 1, 1 << 30);

	dp[0] = 0;

	for (int i = 1; i <= n; ++i)
		for (auto coin : coins)
			if (0 <= (i - coin))
				dp[i] = min(dp[i], 1 + dp[i - coin]);

	return dp[n] == maxInt ? -1 : dp[n];
}

int main() {

	auto testCase = [](int n, const vector<int>& coins, int expectedOutput) {
		cout << "__________" << endl;
		cout << "TEST CASE" << endl;
		cout << "Number of Steps: " << n << endl;
		cout << "Available Coins: ";
		for (auto i : coins)
			cout << i << " ";
		cout << endl;
		cout << "Expected Output: " << expectedOutput << endl;
		auto ansTab = coinChange(n, coins);
		cout << "Output of Tabulation: " << ansTab << endl;
		cout << "STATUS: " << ((ansTab == expectedOutput) ? "PASS" : "FAIL") << endl;
		cout << "__________" << endl;
	};

	testCase( 15, { 2, 3, 7 }, 4 );

	return 0;
}