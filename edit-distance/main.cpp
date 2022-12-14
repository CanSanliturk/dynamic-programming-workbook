#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

/*
	Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

	You have the following three operations permitted on a word:

    	* Insert a character
    	* Delete a character
    	* Replace a character
*/


int getEditDistanceWithRecursion(const string& word1, const string& word2, unordered_map<string, int>& cache, int i1 = 0, int i2 = 0) {

	string key = "";
	key += (i1 + '0');
	key += ',';
	key += (i2 + '0');
	if (cache.find(key) != cache.end())
		return cache[key];

	if (i1 == word1.length())
		cache[key] = word2.length() - i2;

	else if (i2 == word2.length())
		cache[key] = word1.length() - i1;

	else if (word1[i1] == word2[i2])
		cache[key] = getEditDistanceWithRecursion(word1, word2, cache, i1 + 1, i2 + 1);
	else
		cache[key] = 1 + min(
					getEditDistanceWithRecursion(word1, word2, cache, i1 + 1, i2 + 1),
					min(
						getEditDistanceWithRecursion(word1, word2, cache, i1, i2 + 1),
						getEditDistanceWithRecursion(word1, word2, cache, i1 + 1, i2)
					)
				);

	return cache[key];
}

int getEditDistanceWithTabulation(const string& word1, const string& word2) {

	auto m = word1.length();
	auto n = word2.length();

	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	for (int i = 0; i <= m; ++i)
		dp[i][0] = i;

	for (int i = 0; i <= n; ++i)
		dp[0][i] = i;

	for (int i = 1; i <= m; ++i)
		for (int j = 1; j <= n; ++j)
			if (word1[i - 1] == word2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));

	return dp[m][n];
}

int main() {

	auto testCase = [](const string& word1, const string& word2, const int& expectedOutput) {

		cout << "__________" << endl;
		cout << "TEST CASE" << endl;
		cout << "Input: \"" << word1 << "\" and \"" << word2 << "\"" << endl;
		cout << "Expected: " << expectedOutput << endl;
		unordered_map<string, int> cache;
		auto ansRec = getEditDistanceWithRecursion(word1, word2, cache);
		cout << "Calculated With Recursion: " << ansRec << endl;
		auto ansTab = getEditDistanceWithTabulation(word1, word2);
		cout << "Calculated With Tabulation: " << ansTab << endl;
		cout << "Status: " << (((ansRec == ansTab) && (ansTab == expectedOutput)) ? "PASS" : "FAIL") << endl;
		cout << "__________" << endl; 
	};

	testCase("index", "inside", 3);
	testCase("horse", "ros", 3);
	testCase("intention", "execution", 5);

	return 0;
}