#include <vector>
#include <string>
#include <iostream>

using namespace std;

/*
	Find the shortest string to contain both strings
*/
string getShortestCommonSupersequence(const string& str1, const string& str2) {

    auto len1 = str1.length();
    auto len2 = str2.length();
    vector<vector<string>> dp(len2 + 1, vector<string>(len1 + 1, ""));

    for (int i = 1; i <= len1; ++i)
        dp[0][i] = str1.substr(0, i);
        
    for (int i = 1; i <= len2; ++i)
        dp[i][0] = str2.substr(0, i);

    for (int i = 1; i <= len2; ++i) {
        for (int j = 1; j <= len1; ++j) {
            auto curr1 = str1[j - 1];
            auto curr2 = str2[i - 1];
                
            if (curr1 == curr2)
                dp[i][j] = dp[i - 1][j - 1] + curr1;

            else if ((dp[i - 1][j].length()) < (dp[i][j - 1].length()))
                dp[i][j] = dp[i - 1][j] + curr2;
            else
                dp[i][j] = dp[i][j - 1] + curr1;
        }
    }

    return dp[len2][len1];
}

int main() {

	auto test = [](const string& str1, const string& str2, const string& expectedOutput) {
		cout << "__________" << endl;
		cout << "TEST CASE" << endl;
		cout << "Inputs: \"" << str1 << "\" and \"" << str2 << "\"" << endl;
		cout << "Expected: " << expectedOutput << endl;
		auto calcBU = getShortestCommonSupersequence(str1, str2);
		cout << "Calculated (Tabulation): " << calcBU << endl;
		cout << "Status: " << (calcBU.length() == expectedOutput.length() ? "PASS" : "FAIL") << endl;
		cout << "__________" << endl;
	};

	test("abac", "cab", "cabac");
	test("aaaaaaaa", "aaaaaaaa", "aaaaaaaa");
	test("abdacebfcab", "acebfca", "abdacebfcab");

	return 0;
}
