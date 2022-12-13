#include <vector>
#include <iostream>

using namespace std;

/*
	Given an array of integers where an element of an array represents the amount
	of money in the house at that index. Aim is to find the maximum amount of the money
	that a robber can steal knowing that robber cannot steal two adjacent houses because
	the security systems would automatically call the police
*/

int getMaxMoney(const vector<int>& houses) {

	if (houses.size() == 0)
		return 0;

	if (houses.size() == 1)
		return houses.at(0);

	vector<int> dp(houses.size(), 0);
	dp[0] = houses[0];
	dp[1] = max(houses[1], dp[0]);

	for (int i = 2; i < houses.size(); ++i)
		dp[i] = max(houses[i] + dp[i - 2], dp[i - 1]);

	return dp[dp.size() - 1];
}

int main() {

	auto test = [](const vector<int>& input, int expectedOutput) {
		cout << "__________" << endl;
		cout << "TEST CASE" << endl;
		cout << "Input: ";
		for (auto i : input)
			cout << i << " ";
		cout << endl;
		cout << "Expected: " << expectedOutput << endl;
		auto calc = getMaxMoney(input);
		cout << "Calculated: " << calc << endl;
		cout << "Status: " << (calc == expectedOutput ? "PASS" : "FAIL") << endl;
		cout << "__________" << endl;
	};
	test({ 2, 10, 3, 6, 8, 1, 7 }, 25);
	test({ 2, 1, 1, 2 }, 4);
	return 0;
}
