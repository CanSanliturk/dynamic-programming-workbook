#include <vector>
#include <iostream>

using namespace std;

/*
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that 
is either directly below or diagonally left/right. Specifically, the next element from position (row, col) 
will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
*/

int getMinPathSum(const vector<vector<int>>& grid) {

	auto m = grid.size();
	auto n = grid[0].size();

	vector<vector<int>> dp(m, vector<int>(n, 0));

	auto getMinFromUp = [&](int i, int j) {

		int mn = 1 << 30;
		if (0 < j)
			mn = min(mn, dp[i - 1][j - 1]);
		if (j != n - 1)
			mn = min(mn, dp[i - 1][j + 1]);
		mn = min(mn, dp[i - 1][j]);

		return mn;
	};

	dp[0] = grid[0];
	for (int i = 1; i < m; ++i)
		for (int j = 0; j < n; ++j)
			dp[i][j] = grid[i][j] + getMinFromUp(i, j);


	auto ans = 1 << 30;
	for (int i = 0; i < n; ++i)
		ans = min(ans, dp[m - 1][i]);

	return ans;
}

int main() {

	auto testCase = [](const vector<vector<int>>& grid, const int& expectedOutput) {

		cout << "__________" << endl; 
		cout << "TEST CASE" << endl;
		cout << "Expected: " << expectedOutput << endl;
		auto ans = getMinPathSum(grid);
		cout << "Calculated: " << ans << endl;
		cout << "Status: " << (ans == expectedOutput ? "PASS" : "FAIL") << endl;
		cout << "__________" << endl; 
	};

	testCase(
		{ 
			{ 3, 2, 12, 15, 10 },
			{ 6, 19, 7, 11, 17 },
			{ 8, 5, 12, 32, 21 },
			{ 3, 20, 2, 9, 7 }
		}, 
		15);


	return 0;
}