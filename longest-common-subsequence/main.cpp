#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
	Given two strings text1 and text2, return the length of their longest common subsequence. 
	If there is no common subsequence, return 0.

	A subsequence of a string is a new string generated from the original string with some characters (can be none) 
	deleted without changing the relative order of the remaining characters.

    	* For example, "ace" is a subsequence of "abcde".

	A common subsequence of two strings is a subsequence that is common to both strings.
*/

int getLCS(const string& str1, const string& str2, int i1 = 0, int i2 = 0) {


	if (i1 == str1.length() || i2 == str2.length())
		return 0;

	if (str1[i1] == str2[i2])
		return 1 + getLCS(str1, str2, i1 + 1, i2 + 1);
	return max(getLCS(str1, str2, i1 + 1, i2), getLCS(str1, str2, i1, i2 + 1));
}


int getLCSBottomUp(const string& str1, const string& str2) {

    int m = str1.length(), n = str2.length();
        
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            dp[i][j] = str1[i - 1] == str2[j - 1] ?
                1 + dp[i - 1][j - 1] :
                max(dp[i - 1][j], dp[i][j - 1]);

    return dp[m][n];
}


int main() {

	auto test = [](const string& str1, const string& str2, const int& expectedOutput) {
		cout << "__________" << endl;
		cout << "TEST CASE" << endl;
		cout << "Inputs: \"" << str1 << "\" and \"" << str2 << "\"" << endl;
		cout << "Expected: " << expectedOutput << endl;
		auto calcRec = getLCS(str1, str2);
		auto calcBU = getLCSBottomUp(str1, str2);
		cout << "Calculated (Recursive): " << calcRec << endl;
		cout << "Calculated (Bottom-Up): " << calcBU << endl;
		auto isPass = (calcRec == calcBU) && (calcBU == expectedOutput);
		cout << "Status: " << (isPass ? "PASS" : "FAIL") << endl;
		cout << "__________" << endl;
	};

	test("abdacbab", "acebfca", 4);

	return 0;
}
