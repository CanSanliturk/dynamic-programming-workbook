#include <array>
#include <vector>
#include <iostream>

using namespace std;

/*
	A matrix is given and value of cells are cost of passing through it.
	Find the minimum cost of reaching the bottom-right cell starting from
	top-left cell.
*/

int minCostUsingTopDown(vector<vector<int>>& input, int i, int j, vector<vector<int>> cache) {

	if (cache[i][j] != -1)
		return cache[i][j];

	auto nRow = input.size();
	auto nCol = input[0].size();

	if (i == 0 && j == 0)
		return input[i][j];

	if (i == 0)
		cache[i][j] = input[i][j] + minCostUsingTopDown(input, i, j - 1, cache);
	else if (j == 0)
		cache[i][j] = input[i][j] + minCostUsingTopDown(input, i - 1, j, cache);
	else
		cache[i][j] = input[i][j] + min(
			minCostUsingTopDown(input, i, j - 1, cache), 
			minCostUsingTopDown(input, i - 1, j, cache)
			);

	return cache[i][j];
}

int minCostUsingBottomUp(vector<vector<int>>& input) {

	vector<vector<int>> dp(input.size(), vector<int>(input[0].size(), 0));
	dp[0][0] = input[0][0];

	for (int i = 1; i < input[0].size(); ++i)
		dp[0][i] = input[0][i] + dp[0][i - 1];

	for (int i = 1; i < input.size(); ++i)
		dp[i][0] = input[i][0] + dp[i - 1][0];

	for (int i = 1; i < input.size(); ++i)
		for (int j = 1; j < input[0].size(); ++j)
			dp[i][j] = input[i][j] + min(dp[i - 1][j], dp[i][j - 1]);

	return dp[input.size() - 1][input[0].size() - 1];
} 

int main() {

	vector<vector<int>> inputMatrix{
		{ 3, 2, 12, 15, 10 },
		{ 6, 19, 7, 11, 17 },
		{ 8, 5, 12, 32, 21 },
		{ 3, 20, 2, 9, 7 }
	};

	vector<vector<int>> cache(inputMatrix.size(), vector<int>(inputMatrix[0].size(), -1));
	auto ansOfMemorization = minCostUsingTopDown(inputMatrix, inputMatrix.size() - 1, inputMatrix[0].size() - 1, cache);
	auto ansOfTabulation = minCostUsingBottomUp(inputMatrix);

	cout << "Answer of Memorization: " << ansOfMemorization << endl;
	cout << "Answer of Tabulation: " << ansOfTabulation << endl;

	return 0;
}
