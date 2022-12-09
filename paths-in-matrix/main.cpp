#include <vector>
#include <iostream>

using namespace std;

/*
	Given a matrix where a cell has the value of 1 if it is a wall and 0 if not, find the
	number of ways to go from the top-left cell to the bottom-right cell, knowing that
	it is not possible to pass from a wall and we can onnly go the the right or to the bottom.
*/

int numOfWays(const vector<vector<bool>>& grid) {

	int nRow = grid.size(), nCol = grid[0].size();

	vector<vector<int>> dp(nRow, vector<int>(nCol, 0));
	dp[0][0] = 1;

	for (int i = 1; i < nCol; ++i) {
		if (grid[0][i] == 1)
			break;
		dp[0][i] = 1;
	}

	for (int i = 1; i < nRow; ++i) {
		if (grid[i][0] == 1)
			break;
		dp[i][0] = 1;
	}

	for (int i = 1; i < nRow; ++i)
		for (int j = 1; j < nCol; ++j)
			if (grid[i][j] == 0)
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];

	return dp[nRow - 1][nCol - 1];
}

int main() {

	cout << "Number of Ways: Expected = 7, Calculated = " <<
		numOfWays({
			{ 0, 0, 1, 0, 1 },
			{ 0, 0, 0, 0, 1 },
			{ 0, 0, 1, 0, 0 },
			{ 1, 0, 0, 0, 0 }
		}) << endl;

	return 0;
}